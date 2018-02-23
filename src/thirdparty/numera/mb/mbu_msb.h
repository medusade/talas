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
 *   File: mbu_msb.h
 *
 * Author: $author$
 *   Date: 2/21/2018
 **********************************************************************
 */
#ifndef _NUMERA_MBU_MSB_H
#define _NUMERA_MBU_MSB_H

#include <mbu.h>

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

mb_uint_t* mbu_init_set_msb(mb_uint_t *m, const unsigned char *n, size_t nbytes);
mb_uint_t* mbu_set_msb(mb_uint_t *m, const unsigned char *n, size_t nbytes);
mb_uint_t* mbu_get_msb(mb_uint_t *m, unsigned char *n, size_t nbytes);

mb_uint_t* mbu_add_msb(mb_uint_t *m, const unsigned char *n, size_t nbytes);
mb_uint_t* mbu_sub_msb(mb_uint_t *m, const unsigned char *n, size_t nbytes);
mb_uint_t* mbu_mul_msb(mb_uint_t *m, const unsigned char *n, size_t nbytes);
mb_uint_t* mbu_mod_msb(mb_uint_t *m, const unsigned char *n, size_t nbytes);
mb_uint_t* mbu_div_msb(mb_uint_t *m, const unsigned char *n, size_t nbytes);

mb_uint_t* mbu_inv_mod_msb(mb_uint_t *m, const unsigned char *n, size_t nbytes);
mb_uint_t* mbu_exp_mod_msb(mb_uint_t *m, const unsigned char *x, size_t xbytes, const unsigned char *n, size_t nbytes);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* _NUMERA_MBU_MSB_H */

        

