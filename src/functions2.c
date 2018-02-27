/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:58:46 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:58:50 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static inline t_complex	cx_func(t_complex z)
{
	z = cx_sub(cx_pow(z, 3), compl(1, 0));
	return (z);
}

static inline t_complex	cx_prederiv(t_complex z)
{
	z = cx_add(z, compl(TOLER, 0));
	return (cx_func(z));
}

static inline t_complex	cx_deriv(t_complex z)
{
	t_complex	c;

	c = cx_prederiv(z);
	c = cx_sub(c, cx_func(z));
	c = cx_mul_sc(c, (1.0 / TOLER));
	return (c);
}

void					newton(t_fractol *fr, int x, int y)
{
	const t_complex	roots[3] = {
		compl(1, 0),
		compl(-0.5, sqrt(3) / 2),
		compl(-0.5, -sqrt(3) / 2) };
	t_complex		z;
	int				i;
	int				j;

	z.re = fr->reoff + x * fr->centerx;
	z.im = fr->imoff + (HEIGHT - y) * fr->centery;
	i = 100;
	while ((i--) > 0)
	{
		z = cx_sub(z, cx_div(cx_func(z), cx_deriv(z)));
		j = -1;
		while ((++j) < 3)
		{
			if (fabs(z.re - roots[j].re) < TOLER &&
				fabs(z.im - roots[j].im) < TOLER)
				return (put_pxl(fr, x, y, fr->color(fr->colormode,
					(float)i / 100)));
		}
	}
	put_pxl(fr, x, y, BLACK);
}

void					strnewton(t_fractol *fr, int x, int y)
{
	const t_complex	roots[3] = {
		compl(1, 0),
		compl(-0.5, sqrt(3) / 2),
		compl(-0.5, -sqrt(3) / 2) };
	t_complex		z;
	int				i;
	int				j;

	z.re = fr->reoff + x * fr->centerx;
	z.im = fr->imoff + (HEIGHT - y) * fr->centery;
	i = 100;
	while ((i--) > 0)
	{
		z = cx_sub(z, cx_div(cx_func(z), cx_deriv(z)));
		j = -1;
		while ((++j) < 3)
		{
			if (fabs(z.re - roots[j].re) < TOLER &&
				fabs(z.im - roots[j].im) < TOLER)
				return (put_pxl(fr, x, y, fr->color(fr->colormode,
					((float)(fr->iter - i) - log2(log2(sqrt(z.re * z.re
					+ z.im * z.im)))) / fr->iter)));
		}
	}
	put_pxl(fr, x, y, BLACK);
}
