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
 *   File: dbdump.h
 *
 * Author: $author$
 *   Date: 6/17/98, 2/11/2018
 **********************************************************************
 */
#ifndef DBDUMP_H
#define DBDUMP_H

#ifndef DBDUMP_COLS
#define DBDUMP_COLS 32
#endif

#ifndef dbdump
#ifndef DBPRINTF
#define dbset(buff,val,bytes)
#define dbdump(buff,bytes)
#else /* ndef DBPRINTF */
#define dbset _dbset
#define dbdump _dbdump
#ifndef _dbdump
static void _dbset(void *buff,unsigned char val,unsigned long bytes)
{
    unsigned long i;

    for (i=0; i<bytes; i++)
        ((unsigned char*)buff)[i]=val;
}
static void _dbdump(const void *buff,unsigned long bytes)
{
    unsigned long i,j;

    for (j=0,i=0; i<bytes; i++)
    {
        if (j<DBDUMP_COLS) 
            j++;
        else 
        { 
            j=1; 
            dbprintf(("\n")); 
        }
        dbprintf(("%2.2x",((const unsigned char*)buff)[i]));
    }
    dbprintf(("\n"));
}
#endif /* ndef _dbdump */
#endif /* ndef DBPRINTF */
#endif /* ndef dbdump */
#endif /* ndef DBDUMP_H */
