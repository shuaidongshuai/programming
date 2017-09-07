#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include "locker.h"

class http_conn
{
public:
	/*文件名最大长度*/
    static const int FILENAME_LEN = 200;
	/*读写缓冲区大小*/
    static const int READ_BUFFER_SIZE = 2048;
    static const int WRITE_BUFFER_SIZE = 1024;
	/*各种请求*/
    enum METHOD { GET = 0, POST, HEAD, PUT, DELETE, TRACE, OPTIONS, CONNECT, PATCH };
    enum CHECK_STATE { CHECK_STATE_REQUESTLINE = 0, CHECK_STATE_HEADER, CHECK_STATE_CONTENT };//主状态机，正在分析请求行，正在分析头部字段，内容
    enum HTTP_CODE { NO_REQUEST, //请求不完整，需要继续读客户数据
					GET_REQUEST, //得到一个完整的客户请求
					BAD_REQUEST, //请求语法错误
					NO_RESOURCE, //没有资源
					FORBIDDEN_REQUEST, //客户端对资源没有足够的访问权限
					FILE_REQUEST, //文件请求
					INTERNAL_ERROR, //服务器内部错误
					CLOSED_CONNECTION /*客户端关闭连接*/};
    enum LINE_STATUS { LINE_OK = 0, LINE_BAD, LINE_OPEN };//从状态机。读取状态：1.读到完整行 2.行出错 3.数据不完整

public:
    http_conn(){}
    ~http_conn(){}
public:
    void init( int sockfd, const sockaddr_in& addr );
    void close_conn( bool real_close = true );
	/*处理客户请求*/
    void process();
	/*非阻塞读写*/
    bool read();
    bool write();

private:
    void init();
	/*填充HTTP应答*/
    bool process_write( HTTP_CODE ret );

	/*解析http请求*/
    HTTP_CODE process_read();
    HTTP_CODE parse_request_line( char* text );
    HTTP_CODE parse_headers( char* text );
    HTTP_CODE parse_content( char* text );
    HTTP_CODE do_request();
    char* get_line() { return m_read_buf + m_start_line; }
    LINE_STATUS parse_line();

    void unmap();
    bool add_response( const char* format, ... );
    bool add_content( const char* content );
    bool add_status_line( int status, const char* title );
    bool add_headers( int content_length );
    bool add_content_length( int content_length );
    bool add_linger();
    bool add_blank_line();

public:
    static int m_epollfd;
	/*统计用户数量*/
    static int m_user_count;

private:
    int m_sockfd;
    sockaddr_in m_address;
	/*读缓冲区*/
    char m_read_buf[ READ_BUFFER_SIZE ];
	/*读的位置(最后一个字节的下一个位置)*/
    int m_read_idx;
	/*正在分析的字符串在读取缓冲区中的位置*/
    int m_checked_idx;
	/*正在解析的行的起始位置*/
    int m_start_line;
	/*写缓冲区*/
    char m_write_buf[ WRITE_BUFFER_SIZE ];
    int m_write_idx;
	
	/*主状态机当前所处的状态*/
    CHECK_STATE m_check_state;
    METHOD m_method;
	/*请求的目标文件路径*/
    char m_real_file[ FILENAME_LEN ];
	/*文件名*/
    char* m_url;
	/*http协议号*/
    char* m_version;
	/*主机名*/
    char* m_host;
	/*请求消息体长度*/
    int m_content_length;
	/*http是否保持连接*/
    bool m_linger;

	/*客户请求的目标文件被mmap到内存中的起始位置*/
    char* m_file_address;
    /*目标文件状态，是否是目录，是否可读，文件大小*/
	struct stat m_file_stat;
    /*采用writev来写*/
	struct iovec m_iv[2];
	int m_iv_count;
};

#endif
