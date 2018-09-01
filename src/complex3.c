/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:58:46 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:58:50 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	cx_func(t_complex z)
{
	z = cx_sub(cx_pow(z, 3), compl(1, 0));
	return (z);
}

t_complex	cx_prederiv(t_complex z)
{
	z = cx_add(z, compl(TOLER, 0));
	return (cx_func(z));
}

t_complex	cx_deriv(t_complex z)
{
	t_complex	c;

	c = cx_prederiv(z);
	c = cx_sub(c, cx_func(z));
	c = cx_mul_sc(c, (1.0 / TOLER));
	return (c);
}
