/*
 * Command option parser.
 */
#ifndef _CMDOPT_H_
#define _CMDOPT_H_

#include <stdbool.h>

typedef struct cmdopts_t
{
    bool  needhelp;
    bool  cntmode;
    char *command;
    char *srcfile;
    char *destfile;
    char *prefix;
    char *postfix;
} cmdopts_t;

void cmdopts_load_defaults(cmdopts_t *conf);
void cmdopts_load_args(cmdopts_t *conf, int argc, char *argv[]);

#endif
