#include "Nginx.h"
#include "DtbtNginx.h"
#include "protoCallBack.h"
#include "inNginx.pb.h"
#include "easylogging++.h"
#include "Singleton.h"

/* 默认et模式 */
Nginx::Nginx(int readBufSize)
			:events(EPOLLET), eStatus(0), readBufSize(readBufSize), readIdx(0),
			writeIdx(0),writeLen(0),writeBufSize(1024),
			sockfd(-1), keepAliveInterval(1), ActiveInterval(60){
	dbNginx = Singleton<DtbtNginx>::getInstence();
	readBuf = new char[readBufSize];
	writeBuf = new char[writeBufSize];
	/* 注册回调函数 */
	callBack[VoteNo] = &Nginx::VoteRcve;
	callBack[AckVote2LeaderNo] = &Nginx::AckVote2LeaderRcve;
	callBack[AckVote2FollowerNo] = &Nginx::AckVote2FollowerRcve;

	callBack[SynchDataNo] = &Nginx::SynchDataRcve;
	callBack[AckData2LeaderNo] = &Nginx::AckData2LeaderRcve;
	callBack[AckData2FollowerNo] = &Nginx::AckData2FollowerRcve;

	callBack[KeepAliveNo] = &Nginx::KeepAliveRcve;
}

Nginx::~Nginx(){
	delete readBuf;
}

void Nginx::SetReadBuf(int size){
	char *newBuf = new char[size];
	char *temp = readBuf;
	readBuf = newBuf;
	readBufSize = size;
	delete temp;
}
//所有数据都是 cmd+len+protobuf  要按照这个来读 cmd 和 len 都是 int
//返回false说明没有读完，接着读。或者已经关闭socket(反正就是不处理读到的消息)  true说明数据完整
bool Nginx::Read(){
	lastActive = time(0);//记录活跃的时间

	int n, nread = 0;//1.一次读到的size 2.一共读到的大小 3.最多读10次(避免网络丢包)
	//读 cmd 和 len 只有小于8Byte才去读它
	if(readIdx < 2 * sizeof(int)){
		nread = readIdx;
		while ((n = read(sockfd, readBuf + nread, 2 * sizeof(int) - nread)) > 0) {
			if (n == -1) {
				if(errno == EAGAIN)
					break;
				LOG(INFO) << "客服端异常退出";
				break;
			}
			if(n == 0) {
				LOG(INFO) << "客服端正常退出";
				break;
			}
			nread += n;
		}
		readIdx = nread;
		if(n == -1 || n == 0){
			if(errno == EAGAIN)
				return false;
			CloseSocket(sockfd);
			return false;
		}
	}
	//读protobuf
	int cmd = *(int *)readBuf;
	int len = *(int *)(readBuf + sizeof(int));
	nread = 0;
	while ((n = read(sockfd, readBuf + readIdx, len - nread)) > 0) {
		if (n == -1) {
			if(errno == EAGAIN)
				break;
			LOG(INFO) << "客服端异常退出";
			break;
		}
		if(n == 0) {
			LOG(INFO) << "客服端正常退出";
			break;
		}
		nread += n;
	}
	readIdx += nread;
	if(n == -1 || n == 0){
		if(errno == EAGAIN)
			return false;
		CloseSocket(sockfd);
		return false;
	}
	LOG(DEBUG) << "读到：" << readBuf << "---" << readIdx << "字节";
	//执行回调函数
	(this->*(callBack[cmd]))(readBuf + 2 * sizeof(int));
}
/* 还需要监听就返回false */
bool Nginx::Write(){
	int n;
	while (1){
		n = write(sockfd, writeBuf + writeIdx, writeLen - writeIdx);
		if ( n <= -1 ) {
			if( errno == EAGAIN ) {
				LOG(DEBUG) << "当前不可写，继续监听写事件";
				return false;
			}
			LOG(INFO) << "发送失败";
			break;
		}
		writeIdx += n;
		if(writeIdx >= writeLen)
			break;
	}
	LOG(DEBUG) << "写了:" << writeBuf << "-" << writeLen << "字节";
	return true;
}
/* 发送protobuf协议 加上包头(cmd + len) */
bool Nginx::WriteProto(int cmd, string data){
	int len = data.size();
	if(2 * sizeof(int) + len > writeBufSize){
		delete writeBuf;
		writeBuf = new char[len + 2 * sizeof(int)];
	}
	strncpy(writeBuf, (char *)&cmd, sizeof(int));
	strncpy(writeBuf + sizeof(int), (char *)&len, sizeof(int));
	strcpy(writeBuf + 2 * sizeof(int), data.c_str());
	return Write();
}
bool Nginx::ReadWithoutCmd(){

}
//收到投票--Leader-Candiate-Follower
void Nginx::VoteRcve(char *proto){
	if(!proto){
		LOG(ERROR) << "VoteFunc nullptr";
		return;
	}
	string data(proto, readIdx - 2 * sizeof(int));
	Vote vote;
	bool parseRes = vote.ParseFromString(data);
	if(!parseRes){
		LOG(ERROR) << "VoteFunc parseRes is false";
		return;
	}
	int ver = vote.version();
	string nginxName = vote.nginxname();
	//判断自己的状态只有follower才能为别人投票 && 新版本号比自己老版本大
	if(dbNginx->status == FOLLOWER && ver > dbNginx->version[ENSURE]){
		dbNginx->version[SUBMIT] = ver;
		dbNginx->leaderName[SUBMIT] = nginxName;
		//发ack
		string data;
		AckVote2Leader av2l;
		av2l.set_version(ver);
		av2l.set_nginxname(nginxName);
		av2l.SerializeToString(&data);
		if( !WriteProto(AckVote2LeaderNo, data) ){
			Addfd2Write();
		}
		else{
			Addfd2Read();
		}
		LOG(DEBUG) << "vote for " << nginxName;
	}
}
//收到投票响应1
void Nginx::AckVote2LeaderRcve(char *proto){
	if(!proto){
		LOG(ERROR) << "VoteFunc nullptr";
		return;
	}
	string data(proto, readIdx - 2 * sizeof(int));
	AckVote2Leader av2l;
	bool parseRes = av2l.ParseFromString(data);
	if(!parseRes){
		LOG(ERROR) << "VoteFunc parseRes is false";
		return;
	}
	int ver = av2l.version();
	string nginxName = av2l.nginxname();
	if(ver != dbNginx->version[ENSURE] + 1 || nginxName != dbNginx->nginxName){
		LOG(ERROR) << "VoteAckRcve ver:" << ver << " nginxName:" << nginxName;
		return;
	}
	//如果票数大于一半  自己变为Leader
	if(dbNginx->voteNum > dbNginx->allNginxNum / 2){
		dbNginx->status = LEADER;
		++dbNginx->version[ENSURE];
		//给所有节点发送自己是Leader信息
		dbNginx->AckVote2FollowerSend();
		LOG(DEBUG) << nginxName << " 变为Leader";
	}
}
//收到投票响应2
void Nginx::AckVote2FollowerRcve(char *proto){
	if(!proto){
		LOG(ERROR) << "VoteFunc nullptr";
		return;
	}
	string data(proto, readIdx - 2 * sizeof(int));
	AckVote2Follower av2f;
	bool parseRes = av2f.ParseFromString(data);
	if(!parseRes){
		LOG(ERROR) << "VoteFunc parseRes is false";
		return;
	}
	int ver = av2f.version();
	string nginxName = av2f.nginxname();
	if(ver == dbNginx->version[SUBMIT] && nginxName == dbNginx->leaderName[SUBMIT]){
		//说明Leader已经选出来了
		dbNginx->version[ENSURE] = ver;
		dbNginx->leaderName[ENSURE] = nginxName;
		dbNginx->status = FOLLOWER;
	}
}
/* 收到同步数据 */
void Nginx::SynchDataRcve(char *proto){
	if(!proto){
		LOG(ERROR) << "VoteFunc nullptr";
		return;
	}
	string data(proto, readIdx - 2 * sizeof(int));
	AckData2Leader ad2l;
	bool parseRes = ad2l.ParseFromString(data);
	if(!parseRes){
		LOG(ERROR) << "VoteFunc parseRes is false";
		return;
	}
}
void Nginx::AckData2LeaderRcve(char *proto){
	if(!proto){
		LOG(ERROR) << "VoteFunc nullptr";
		return;
	}
	string data(proto, readIdx - 2 * sizeof(int));
	AckData2Leader ad2l;
	bool parseRes = ad2l.ParseFromString(data);
	if(!parseRes){
		LOG(ERROR) << "VoteFunc parseRes is false";
		return;
	}
}
void Nginx::AckData2FollowerRcve(char *proto){
	if(!proto){
		LOG(ERROR) << "AckData2Follower nullptr";
		return;
	}
}

void Nginx::KeepAliveRcve(char *proto){
	if(!proto){
		LOG(ERROR) << "KeepAliveRcve nullptr";
		return;
	}
	lastKeepAlive = time(0);
	lastActive = lastKeepAlive;
}

int Nginx::SetNoBlocking(int fd) {
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	return fcntl(fd, F_SETFL, new_option);//如果出错，所有命令都返回-1
}

void Nginx::Addfd2Read() {
	if(SetNoBlocking(sockfd) < 0) {
		LOG(WARNING) << "SetNoBlocking 失败 sockfd = " << sockfd;
		return;
	}
	epoll_event event;
	int op;
	//如果已经在epoll里了，把加 变成 修改
	if(!eStatus) {
		op = EPOLL_CTL_ADD;
		event.data.fd = sockfd;
		event.data.ptr = this;
	}
	else {
		op = EPOLL_CTL_MOD;
	}
	event.events = EPOLLIN | EPOLLONESHOT | EPOLLRDHUP | events;
	epoll_ctl(epollfd, op, sockfd, &event);

	lastActive = time(0);
}
void Nginx::Addfd2Write() {
	if(SetNoBlocking(sockfd) < 0) {
		LOG(WARNING) << "SetNoBlocking 失败 sockfd = " << sockfd;
		return;
	}
	epoll_event event;
	int op;
	if(!eStatus) {
		op = EPOLL_CTL_ADD;
		event.data.fd = sockfd;
		event.data.ptr = this;
	}
	else {
		op = EPOLL_CTL_MOD;
	}
	event.events = EPOLLOUT | EPOLLONESHOT | EPOLLRDHUP | events;
	epoll_ctl(epollfd, op, sockfd, &event);

	lastActive = time(0);
}

void Nginx::Removefd() {
	epoll_ctl(epollfd, EPOLL_CTL_DEL, sockfd, NULL);
	sockfd = -1;
	eStatus = 0;
	readIdx = 0;
	CloseSocket(sockfd);
}

void Nginx::CloseSocket(int sockfd){
	close(sockfd);
	sockfd = -1;
	eStatus = 0;
	lastActive = 0;
	lastKeepAlive = 0;
	readIdx = 0;
	writeIdx = 0;
	writeLen = 0;
}