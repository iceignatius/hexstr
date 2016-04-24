#include <string.h>
#include <stdio.h>
#include <gen/jmpbk.h>
#include <gen/string.h>
#include "cmddata.h"
#include "hexconv.h"

//------------------------------------------------------------------------------
int hexconv_convert_bin_to_str(const char *srcfile,
                               const char *destfile,
                               bool        cntmode,
                               const char *prefix,
                               const char *postfix)
{
    mem_t src;
    mem_init(&src, 0);

    mem_t dest;
    mem_init(&dest, 0);

    int res;
    JMPBK_BEGIN
    {
        prefix  = prefix  ? prefix  : "";
        postfix = postfix ? postfix : "";

        if( !cmddata_read(&src, false, srcfile) ) JMPBK_THROW(HEXCONV_ERR_READ_FILE);

        size_t sizeneed = src.size * ( strlen(prefix) + 2 + strlen(postfix) ) + 1;
        if( !mem_resize(&dest, sizeneed) ) JMPBK_THROW(HEXCONV_ERR_MEM_ALLOC);

        size_t count = str_bin_to_hexstr((char*)dest.buf,
                                         dest.size,
                                         src.buf,
                                         src.size,
                                         prefix,
                                         postfix);
        if( !count ) JMPBK_THROW(HEXCONV_ERR_INPUT_FORMAT);
        count = strlen((char*)dest.buf);

        if( cntmode )
        {
            char str[64];
            snprintf(str, sizeof(str), "%zu\n", count);
            if( !mem_import(&dest, str, strlen(str)) ) JMPBK_THROW(HEXCONV_ERR_MEM_ALLOC);
        }

        if( !cmddata_write(&dest, true, destfile) ) JMPBK_THROW(HEXCONV_ERR_WRITE_FILE);
    }
    JMPBK_CATCH_ALL
    {
        fprintf(stderr, "ERROR: %s\n", hexconv_errcode_to_str(JMPBK_ERRCODE));
    }
    JMPBK_FINAL
    {
        res = JMPBK_ERRCODE;
    }
    JMPBK_END

    mem_deinit(&dest);
    mem_deinit(&src);

    return res;
}
//------------------------------------------------------------------------------
int hexconv_convert_str_to_bin(const char *srcfile,
                               const char *destfile,
                               bool        cntmode)
{
    mem_t src;
    mem_init(&src, 0);

    mem_t dest;
    mem_init(&dest, 0);

    int res;
    JMPBK_BEGIN
    {
        if( !cmddata_read(&src, true, srcfile) ) JMPBK_THROW(HEXCONV_ERR_READ_FILE);

        if( !mem_resize(&dest, src.size) ) JMPBK_THROW(HEXCONV_ERR_MEM_ALLOC);
        size_t count = str_hexstr_to_bin(dest.buf, dest.size, (char*)src.buf, true);
        if( !count ) JMPBK_THROW(HEXCONV_ERR_INPUT_FORMAT);
        if( !mem_resize(&dest, count) ) JMPBK_THROW(HEXCONV_ERR_MEM_ALLOC);

        if( cntmode )
        {
            char str[64];
            snprintf(str, sizeof(str), "%zu\n", count);
            if( !mem_import(&dest, str, strlen(str)) ) JMPBK_THROW(HEXCONV_ERR_MEM_ALLOC);
        }

        if( !cmddata_write(&dest, false, destfile) ) JMPBK_THROW(HEXCONV_ERR_WRITE_FILE);
    }
    JMPBK_CATCH_ALL
    {
        fprintf(stderr, "ERROR: %s\n", hexconv_errcode_to_str(JMPBK_ERRCODE));
    }
    JMPBK_FINAL
    {
        res = JMPBK_ERRCODE;
    }
    JMPBK_END

    mem_deinit(&dest);
    mem_deinit(&src);

    return res;
}
//------------------------------------------------------------------------------
