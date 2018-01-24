#include "read_custom.h"

int get_respone_head_line(char *first_buf) {
    int first_sum = strlen(first_buf);
    for (int i = 0; i < first_sum - 3; i++) {
        if (first_buf[i] == 13 &&
            first_buf[i + 1] == 10 &&
            first_buf[i + 2] == 13 &&
            first_buf[i + 3] == 10) {
            // 请求头包含结束符\r\n\r\n
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
    char *bufp = (char *) buf;

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
    return num;
}