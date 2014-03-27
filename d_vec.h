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

    Copyright (C) 2014 Abhinav Baid

******************************************************************************/

#ifndef D_VEC_H
#define D_VEC_H

#include <math.h>
#include "double_extras.h"
#include "flint.h"

#ifdef __cplusplus
 extern "C" {
#endif

/*  Memory management  *******************************************************/

double * _d_vec_init(slong len);

void _d_vec_clear(double * vec);

/*  Randomisation  ***********************************************************/

void _d_vec_randtest(double * f, flint_rand_t state, 
                        slong len);

/*  Assignment and basic manipulation  ***************************************/

void _d_vec_set(double * vec1, const double * vec2, slong len2);

void _d_vec_zero(double * vec, slong len);

/*  Comparison  **************************************************************/

int _d_vec_equal(const double * vec1, const double * vec2, slong len);

int _d_vec_approx_equal(const double * vec1, const double * vec2, slong len, double eps);

int _d_vec_is_zero(const double * vec, slong len);

/*  Addition  ****************************************************************/

void _d_vec_add(double * res, const double * vec1, const double * vec2, slong len2);

void _d_vec_sub(double * res, const double * vec1, const double * vec2, slong len2);

/*  Scalar product and norm  **************************************/

double _d_vec_scalar_product(const double * vec1, const double * vec2, slong len2);

double _d_vec_norm(const double * vec, slong len);

#ifdef __cplusplus
}
#endif

#endif
