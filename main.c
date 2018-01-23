#include "getcustom.h"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "socket.h"

char http_url[1024];
#define MAXLINE 204800

void build_require_string(CON *con) {
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
    char *source = strstr(i, "/");

    int host_length = strlen(i) - strlen(source);
    char *host = (char *) malloc(host_length);
    strncpy(host, i, host_length);


//    printf("source is %s \n", source);
//    printf("host is %s \n", host);

    strcat(http_url, type);
    strcat(http_url, source);
    strcat(http_url, " HTTP/1.1");
//    printf("http_url is %s \n", http_url);


    printf("----------------------------------------------------------------\n");
}

int get_respone_head_line(char *first_buf) {
    int first_sum = strlen(first_buf);
    for (int i = 0; i < first_sum - 3; i++) {
        if (first_buf[i] == 13 &&
            first_buf[i + 1] == 10 &&
            first_buf[i + 2] == 13 &&
            first_buf[i + 3] == 10) {
            return i + 4;
        }
    }
    return 0;

}

void readn(int sock, void *buf, int sum) {
    char *bufp = (char *) buf;
    int left_sum = sum;
    int max_size = 1024;
    while (left_sum > 0) {
        if (left_sum < max_size) {
            max_size = left_sum;
        }
        int read_sum = read(sock, bufp, max_size);
        bufp += read_sum;
        left_sum = left_sum - read_sum;
    }
}

int readline(int sock, void *buf) {
    int first_size = 400;
    int second_size = 1024;
    char *bufp = (char *) buf;
    char second_buff[second_size];

    int first_sum = read(sock, bufp, first_size);

    int left_sum = 0;
    char *i = strstr(bufp, "Content-Length");
    char dest[16] = {""};
    strncpy(dest, i, 15);

    if (strcmp(dest, "Content-Length:") != 0) {
        printf("url not begin with `Content-Length:`");
    }
    int j = strlen("Content-Length: ");
    int num = atoi(&i[j]);


    int head_line = get_respone_head_line(bufp);
    if (head_line == 0) {
        printf("get_respone_head_line is error\n");
        exit(0);
    }

    num = num + head_line;
    left_sum = num - first_sum;

    bufp += first_sum;

    if (left_sum == 0) {
        return 0;
    } else {
        readn(sock, buf, left_sum);
    }
    return 0;
}


int main(int argc, char *argv[]) {
    CON con;

    getcustom(argc, argv, &con);

    build_require_string(&con);

    //创建套接字
    char *host = "192.168.3.45";
    int sock = Socket(host, 80); // 创建主动套接字

    char read_buf[MAXLINE] = {0};
    char send_buf[170] = "GET /2017/07/07/hello-world/index.html HTTP/1.1\r\nHost:192.168.3.45\r\nUser-Agent:Mozila/4.0(compatible;MSIE5.01;Window NT5.0)\r\nAccept-Language:zh-cn\r\nUser-Agent:goBench\r\n\r\n";

    write(sock, send_buf, sizeof(send_buf));
    int read_int = readline(sock, read_buf);
    printf("read_buf is :\n%s", read_buf);



//    printf("get is %d\n", read_int);
//    printf("get is %s\n", read_buf);

//    printf("con t is %d \n", con.t);
//    printf("con c is %d \n", con.c);
//    printf("con url is %s \n", con.url);
//    printf("con type is %s \n", con.type);

    return 0;
}