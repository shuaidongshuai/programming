#include "DtbtNginx.h"
#include "inNginx.pb.h"
#include "protoCallBack.h"
#include "Processpool.h"
#include "Nginx.h"
#include "ConsistentHash.h"
#include "easylogging++.h"
//使用宏 INITIALIZE_EASYLOGGINGPP 初始化log
INITIALIZE_EASYLOGGINGPP

/* 把全局的 需要修改的全部映射到共享区 */
DtbtNginx::DtbtNginx():status(FOLLOWER), voteNum(0){
	version[0] = 0;
	version[1] = 0;
}
DtbtNginx::~DtbtNginx(){
}

bool DtbtNginx::ReadDtbtNginxConf(string num, string confSrc){
	if(num.empty() || confSrc.empty())
		return false;
	string hostPre("DtbtNginx");
	string listenPre("ListenNginx");
	ReadConf rc;
	rc.read(confSrc);
	int idx;
	for(auto m : rc.conf){
		string key = m.first;
		string val = m.second;
		idx = val.find(':');
		if(idx == val.npos){
			LOG(ERROR) << "ReadDtbtNginxConf error";
			return false;
		}
		string ip(val, 0, idx);
		string port(val, idx + 1, val.size());
		//设置本机名
		if(hostPre + num == key){
			nginxName = ip + " " + port;
			LOG(DEBUG) << "selfNginxName = " << nginxName;
		}
		else if(listenPre + num == key){
			lisName = ip + " " + port;
			LOG(DEBUG) << "listenName = " << lisName;
		}
		else if(hostPre == string(key.begin(), key.end() - 1)){
			otherName.push_back(ip + " " + port);
			LOG(DEBUG) << "DtbtNginx = " << ip + " " + port;
		}
	}
	allNginxNum = otherName.size() + 1;
	return true;
}
/* connect other nginxs */
void DtbtNginx::ConOtherNginx(){
	aliveNginxfd.clear();
	struct sockaddr_in servaddr;
	int sockfd;
	int size = otherName.size();
	for(int i = 0; i < size; ++i){
		int idx = otherName[i].find(' ');
		string ipStr(otherName[i], 0, idx);
		string portStr(otherName[i], idx + 1, otherName[i].size());
		const char *ip = ipStr.c_str();
		int port = atoi(portStr.c_str());
		if(0 == port){
			LOG(ERROR) << "ConOtherNginx transform port error";
			continue;
		}
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			LOG(ERROR) << "ConOtherNginx create socket error";
			return;
		}
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		inet_pton(AF_INET, ip, &servaddr.sin_addr);
		servaddr.sin_port = htons(port);
		
		if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1) {
			LOG(WARNING) << "connect:" << ip << ":" << port << " Error"; 
		}
		else{
			aliveNginxfd.push_back(sockfd);
			LOG(DEBUG) << "connect -> " << otherName[i];
		}
	}
}

/* 发起投票 */
void DtbtNginx::VoteSend(){
	//vote for myself
	voteNum = 1;
	//vote for other
	for(auto fd : aliveNginxfd){
		string data;
		Vote v;
		v.set_version(version[ENSURE] + 1);//版本 + 1 
		v.set_nginxname(nginxName);
		v.SerializeToString(&data);
		if(!nginxs[fd].WriteProto(VoteNo, data)){
			nginxs[fd].Addfd2Write();
		}
		else{
			nginxs[fd].Addfd2Read();
		}
	}
	LOG(DEBUG) << "vote to all";
}
/* 如果变为了Leader 需要向其他 follower */
void DtbtNginx::AckVote2FollowerSend(){
	//ackvote for other
	for(auto fd : aliveNginxfd){
		string data;
		AckVote2Follower avf;
		avf.set_version(version[ENSURE]);//版本已经升级过了
		avf.set_nginxname(nginxName);
		avf.SerializeToString(&data);
		if(!nginxs[fd].WriteProto(AckVote2FollowerNo, data)){
			nginxs[fd].Addfd2Write();
		}
		else{
			nginxs[fd].Addfd2Read();
		}
	}
	LOG(DEBUG) << "AckVote2FollowerSend";
}

void DtbtNginx::SynchDataSend(){

}

void DtbtNginx::AckData2FollowerSend(){

}
/* check and send keepAlive to all Nginx */
void DtbtNginx::SendKeepAlive(){
	int curTime = time(0);
	int fd;
	for(vector<int>::iterator it = aliveNginxfd.begin(); it != aliveNginxfd.end();){
		fd = *it;
		/* check keepAlive before check lastActive */
		if(curTime - nginxs[fd].lastActive > nginxs[fd].ActiveInterval){
			/* check whether Leader */
			if(leaderName[ENSURE] == nginxs[fd].clientName){
				leaderName[ENSURE] = "";//no need for lock
			}
			it = aliveNginxfd.erase(it);
		}
		else{
			/* check keepAlive */
			if(curTime - nginxs[fd].lastKeepAlive > nginxs[fd].keepAliveInterval){
				/* alive */
				string data;
				KeepAlive ka;
				ka.SerializeToString(&data);
				if(!nginxs[aliveNginxfd[*it]].WriteProto(KeepAliveNo, data)){
					nginxs[fd].Addfd2Write();
				}
				else{
					nginxs[fd].Addfd2Read();
				}
			}
			++it;
		}
	}
}
/* 参数：
1.自己DtBtNginx编号 
2.配置文件位置
*/
int main(int argc, char **argv){
	if(argc != 2){
		LOG(ERROR) << "input 1.DtBtNginx编号";
		return 0;
	}
	DtbtNginx *dbNginx = Singleton<DtbtNginx>::getInstence();

	/* log init config files */
	el::Configurations conf("conf/log.conf");  
	el::Loggers::reconfigureAllLoggers(conf); 

	/* load DtbtNginx config files */
	dbNginx->ReadDtbtNginxConf(argv[1], "conf/DtbtNginx.conf");

	/* 启动一个进程池  */
	int idx = dbNginx->nginxName.find(' ');
	string ip(dbNginx->nginxName, 0, idx);
	string portStr(dbNginx->nginxName, idx + 1, dbNginx->nginxName.size());
	int port = atoi(portStr.c_str());
		Processpool *DtbiNginxProcesspool = Processpool::CreateProcesspool(ip, port, 1, true);//3.子进程个数
	if(DtbiNginxProcesspool){
		DtbiNginxProcesspool->run<Nginx>();
        delete DtbiNginxProcesspool;
	}
	return 0;
}