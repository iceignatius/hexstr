#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include "cmdopt.h"

//------------------------------------------------------------------------------
void cmdopts_load_defaults(cmdopts_t *conf)
{
    memset(conf, 0, sizeof(*conf));
}
//------------------------------------------------------------------------------
void cmdopts_load_args(cmdopts_t *conf, int argc, char *argv[])
{
    struct option longopts[] =
    {
        { "help"   , no_argument      , NULL, 'h' },
        { "output" , required_argument, NULL, 'o' },
        { "prefix" , required_argument, NULL, 'B' },
        { "postfix", required_argument, NULL, 'A' },
        { "count"  , no_argument      , NULL, 'c' },
        { NULL     , 0                , NULL,  0  }
    };

    int opt;
    int index;
    while( 0 <= ( opt = getopt_long(argc, argv, "ho:c", longopts, &index) ) )
    {
        switch( opt )
        {
        case 'o':
            conf->destfile = optarg;
            break;

        case 'B':
            conf->prefix = optarg;
            break;

        case 'A':
            conf->postfix = optarg;
            break;

        case 'c':
            conf->cntmode = true;
            break;

        case 'h':
        case '?':
            conf->needhelp = true;
            break;

        }
    }

    if( optind < argc )
        conf->command = argv[optind++];

    if( optind < argc )
        conf->srcfile = argv[optind++];

    if( optind < argc )
    {
        conf->needhelp = true;
        fprintf(stderr, "Unknown argument: %s\n", argv[optind]);
    }
}
//------------------------------------------------------------------------------
