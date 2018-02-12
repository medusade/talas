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
 *   File: dbprintf.h
 *
 * Author: $author$
 *   Date: 6/17/98, 2/11/2018
 **********************************************************************
 */
#ifndef DBPRINTF_H
#define DBPRINTF_H

#ifndef dbprintf
#ifndef DBPRINTF
#define dbif(cond)
#define dbprintf(args)
#define dbset(buff,val,bytes)
#define dbdump(buff,bytes)
#else
#include <stdio.h>
#define dbif(cond) if (cond)
#define dbprintf(args) stderr_dbprintf args
#ifdef __cplusplus
extern "C" {
#endif /* def __cplusplus */
extern int stderr_dbprintf(const char* format, ...);
extern void dbset(void *buff,unsigned char val,unsigned long bytes);
extern void dbdump(const void *buff,unsigned long bytes);
#ifdef __cplusplus
} /* extern "C" { */
#endif /* def __cplusplus */
#endif
#endif
#endif
