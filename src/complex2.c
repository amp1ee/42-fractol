/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:59:06 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:59:08 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../complex.h"

t_complex	cx_div(t_complex c0, t_complex c1)
{
	t_complex c;

	c = cx_mul_sc(cx_conj(c1), (1.0 / (c1.re * c1.re + c1.im * c1.im)));
	return (cx_mul_cx(c0, c));
}

t_complex	cx_pow(t_complex c, int pow)
{
	t_complex	res;

	res = c;
	while (--pow)
		res = cx_mul_cx(res, c);
	return (res);
}

t_complex	cx_sin(t_complex c)
{
	return (compl(sin(c.re) * cosh(c.im), cos(c.re) * sinh(c.im)));
}

t_complex	cx_cos(t_complex c)
{
	return (compl(cos(c.re) * cosh(c.im), -sin(c.re) * sinh(c.im)));
}

t_complex	cx_conj(t_complex c)
{
	return (compl(c.re, c.im * -1));
}
