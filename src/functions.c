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

#include "fractol.h"

void	mandelbrot(t_fractol *fr, t_complex *a, t_complex a2, int *i)
{
	while (((*i)--) > 0 && !BAILOUT(*a))
	{
		a2 = cx_pow(*a, 2);
		*a = cx_add(a2, fr->c);
	}
}

void	mandelbar(t_fractol *fr, t_complex *a, t_complex a2, int *i)
{
	while (((*i)--) > 0 && !BAILOUT(*a))
	{
		a2 = cx_conj(cx_pow(*a, 2));
		*a = cx_add(a2, fr->c);
	}
}

void	burning(t_fractol *fr, t_complex *a, t_complex a2, int *i)
{
	while (((*i)--) > 0 && !BAILOUT(*a))
	{
		a2.re = (a->re * a->re) - (a->im * a->im);
		a2.im = -2 * fabs(a->re) * fabs(a->im);
		*a = cx_add(a2, fr->c);
	}
}

void	celtic(t_fractol *fr, t_complex *a, t_complex a2, int *i)
{
	while (((*i)--) > 0 && !BAILOUT(*a))
	{
		a2.re = fabs(a->re * a->re - a->im * a->im);
		a2.im = -2 * a->re * a->im;
		*a = cx_add(a2, fr->c);
	}
}

void	perpend_bship(t_fractol *fr, t_complex *a, t_complex a2, int *i)
{
	while (((*i)--) > 0 && !BAILOUT(*a))
	{
		a2.re = a->re * a->re - a->im * a->im;
		a2.im = -2 * a->re * fabs(a->im);
		*a = cx_add(a2, fr->c);
	}
}
