/*
 * Hexadecimal string converter.
 */
#ifndef _HEXCONV_H_
#define _HEXCONV_H_

#include <stdbool.h>

enum
{
    HEXCONV_ERR_SUCCESS = 0,
    HEXCONV_ERR_READ_FILE,
    HEXCONV_ERR_WRITE_FILE,
    HEXCONV_ERR_MEM_ALLOC,
    HEXCONV_ERR_INPUT_FORMAT,
};

static inline
const char* hexconv_errcode_to_str(int errcode)
{
    switch(errcode)
    {
    case HEXCONV_ERR_SUCCESS      :  return "Success.";
    case HEXCONV_ERR_READ_FILE    :  return "Cannot read source file!";
    case HEXCONV_ERR_WRITE_FILE   :  return "Cannot write destination file!";
    case HEXCONV_ERR_MEM_ALLOC    :  return "No more memory!";
    case HEXCONV_ERR_INPUT_FORMAT :  return "Input format error!";

    default :  return "Unknown failure!";

    }
}

int hexconv_convert_bin_to_str(const char *srcfile,
                               const char *destfile,
                               bool        cntmode,
                               const char *prefix,
                               const char *postfix);
int hexconv_convert_str_to_bin(const char *srcfile,
                               const char *destfile,
                               bool        cntmode);

#endif
