#include <string.h>
#include <stdio.h>
#include "cmdopt.h"
#include "hexconv.h"

void print_help(void)
{
    printf("Hexadecimal string converter.\n");
    printf("Usage: hexstr <command> [options] [file]\n");
    printf("\n");
    printf("Command:\n");
    printf("  tobin                  Convert hexadecimal string to binary data.\n");
    printf("  tostr                  Convert binary data to hexadecimal string.\n");
    printf("\n");
    printf("Options:\n");
    printf("  -h, --help             Print help message.\n");
    printf("  -o, --output FILE      Set the output file, or the output will be\n");
    printf("                         printed to standard output by default.\n");
    printf("      --prefix STR       Prefix to each bytes of string output.\n");
    printf("                         This option will be effected for binary to string\n");
    printf("                         command only.\n");
    printf("      --postfix STR      Postfix to each bytes of string output.\n");
    printf("                         This option will be effected for binary to string\n");
    printf("                         command only.\n");
    printf("  -c, --count            Count how many bytes or characters will be generated\n");
    printf("                         for the convert result.\n");
    printf("\n");
    printf("File:\n");
    printf("  The source file to read, or data will be read from the standard input by\n");
    printf("  default.\n");
}

int main(int argc, char *argv[])
{
    cmdopts_t opts;
    cmdopts_load_defaults(&opts);
    cmdopts_load_args(&opts, argc, argv);
    if( opts.needhelp )
    {
        print_help();
        return 0;
    }

    if( !opts.command )
    {
        fprintf(stderr, "ERROR: No command input!\n");
        print_help();
        return -1;
    }
    else if( 0 == strcmp(opts.command, "tobin") )
    {
        return hexconv_convert_str_to_bin(opts.srcfile,
                                          opts.destfile,
                                          opts.cntmode);
    }
    else if( 0 ==strcmp(opts.command, "tostr") )
    {
        return hexconv_convert_bin_to_str(opts.srcfile,
                                          opts.destfile,
                                          opts.cntmode,
                                          opts.prefix,
                                          opts.postfix);
    }
    else
    {
        fprintf(stderr, "ERROR: Unknown command: %s\n", opts.command);
        print_help();
        return -1;
    }

    return 0;
}
