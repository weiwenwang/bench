#include "getcustom.h"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "socket.h"
#include "read_custom.h"

char http_url[1024];
char *host;
char *source;
int port;
char *User_Aagent;
char *http_type;

char request_url[1024];
int request_length;

#define MAXLINE 204800

void build_require_string(CON *con) {
    http_type = "HTTP/1.1";
    User_Aagent = "User-Agent:Mozila/4.0(compatible;MSIE5.01;Window NT5.0)";

    // 处理请求方式
    int type_length = strlen(con->type);
    char *type;
    for (int i = 0; i < type_length; i++) {
        if (con->type[i] >= 97 && con->type[i] <= 122) {
            con->type[i] = con->type[i] - 32;
        }
    }
    type = con->type;
    // over

    // 请求地址
    int url_length = strlen(con->url);
    char dest[8] = {""};
    strncpy(dest, con->url, 7);
    if (strcmp(dest, "http://") != 0) {
        printf("url not begin with `http://`");
    }

    char *i = strstr(con->url, "://") + 3;
    source = strstr(i, "/");
    port = 80;
    int host_length = strlen(i) - strlen(source);
    host = (char *) malloc(host_length);
    strncpy(host, i, host_length);

    strcat(http_url, type);
    strcat(http_url, source);
    strcat(http_url, " HTTP/1.1");

    printf("----------------------------------------------------------------\n");
}

void append_request(char *ch) {
    strcat(request_url, ch);
    request_length += strlen(ch);
}

int main(int argc, char *argv[]) {
    CON con;
    getcustom(argc, argv, &con);

    build_require_string(&con);

    //创建套接字
    int sock = Socket(host, port); // 创建主动套接字

    char read_buf[MAXLINE] = {0};

    char *CRLF = "\r\n";
    char *SPACE = " ";

    append_request(con.type);
    append_request(SPACE);
    append_request(source);
    append_request(SPACE);
    append_request(http_type);
    append_request(CRLF);
    append_request("Host:192.168.3.45");
    append_request(CRLF);
    append_request(User_Aagent);
    append_request(CRLF);
    append_request(CRLF);


    write(sock, request_url, request_length);
    int read_int = readline(sock, read_buf);
    printf("read_buf is :\n%s", read_buf);




//    printf("con t is %d \n", con.t);
//    printf("con c is %d \n", con.c);
//    printf("con url is %s \n", con.url);
//    printf("con type is %s \n", con.type);

    return 0;
}