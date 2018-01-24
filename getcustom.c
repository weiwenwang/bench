#include "getcustom.h"

int getcustom(int argc, char *argv[], CON *con) {
    int opt;
    int option_index = 0;
    char *optstring = "t:p:u:type:d";
    static struct option long_options[] = {
            {"t",    required_argument, NULL, 't'},
            {"p",    no_argument,       NULL, 'p'},
            {"url",  optional_argument, NULL, 'u'},
            {"type", optional_argument, NULL, 'type'},
            {0, 0, 0,                         0}
    };

    while ((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
        switch (opt) {
            case 't':
                con->t = atoi(optarg);
                break;
            case 'p':
                con->p = atoi(optarg);
                break;
            case 'u':
                con->url = optarg;
                break;
            case 'type':
                con->type = optarg;
                break;
        }
    }

    return 0;
}



