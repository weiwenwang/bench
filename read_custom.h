#ifndef __READ_CUSTOM_
#define __READ_CUSTOM_

#include "common.h"

void readn(int sock, void *buf, int sum);

int readline(int sock, void *buf);

int get_respone_head_line(char *first_buf);

#endif