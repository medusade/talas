/**
 **********************************************************************
 * Copyright (c) 1988-2018 $organization$
 *
 * This software is provided by the author and contributors ``as is'' 
 * and any express or implied warranties, including, but not limited to, 
 * the implied warranties of merchantability and fitness for a particular 
 * purpose are disclaimed. In no event shall the author or contributors 
 * be liable for any direct, indirect, incidental, special, exemplary, 
 * or consequential damages (including, but not limited to, procurement 
 * of substitute goods or services; loss of use, data, or profits; or 
 * business interruption) however caused and on any theory of liability, 
 * whether in contract, strict liability, or tort (including negligence 
 * or otherwise) arising in any way out of the use of this software, 
 * even if advised of the possibility of such damage.
 *
 *   File: dump.h
 *
 * Author: $author$
 *   Date: 6/17/98, 2/11/2018
 **********************************************************************
 */
#ifndef DUMP_H
#define DUMP_H

#ifndef DUMP_COLS
#define DUMP_COLS 32
#endif

static void dump(const void *buff,unsigned long bytes)
{
    unsigned long i,j;

    for (j=0,i=0; i<bytes; i++)
    {
        if (j<DUMP_COLS) 
            j++;
        else 
        { 
            j=1; 
            printf("\n"); 
        }
        printf("%2.2x",((const unsigned char*)buff)[i]);
    }
    printf("\n");
}
static void dump0x(const void *buff,unsigned long bytes)
{
    unsigned long i,j;

    for (j=0,i=0; i<bytes; i++)
    {
        if (j<DUMP_COLS) 
            j++;
        else 
        { 
            j=1; 
            printf("\n"); 
        }
        printf("0x%2.2x,",((const unsigned char*)buff)[i]);
    }
    printf("\n");
}

#endif
