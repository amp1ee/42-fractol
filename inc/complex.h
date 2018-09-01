/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:59:25 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:59:27 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_H
# define COMPLEX_H

# include <math.h>

typedef struct	s_complex
{
	double		re;
	double		im;
}				t_complex;

t_complex		compl(double re, double im);
t_complex		cx_add(t_complex c0, t_complex c1);
t_complex		cx_sub(t_complex c0, t_complex c1);
t_complex		cx_mul_cx(t_complex c0, t_complex c1);
t_complex		cx_mul_sc(t_complex c, double scalar);
t_complex		cx_div(t_complex c0, t_complex c1);
t_complex		cx_conj(t_complex c);
t_complex		cx_pow(t_complex c, int pow);
t_complex		cx_func(t_complex z);
t_complex		cx_prederiv(t_complex z);
t_complex		cx_deriv(t_complex z);

#endif
