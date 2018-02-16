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
#else
#include <stdio.h>
#define dbif(cond) if (cond)
#define dbprintf(args) _dbprintf args
#ifndef _dbprintf
#ifdef __cplusplus
extern "C" {
#endif /* def __cplusplus */
extern int _dbprintf(const char* format, ...);
#ifdef __cplusplus
} /* extern "C" { */
#endif /* ndef _dbprintf */
#endif /* def __cplusplus */
#endif /* ndef DBPRINTF */
#endif /* ndef dbprintf */
#endif /* ndef DBPRINTF_H */
