/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:58:40 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:58:41 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void		mandelbrot(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	if (fr->julia == 0)
		fr->c = compl(a.re, a.im);
	i = fr->iter;
	while ((i--) > 0 && (a.re * a.re + a.im * a.im) < 4)
	{
		aa = cx_pow(a, 2);
		a = cx_add(aa, fr->c);
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y, fr->color(fr->colormode, ((float)(fr->iter - i)
			- log2(log2(sqrt(a.re * a.re + a.im * a.im)))) / fr->iter));
}

void		something(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	fr->c = a;
	i = fr->iter;
	while ((i--) > 0 && (a.re * a.re + a.im * a.im) < 4)
	{
		aa = cx_cos(compl(a.re + fr->c.re,
			(2 * a.re * a.im) + fr->c.im));
		a = cx_add(aa, fr->c);
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y, fr->color(fr->colormode, ((float)(fr->iter - i)
			- log2(log2(sqrt(a.re * a.re + a.im * a.im)))) / fr->iter));
}

void		mandelbar(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	if (fr->julia == 0)
		fr->c = compl(a.re, a.im);
	i = fr->iter;
	while ((i--) > 0 && (a.re * a.re + a.im * a.im) < 4)
	{
		aa = cx_conj(cx_pow(a, 2));
		a = cx_add(aa, fr->c);
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y, fr->color(fr->colormode, ((float)(fr->iter - i)
			- log2(log2(sqrt(a.re * a.re + a.im * a.im)))) / fr->iter));
}

void		burning(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	fr->c = compl(a.re, a.im);
	i = fr->iter;
	while ((i--) > 0 && (a.re * a.re + a.im * a.im) < 4)
	{
		aa.re = (a.re * a.re) - (a.im * a.im);
		aa.im = -2 * fabs(a.re) * fabs(a.im);
		a = cx_add(aa, fr->c);
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y, fr->color(fr->colormode, ((float)(fr->iter - i)
			- log2(log2(sqrt(a.re * a.re + a.im * a.im)))) / fr->iter));
}
