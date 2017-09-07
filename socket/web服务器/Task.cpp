

class Task
{
private:  
    int sockfd;    //连接的描述符  
private:  
    //错误返回函数  
    void response_error(char method[], char res[], char why[])  
    {  
		char body[MAXBUFFER];  //消息体  
		char content[MAXLINE]; //请求头  
		//设置消息体  
		sprintf(body, "<html><title>Tinyhttpd Error</title>");  
		sprintf(body, "%s<body bgcolor=""yellow"">\r\n", body);  
		sprintf(body, "%s %s\r\n", body, res);  
		sprintf(body, "%s <p>%s: %s", body, method, why);  
		sprintf(body, "%s<hr><h3>The Tiny Web Server<h3></body>", body);  
	  
		//设置请求头  
		sprintf(content, "HTTP/1.1 %s\r\n", method);  
		sprintf(content, "%sContent-type: text/html\r\n", content);  
		sprintf(content, "%sContent-length: %d\r\n", content,   
						(int)strlen(body));  
		sprintf(content, "%sEncoding:UTF-8\r\n\r\n", content);  
		write(sockfd, content, strlen(content));  
		write(sockfd, body, strlen(body));  
    }
	 //发送请求文件函数  
    void response_file(char file[], off_t size)  
    {
		char content[MAXLINE], buf[MAXLINE];  
		int filefd = open(file, O_RDONLY);  
		//设置请求头  
		sprintf(content, "HTTP/1.1 %s\r\n", "GET");  
		sprintf(content, "%sContent-type: text/html\r\n", content);  
		sprintf(content, "%sContent-length: %d\r\n", content,   
						(int)size);  
		sprintf(content, "%sEncoding:UTF-8\r\n\r\n", content);  
		//发送请求头  
		write(sockfd, content, strlen(content));  
		//使用“零拷贝”发送文件  
		sendfile(sockfd, filefd, 0, size);  
	//  int ret;   //读取文件，再发送  
	//  while((ret = read(filefd, buf, MAXLINE)) > 0)  
	//      write(sockfd, buf, ret);  
    }
	//动态请求函数  
    void response_dynamic(char file[], char argv[])  
    {  
		if(fork() == 0)  /*创建子进程执行对应的子程序，多线程中，创建子进程， 
		只有当前线程会被复制，其他线程就“不见了”，这正符合我们的要求， 
		而且fork后执行execl，程序被进程被重新加载*/  
		{  
			dup2(sockfd, STDOUT_FILENO);    
			//将标准输出重定向到sockfd,将子程序输出内容写到客户端去。  
			execl(file, argv); //执行子程序  
		}
		wait(NULL);  
    }  
      
    void parse_url(char Head[])   //解析URL中第一行中的请求方法和文件  
    {  
		char method[8];  //请求方法  
		char file[20];    //请求文件  
		int i = 0, j = 0;  
		while(Head[i] != ' ' && Head[i] != '\0')  //获取请求方法  
		{  
			method[j++] = Head[i++];  
		}  
		method[j] = '\0';  
		++i;  
		j = 0;  
		while(Head[i] != ' ' && Head[i] != '\0')  //获取请求文件  
		{  
			file[j++] = Head[i++];  
		}  
		file[j] = '\0';  
	  
		//判断是否为GET 请求，不是，则返回出错信息  
		if(strcasecmp(method, "GET"))  
		{  
			response_error(method, "501", "Httpd does not implement "  
				"this method");  
			return;  
		}  
		bool is_dynamic = false;  
		char argv[20];  
		i = 0;  
		//查找是否有？号  
		while(file[i] != '?' && file[i] != '\0')  
			++i;  
		if(file[i] == '?')  
		{//有?号，则是动态请求  
			j = i; ++i;  
			int k = 0;  
			while(file[i] != '\0')  //分离参数和文件名  
			argv[k++] = file[i++];  
			argv[k] = '\0';  
			file[j] = '\0';  
			//printf("%s  %s\n", file, argv);  
			is_dynamic = true;  
		}  
		struct stat buf;  
		char temp[50];  
		strcpy(temp, PATH);  
		strcat(temp, file);  
		int ret = stat(temp, &buf);  
		if(ret < 0)//判断文件是否存在  
		{  
			response_error(method, "404", "Httpd does not have this file");  
			return;  
		}  
		if(S_ISDIR(buf.st_mode))  //文件为文件夹  
		{  
			response_error(method, "404", "The file is a Folder");  
			return;  
		}  
		//发送文件  
		if(!is_dynamic)  
			response_file(temp, buf.st_size);  
		else  
			response_dynamic(temp, argv);  
    }  
  
public:  
    task(int sock) : sockfd(sock)   //构造函数  
    {}
    ~task(){}   //析构  
    void doit() //处理请求函数  
    {  
		char buffer[MAXBUFFER];   //请求的信息  
		char Head[50];            //第一行的信息  
Read:   int getByte = read(sockfd, buffer, MAXBUFFER);  //读取请求信息  
		if(getByte > 0)   //读取成功  
		{
			buffer[getByte] = '\0';  
			int i = 0;  
			while(buffer[i] != '\n' && buffer[i] != '\0')  //获取第一行请求信息  
			{
				Head[i] = buffer[i];  
				++i;  
			}
			Head[i] = '\0';  
			printf("%s\n", Head);  
			parse_url(Head);  //解析请求的信息  
		}  
		else if(getByte == 0)  //对方关闭连接  
			close(sockfd);  
		else     //读取出错，重新读取  
		{
			goto Read;  
		}
		close(sockfd);  
    }
};
int main(int argc, char *argv[])  
{  
    if(argc != 2)  
    {  
    printf("usage : %s port\n", argv[0]);  
    return 1;  
    }  
  
    int sockfd, connfd;  
    struct sockaddr_in servaddr, client;  
    int port = atoi(argv[1]);  //获取端口  
    //设置服务端的sockaddr_in  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port);  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    //创建socket  
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    if(sockfd < 0)  
    {  
    printf("socket error\n");  
    return 1;  
    }  
    //绑定  
    int ret = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));  
    if(ret < 0)  
    {  
    printf("bind error\n");  
    return 1;  
    }  
    //监听  
    ret = listen(sockfd, 10);  
    if(ret < 0)  
    {  
    printf("listen error\n");  
    return 1;  
    }  
    //创建线程池  
    threadpool<task> pool(10, 15);  
    pool.start();  //线程池开始运行  
  
    while(1)  
    {  
    socklen_t len = sizeof(client);  
    //接受连接  
    connfd = accept(sockfd, (struct sockaddr *)&client, &len);  
    task *ta = new task(connfd);  
    //向线程池添加任务  
    while(!pool.append_task(ta))  
        ;  
    }  
    return 0;  
}  