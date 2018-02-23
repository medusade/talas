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
 *   File: mbu.h
 *
 * Author: $author$
 *   Date: 2/21/2018
 **********************************************************************
 */
#ifndef _NUMERA_MBU_H
#define _NUMERA_MBU_H

#include <mbi.h>

/**
 * struct mb_uint_t
 */
struct mb_uint_t;
typedef struct mb_uint_t {
    unsigned char b[mb_int_size_max];
} mb_uint_t;

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

mb_uint_t* mbu_init(mb_uint_t *m);
mb_uint_t* mbu_clear(mb_uint_t *m);

mb_uint_t* mbu_init_set_u(mb_uint_t *m, unsigned n);
mb_uint_t* mbu_set_u(mb_uint_t *m, unsigned n);

mb_uint_t* mbu_init_set(mb_uint_t *m, const mb_uint_t *n);
mb_uint_t* mbu_set(mb_uint_t *m, const mb_uint_t *n);

mb_uint_t* mbu_add_u(mb_uint_t *m, unsigned n);
mb_uint_t* mbu_add(mb_uint_t *m, const mb_uint_t *n);

mb_uint_t* mbu_sub_u(mb_uint_t *m, unsigned n);
mb_uint_t* mbu_sub(mb_uint_t *m, const mb_uint_t *n);

mb_uint_t* mbu_mul_u(mb_uint_t *m, unsigned n);
mb_uint_t* mbu_mul(mb_uint_t *m, const mb_uint_t *n);

mb_uint_t* mbu_mod_u(mb_uint_t *m, unsigned n);
mb_uint_t* mbu_mod(mb_uint_t *m, const mb_uint_t *n);

mb_uint_t* mbu_div_u(mb_uint_t *m, unsigned n);
mb_uint_t* mbu_div(mb_uint_t *m, const mb_uint_t *n);

mb_uint_t* mbu_exp_u(mb_uint_t *m, unsigned x);
mb_uint_t* mbu_exp(mb_uint_t *m, const mb_uint_t *x);

mb_uint_t* mbu_inv_mod_u(mb_uint_t *m, unsigned n);
mb_uint_t* mbu_inv_mod(mb_uint_t *m, const mb_uint_t *n);

mb_uint_t* mbu_exp_mod_u(mb_uint_t *m, unsigned x, const mb_uint_t *n);
mb_uint_t* mbu_exp_mod(mb_uint_t *m, const mb_uint_t *x, const mb_uint_t *n);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* _NUMERA_MBU_H */

        

