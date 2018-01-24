#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include "getcustom.h"
#include "socket.h"
#include "read_custom.h"

char http_url[1024];
char *host;
char *source;
int port;
char *User_Aagent;
char *http_type;
int total;

char request_url[1024];
int request_length;

#define MAXLINE 204800

void build_require_string(CON *con) {
    http_type = "HTTP/1.1";
    User_Aagent = "User-Agent:Mozila/4.0(compatible;MSIE5.01;Window NT5.0)";

    // 处理请求方式
    int type_length = strlen(con->type);
    char *type;
    int i = 0;
    for (i; i < type_length; i++) {
        if (con->type[i] >= 97 && con->type[i] <= 122) {
            con->type[i] = con->type[i] - 32;
        }
    }
    type = con->type;
    total = con->t;
    // over

    // 请求地址
    int url_length = strlen(con->url);
    char dest[8] = {""};
    strncpy(dest, con->url, 7);
    if (strcmp(dest, "http://") != 0) {
        printf("url not begin with `http://`");
    }

    char *ii = strstr(con->url, "://") + 3;
    source = strstr(ii, "/");
    port = 80;
    int host_length = strlen(ii) - strlen(source);
    host = (char *) malloc(host_length);
    strncpy(host, ii, host_length);

    strcat(http_url, type);
    strcat(http_url, source);
    strcat(http_url, " HTTP/1.1");

    printf("----------------------------------------------------------------\n");
}

void append_request(char *ch) {
    strcat(request_url, ch);
    request_length += strlen(ch);
}

void handle_sigchld(int signo) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0) {
        sleep(1);
        printf("子进程退出");
    }
}

int main(int argc, char *argv[]) {
    CON con;
    getcustom(argc, argv, &con);

    build_require_string(&con);


    char read_buf[MAXLINE] = {0};

    char *CRLF = "\r\n";
    char *SPACE = " ";

    append_request(con.type);
    append_request(SPACE);
    append_request(source);
    append_request(SPACE);
    append_request(http_type);
    append_request(CRLF);
    append_request("Host:");
    append_request(host);
    append_request(CRLF);
    append_request(User_Aagent);
    append_request(CRLF);
    append_request(CRLF);

//    signal(SIGCHLD, handle_sigchld);

    struct timeval start, end;
    gettimeofday(&start, NULL);


    pid_t pid;
    int i = 0;
    for (i; i < con.p; i++) {
        int ppid;
        ppid = fork();
        if (ppid == 0) { // 子进程
            int sock = Socket(host, port); // 创建主动套接字
            while (total > 0) {
                write(sock, request_url, request_length);
                int read_int = readline(sock, read_buf);
                total -= 1;
            }
            exit(EXIT_SUCCESS);
        }

    }
    int status;
    while ((pid = wait(&status)) > 0) {
        printf("进程退出 pid=%d\n", pid);
    }

    gettimeofday(&end, NULL);
    suseconds_t msec = end.tv_usec - start.tv_usec;
    time_t sec = end.tv_sec - start.tv_sec;

    printf("REPORT: \n");
    printf("    %d clients, %d progresses, running %ld.%u sec.\n", con.t, con.p, sec, msec);


    printf("\n\n");
//Benchmarking: GET http://360zhanghao.com/index.php
//
//500 clients, running 10 sec.     //说明 500次并发
//
//Speed=9438 pages/min, 1433025 bytes/sec.    //每秒钟传输数据量1433025bytes
//
//Requests: 1573 susceed, 0 failed.     // 0次失败



//    printf("con t is %d \n", con.t);
//    printf("con p is %d \n", con.p);
//    printf("con url is %s \n", con.url);
//    printf("con type is %s \n", con.type);

    return 0;
}
