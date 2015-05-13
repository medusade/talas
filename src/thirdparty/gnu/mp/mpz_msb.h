/**
 **********************************************************************
 * Copyright (C) 1991, 1993, 1994, 1995, 1996 Free Software Foundation, Inc.
 *
 * This file is part of the GNU MP Library.
 *
 * The GNU MP Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * The GNU MP Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 *
 *   File: mpz_msb.h
 *
 * Author: $author$
 *   Date: 2/1/2005
 *
 *    $Id$
 **********************************************************************
 */
#ifndef _MPZ_MSB_H
#define _MPZ_MSB_H

#include <gmp.h>

#if defined(__cplusplus)
extern "C" {
#endif

/**
 **********************************************************************
 * Function: mpz_get_msb
 *
 *   Author: $author$
 *     Date: 2/1/2005
 **********************************************************************
 */
mp_size_t mpz_get_msb _PROTO ((unsigned char *, mp_size_t , mpz_srcptr));
/**
 **********************************************************************
 * Function: mpz_set_msb
 *
 *   Author: $author$
 *     Date: 2/1/2005
 **********************************************************************
 */
mp_size_t mpz_set_msb _PROTO ((mpz_ptr, const unsigned char *, mp_size_t));

#if defined(__cplusplus)
}
#endif

#endif
