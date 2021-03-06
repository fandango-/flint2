/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2013 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#ifndef GMP_COMPAT_H
#define GMP_COMPAT_H

#if defined(__MINGW64__) && !defined(__MPIR_VERSION)

#define FLINT_MOCK_MPZ_UI(xxx, yyy) \
   __mpz_struct (xxx)[1] = {{ 1, 0, NULL }}; \
   do { \
      (xxx)->_mp_d = (mp_ptr) &(yyy); \
      if ((yyy) > 0) \
         (xxx)->_mp_size = 1; \
   }while (0)

#define FLINT_MOCK_MPZ_SI(xxx, yyy) \
   __mpz_struct (xxx)[1] = {{ 1, 0, NULL }}; \
   do { \
      (xxx)->_mp_d = (mp_ptr) &(yyy); \
      if ((yyy) < 0) (xxx)->_mp_size = -1, (yyy) = -(yyy); \
      else (xxx)->_mp_size = (yyy) != 0; \
   } while (0)

#define flint_mpz_get_si(xxx) \
   ((xxx)->_mp_size == 0 ? (slong) WORD(0) : \
   ((xxx)->_mp_size > 0 ? (slong) (xxx)->_mp_d[0] : (slong) -(xxx)->_mp_d[0]))

#define flint_mpz_get_ui(xxx) \
   ((xxx)->_mp_size == 0 ? WORD(0) : (xxx)->_mp_d[0])

static __inline__
void flint_mpz_set_si(mpz_ptr r, slong s)
{
   if (s < 0) {
      r->_mp_size = -1;
      r->_mp_d[0] = -s;
   } else {
      r->_mp_size = s != 0;
      r->_mp_d[0] = s;
   }
}

static __inline__
void flint_mpz_set_ui(mpz_ptr r, ulong u)
{
   r->_mp_d[0] = u; 
   r->_mp_size = u != 0;
}

static __inline__
void flint_mpz_init_set_si(mpz_ptr r, slong s)
{
   r->_mp_d = (mp_ptr) flint_malloc(sizeof(mp_limb_t));
   r->_mp_alloc = 1;

   if (s < 0) {
      r->_mp_size = -1;
      r->_mp_d[0] = -s;
   } else {
      r->_mp_size = s != 0;
      r->_mp_d[0] = s;
   }
}

static __inline__
void flint_mpz_init_set_ui(mpz_ptr r, ulong u)
{
   r->_mp_d = (mp_ptr) flint_malloc(sizeof(mp_limb_t));
   r->_mp_alloc = 1;

   r->_mp_d[0] = u; 
   r->_mp_size = u != 0;
}

static __inline__
void flint_mpz_add_ui(mpz_ptr a, mpz_srcptr b, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);
   
   mpz_add(a, b, tc);
}

static __inline__
void flint_mpz_sub_ui(mpz_ptr a, mpz_srcptr b, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);
   
   mpz_sub(a, b, tc);
}

static __inline__
void flint_mpz_mul_ui(mpz_ptr a, mpz_srcptr b, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);
   
   mpz_mul(a, b, tc);
}

static __inline__
void flint_mpz_mul_si(mpz_ptr a, mpz_srcptr b, slong c)
{
   FLINT_MOCK_MPZ_SI(tc, c);
   
   mpz_mul(a, b, tc);
}

static __inline__
void flint_mpz_addmul_ui(mpz_ptr a, mpz_srcptr b, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);
   
   mpz_addmul(a, b, tc);
}

static __inline__
void flint_mpz_submul_ui(mpz_ptr a, mpz_srcptr b, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);
   
   mpz_submul(a, b, tc);
}

static __inline__
void flint_mpz_ui_sub(mpz_ptr a, ulong b, mpz_srcptr c)
{
   FLINT_MOCK_MPZ_UI(tb, b);
   
   mpz_sub(a, tb, c);
}

static __inline__
void flint_mpz_ui_pow_ui(mpz_ptr a, ulong b, ulong c)
{
   FLINT_MOCK_MPZ_UI(tb, b);
   
   mpz_pow_ui(a, tb, c);
}

static __inline__
void flint_mpz_divexact_ui(mpz_ptr a, mpz_srcptr b, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);
   
   mpz_divexact(a, b, tc);
}

static __inline__
int flint_mpz_divisible_ui_p(mpz_srcptr a, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);
   
   return mpz_divisible_p(a, tc);
}

static __inline__
int flint_mpz_congruent_ui_p(mpz_srcptr a, ulong b, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);
   {
      FLINT_MOCK_MPZ_UI(tb, b);
   
      return mpz_congruent_p(a, tb, tc);
   }
}

static __inline__
int flint_mpz_cmp_ui(mpz_srcptr a, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);
   
   return mpz_cmp(a, tc);
}

static __inline__
int flint_mpz_cmp_si(mpz_srcptr a, slong c)
{
   FLINT_MOCK_MPZ_SI(tc, c);
   
   return mpz_cmp(a, tc);
}

static __inline__
int flint_mpq_cmp_si(mpq_srcptr a, slong b, ulong c)
{
   mpq_t tq;
   int res;
   FLINT_MOCK_MPZ_SI(tb, b);
   {
      FLINT_MOCK_MPZ_UI(tc, c);
      mpq_init(tq);
      mpq_set_num(tq, tb);
      mpq_set_den(tq, tc);

      res = mpq_cmp(a, tq);

      mpq_clear(tq);

      return res;
   }
}

static __inline__
int flint_mpq_cmp_ui(mpq_srcptr a, ulong b, ulong c)
{
   mpq_t tq;
   int res;
   FLINT_MOCK_MPZ_UI(tb, b);
   {
      FLINT_MOCK_MPZ_UI(tc, c);
      mpq_init(tq);
      mpq_set_num(tq, tb);
      mpq_set_den(tq, tc);

      res = mpq_cmp(a, tq);

      mpq_clear(tq);

      return res;
   }
}

static __inline__
void flint_mpq_set_si(mpq_ptr a, slong b, ulong c)
{
   FLINT_MOCK_MPZ_SI(tb, b);
   {
      FLINT_MOCK_MPZ_UI(tc, c);

      mpq_set_num(a, tb);
      mpq_set_den(a, tc);
   }
}

static __inline__
void flint_mpq_set_ui(mpq_ptr a, ulong b, ulong c)
{
   FLINT_MOCK_MPZ_UI(tb, b);
   {
      FLINT_MOCK_MPZ_UI(tc, c);

      mpq_set_num(a, tb);
      mpq_set_den(a, tc);
   }
}

static __inline__
void flint_mpz_cdiv_q_ui(mpz_ptr q, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_cdiv_q(q, n, tc);
}

static __inline__
void flint_mpz_fdiv_q_ui(mpz_ptr q, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_fdiv_q(q, n, tc);
}

static __inline__
void flint_mpz_tdiv_q_ui(mpz_ptr q, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_tdiv_q(q, n, tc);
}

static __inline__
ulong flint_mpz_cdiv_r_ui(mpz_ptr r, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_cdiv_r(r, n, tc);

   return flint_mpz_get_ui(r);
}

static __inline__
ulong flint_mpz_fdiv_r_ui(mpz_ptr r, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_fdiv_r(r, n, tc);

   return flint_mpz_get_ui(r);
}

static __inline__
ulong flint_mpz_tdiv_r_ui(mpz_ptr r, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_tdiv_r(r, n, tc);

   return flint_mpz_get_ui(r);
}

static __inline__
ulong flint_mpz_cdiv_qr_ui(mpz_ptr q, mpz_ptr r, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_cdiv_qr(q, r, n, tc);

   return flint_mpz_get_ui(r);
}

static __inline__
ulong flint_mpz_fdiv_qr_ui(mpz_ptr q, mpz_ptr r, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_fdiv_qr(q, r, n, tc);

   return flint_mpz_get_ui(r);
}

static __inline__
ulong flint_mpz_tdiv_qr_ui(mpz_ptr q, mpz_ptr r, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_tdiv_qr(q, r, n, tc);

   return flint_mpz_get_ui(r);
}

static __inline__
ulong flint_mpz_cdiv_ui(mpz_srcptr n, ulong c)
{
   mpz_t r;
   ulong res;

   mpz_init(r);
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_cdiv_r(r, n, tc);

   res = flint_mpz_get_ui(r);

   mpz_clear(r);

   return res;
}

static __inline__
ulong flint_mpz_fdiv_ui(mpz_srcptr n, ulong c)
{
   mpz_t r;
   ulong res;

   mpz_init(r);
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_fdiv_r(r, n, tc);

   res = flint_mpz_get_ui(r);

   mpz_clear(r);

   return res;
}

static __inline__
ulong flint_mpz_tdiv_ui(mpz_srcptr n, ulong c)
{
   mpz_t r;
   ulong res;

   mpz_init(r);
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_tdiv_r(r, n, tc);

   res = flint_mpz_get_ui(r);

   mpz_clear(r);

   return res;
}

static __inline__
ulong flint_mpz_mod_ui(mpz_ptr r, mpz_srcptr n, ulong c)
{
   FLINT_MOCK_MPZ_UI(tc, c);

   mpz_fdiv_r(r, n, tc);

   return flint_mpz_get_ui(r);
}

static __inline__
void flint_mpz_powm_ui(mpz_ptr r, mpz_srcptr b, ulong exp, mpz_srcptr mod)
{
   FLINT_MOCK_MPZ_UI(texp, exp);

   mpz_powm(r, b, texp, mod);
}

static __inline__
void flint_mpz_pow_ui(mpz_ptr r, mpz_srcptr b, ulong exp)
{
   if (exp >= (UWORD(1) << 32)) {
      printf("Exception (flint_mpz_pow_ui). Power too large.\n");
      abort();
   }
   
   mpz_pow_ui(r, b, (unsigned long) exp);
}

static __inline__
void flint_mpz_fac_ui(mpz_ptr r, ulong n)
{
   if (n >= (UWORD(1) << 32)) {
      printf("Exception (flint_mpz_fac_ui). Value n too large.\n");
      abort();
   }
   
   mpz_fac_ui(r, (unsigned long) n);
}

static __inline__
void flint_mpz_bin_uiui(mpz_ptr r, ulong n, ulong k)
{
   if (n >= (UWORD(1) << 32)) {
      printf("Exception (flint_mpz_bin_uiui). Value n too large.\n");
      abort();
   }
   
   if (k >= (UWORD(1) << 32)) {
      printf("Exception (flint_mpz_bin_uiui). Value k too large.\n");
      abort();
   }
   
   mpz_bin_uiui(r, (unsigned long) n, (unsigned long) k);
}

static __inline__
void flint_mpz_fib_ui(mpz_ptr r, ulong n)
{
   if (n >= (UWORD(1) << 32)) {
      printf("Exception (flint_mpz_fib_ui). Value n too large.\n");
      abort();
   }
   
   mpz_fib_ui(r, (unsigned long) n);
}

#else

#define flint_mpz_get_si mpz_get_si
#define flint_mpz_get_ui mpz_get_ui
#define flint_mpz_set_si mpz_set_si
#define flint_mpz_set_ui mpz_set_ui
#define flint_mpz_init_set_si mpz_init_set_si
#define flint_mpz_init_set_ui mpz_init_set_ui
#define flint_mpz_add_ui mpz_add_ui
#define flint_mpz_sub_ui mpz_sub_ui
#define flint_mpz_mul_si mpz_mul_si
#define flint_mpz_mul_ui mpz_mul_ui
#define flint_mpz_addmul_ui mpz_addmul_ui
#define flint_mpz_submul_ui mpz_submul_ui
#define flint_mpz_ui_sub mpz_ui_sub
#define flint_mpz_ui_pow_ui mpz_ui_pow_ui
#define flint_mpz_cdiv_q_ui mpz_cdiv_q_ui
#define flint_mpz_cdiv_r_ui mpz_cdiv_r_ui
#define flint_mpz_cdiv_qr_ui mpz_cdiv_qr_ui
#define flint_mpz_cdiv_ui mpz_cdiv_ui
#define flint_mpz_fdiv_q_ui mpz_fdiv_q_ui
#define flint_mpz_fdiv_r_ui mpz_fdiv_r_ui
#define flint_mpz_fdiv_qr_ui mpz_fdiv_qr_ui
#define flint_mpz_fdiv_ui mpz_fdiv_ui
#define flint_mpz_tdiv_q_ui mpz_tdiv_q_ui
#define flint_mpz_tdiv_r_ui mpz_tdiv_r_ui
#define flint_mpz_tdiv_qr_ui mpz_tdiv_qr_ui
#define flint_mpz_tdiv_ui mpz_tdiv_ui
#define flint_mpz_mod_ui mpz_mod_ui
#define flint_mpz_divexact_ui mpz_divexact_ui
#define flint_mpz_divisible_ui_p mpz_divisible_ui_p
#define flint_mpz_congruent_ui_p mpz_congruent_ui_p
#define flint_mpz_powm_ui mpz_powm_ui
#define flint_mpz_pow_ui mpz_pow_ui
#define flint_mpz_fac_ui mpz_fac_ui
#define flint_mpz_bin_uiui mpz_bin_uiui
#define flint_mpz_fib_ui mpz_fib_ui
#define flint_mpz_cmp_si mpz_cmp_si
#define flint_mpz_cmp_ui mpz_cmp_ui
#define flint_mpq_cmp_si mpq_cmp_si
#define flint_mpq_cmp_ui mpq_cmp_ui
#define flint_mpq_set_si mpq_set_si
#define flint_mpq_set_ui mpq_set_ui

#endif

#endif
