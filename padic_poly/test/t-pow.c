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

    Copyright (C) 2009 William Hart
    Copyright (C) 2012 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "padic_poly.h"
#include "ulong_extras.h"
#include "long_extras.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;

    padic_ctx_t ctx;
    fmpz_t p;
    slong N;

    printf("pow... ");
    fflush(stdout);

    flint_randinit(state);

    /* Aliasing */
    for (i = 0; i < 1000; i++)
    {
        padic_poly_t a, b, c;
        slong e;

        fmpz_init_set_ui(p, n_randtest_prime(state, 0));
        N = n_randint(state, PADIC_TEST_PREC_MAX - PADIC_TEST_PREC_MIN) 
            + PADIC_TEST_PREC_MIN;
        padic_ctx_init(ctx, p, FLINT_MAX(0, N-10), FLINT_MAX(0, N+10), PADIC_SERIES);

        padic_poly_init2(a, 0, N);
        padic_poly_init2(b, 0, N);
        padic_poly_init2(c, 0, N);

        padic_poly_randtest(a, state, n_randint(state, 100), ctx);
        padic_poly_set(b, a, ctx);
        e = n_randint(state, 10);

        padic_poly_pow(c, b, e, ctx);
        padic_poly_pow(b, b, e, ctx);

        result = (padic_poly_equal(b, c) && padic_poly_is_reduced(b, ctx));
        if (!result)
        {
            printf("FAIL:\n");
            padic_poly_print(a, ctx), printf("\n\n");
            padic_poly_print(b, ctx), printf("\n\n");
            padic_poly_print(c, ctx), printf("\n\n");
            printf("e = %ld\n\n", e);
            abort();
        }

        padic_poly_clear(a);
        padic_poly_clear(b);
        padic_poly_clear(c);

        padic_ctx_clear(ctx);
        fmpz_clear(p);
    }

    /* Compare with the computation over QQ */
    for (i = 0; i < 1000; i++)
    {
        padic_poly_t a, b, c;
        fmpq_poly_t aQQ, bQQ;
        slong e;

        fmpz_init_set_ui(p, n_randtest_prime(state, 0));
        N = n_randint(state, PADIC_TEST_PREC_MAX - PADIC_TEST_PREC_MIN) 
            + PADIC_TEST_PREC_MIN;
        padic_ctx_init(ctx, p, FLINT_MAX(0, N-10), FLINT_MAX(0, N+10), PADIC_SERIES);

        padic_poly_init2(a, 0, N);
        padic_poly_init2(b, 0, N);
        padic_poly_init2(c, 0, N);
        fmpq_poly_init(aQQ);
        fmpq_poly_init(bQQ);

        padic_poly_randtest(a, state, n_randint(state, 10), ctx);
        e = n_randint(state, 10);

        padic_poly_pow(b, a, e, ctx);

        padic_poly_get_fmpq_poly(aQQ, a, ctx);
        fmpq_poly_pow(bQQ, aQQ, e);
        padic_poly_set_fmpq_poly(c, bQQ, ctx);

        if (e == 0)
        {
            result = (padic_poly_equal(b, c) && padic_poly_is_reduced(b, ctx));
            if (!result)
            {
                printf("FAIL (cmp with QQ):\n");
                padic_poly_print(a, ctx), printf("\n\n");
                padic_poly_print(b, ctx), printf("\n\n");
                padic_poly_print(c, ctx), printf("\n\n");
                abort();
            }
        }
        else
        {
            padic_poly_t blo, clo;

            slong N2 = N + (e - 1) * a->val;

            padic_poly_init2(blo, 0, N2);
            padic_poly_init2(clo, 0, N2);

            padic_poly_set(blo, b, ctx);
            padic_poly_set(clo, c, ctx);

            result = (padic_poly_equal(blo, clo) && padic_poly_is_reduced(blo, ctx));
            if (!result)
            {
                printf("FAIL (cmp with QQ):\n");
                printf("a = "), padic_poly_print(a, ctx), printf("\n\n");
                printf("b = "), padic_poly_print(b, ctx), printf("\n\n");
                printf("c = "), padic_poly_print(c, ctx), printf("\n\n");
                printf("blo = "), padic_poly_print(blo, ctx), printf("\n\n");
                printf("clo = "), padic_poly_print(clo, ctx), printf("\n\n");
                printf("N = %ld\n\n", N);
                printf("e = %ld\n\n", e);
                printf("N + (e - 1) v = %ld\n\n", N + (e - 1) * a->val);
                abort();
            }

            padic_poly_clear(blo);
            padic_poly_clear(clo);
        }

        padic_poly_clear(a);
        padic_poly_clear(b);
        padic_poly_clear(c);
        fmpq_poly_clear(aQQ);
        fmpq_poly_clear(bQQ);

        padic_ctx_clear(ctx);
        fmpz_clear(p);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}
