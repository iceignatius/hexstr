#include <stdio.h>
#include <gen/jmpbk.h>
#include "cmddata.h"

//------------------------------------------------------------------------------
bool cmddata_read(mem_t *mem, const char *filename)
{
    mem_clear(mem);

    FILE *file = NULL;

    bool res;
    JMPBK_BEGIN
    {
        if( filename && !( file = fopen(filename, "rb") ) )
        {
            fprintf(stderr, "ERROR : Open file failed : %s\n", filename);
            JMPBK_THROW(0);
        }

        FILE *stream = file ? file : stdin;

        while( !feof(stream) )
        {
            char buf[1024];
            size_t readsz = fread(buf, 1, sizeof(buf), stream);
            if( !mem_append(mem, buf, readsz) )
            {
                fprintf(stderr, "ERROR : File IO error!\n");
                JMPBK_THROW(0);
            }
        }
    }
    JMPBK_FINAL
    {
        res = !JMPBK_ERRCODE;
    }
    JMPBK_END

    if( file ) fclose(file);

    return res;
}
//------------------------------------------------------------------------------
bool cmddata_write(const mem_t *mem, const char *filename)
{
    FILE *file = NULL;

    bool res;
    JMPBK_BEGIN
    {
        if( filename && !( file = fopen(filename, "wb") ) )
        {
            fprintf(stderr, "ERROR : Open file failed : %s\n", filename);
            JMPBK_THROW(0);
        }

        FILE *stream = file ? file : stdout;

        if( mem->size != fwrite(mem->buf, 1, mem->size, stream) )
        {
            fprintf(stderr, "ERROR : File IO error!\n");
            JMPBK_THROW(0);
        }
    }
    JMPBK_FINAL
    {
        res = !JMPBK_ERRCODE;
    }
    JMPBK_END

    if( file ) fclose(file);

    return res;
}
//------------------------------------------------------------------------------
