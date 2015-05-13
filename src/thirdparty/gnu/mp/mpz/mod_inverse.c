/* mpz_mod_inverse -- The multiplicative inverse using Euclids algorithm function.

Copyright (C) 1991, 1993, 1994, 1995, 1996 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Library General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
License for more details.

You should have received a copy of the GNU Library General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#include "gmp.h"
#include "gmp-impl.h"

void
#if __STDC__
mpz_mod_inverse (mpz_ptr x, mpz_srcptr a, mpz_srcptr n)
#else
mpz_mod (x, a, n)
     mpz_ptr x;
     mpz_srcptr a;
     mpz_srcptr n;
#endif
{
  MP_INT g0, g1, v0, v1, div, mod, aux;

  mpz_init_set(&g0, n);
  mpz_init_set(&g1, a);
  mpz_init_set_ui(&v0, 0);
  mpz_init_set_ui(&v1, 1);
  mpz_init(&div);
  mpz_init(&mod);
  mpz_init(&aux);

  while (mpz_cmp_ui(&g1, 0) != 0)
    {
      mpz_divmod(&div, &mod, &g0, &g1);
      mpz_mul(&aux, &div, &v1);
      mpz_sub(&aux, &v0, &aux);
      mpz_set(&v0, &v1);
      mpz_set(&v1, &aux);
      mpz_set(&g0, &g1);
      mpz_set(&g1, &mod);
    }

  if (mpz_cmp_ui(&v0, 0) < 0)
    mpz_add(x, &v0, n);
  else
    mpz_set(x, &v0);

  mpz_clear(&g0);
  mpz_clear(&g1);
  mpz_clear(&v0);
  mpz_clear(&v1);
  mpz_clear(&div);
  mpz_clear(&mod);
  mpz_clear(&aux);
}
