/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:59:01 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:59:03 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.h"

t_complex	compl(double re, double im)
{
	t_complex	new;

	new.re = re;
	new.im = im;
	return (new);
}

t_complex	cx_add(t_complex c0, t_complex c1)
{
	return (compl(c0.re + c1.re, c0.im + c1.im));
}

t_complex	cx_sub(t_complex c0, t_complex c1)
{
	return (compl(c0.re - c1.re, c0.im - c1.im));
}

t_complex	cx_mul_cx(t_complex c0, t_complex c1)
{
	return (compl(c0.re * c1.re - c0.im * c1.im,
		c0.re * c1.im + c0.im * c1.re));
}

t_complex	cx_mul_sc(t_complex c, double scalar)
{
	return (compl(c.re * scalar, c.im * scalar));
}
