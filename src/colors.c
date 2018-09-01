/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:58:30 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:58:32 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float				log_perc(int iter, int i, t_complex a)
{
	return (((float)(iter - i)
		- log2(log2(sqrt(a.re * a.re + a.im * a.im)))) / iter);
}

void				change_color(t_fractol *fr, int key)
{
	if (key == KP_4)
		if (fr->color == interp_color)
			fr->color = psy_color;
		else
			fr->color = interp_color;
	else if (key == KP_2)
	{
		fr->colormode++;
		fr->colormode %= 4;
	}
}

static inline int	interp_i(int start, int end, double perc)
{
	int		res;

	if (start == end)
		return (start);
	if (perc == 1.0)
		return (end);
	else if (perc == 0.0)
		return (start);
	res = (1 - perc) * start + perc * end;
	return (res);
}

int					interp_color(int colormode, float perc)
{
	t_complex	rgb;
	int			r;
	int			g;
	int			b;

	if (colormode == 0)
		rgb = compl(COLOR3, COLOR11);
	else if (colormode == 1)
		rgb = compl(COLOR1, COLOR2);
	else if (colormode == 2)
		rgb = compl(COLOR5, COLOR6);
	else
		rgb = compl(COLOR9, COLOR10);
	perc = fabs(sin(PI * perc));
	r = interp_i((int)rgb.re >> 16, (int)rgb.im >> 16, perc);
	g = interp_i(((int)rgb.re >> 8) & 0xFF, ((int)rgb.im >> 8) & 0xFF, perc);
	b = interp_i((int)rgb.re & 0xFF, (int)rgb.im & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}

int					psy_color(int colormode, float perc)
{
	t_complex	c;
	int			r;
	int			g;
	int			b;

	if (colormode == 0)
		c = compl(COLOR7, COLOR8);
	else if (colormode == 1)
		c = compl(COLOR4, COLOR3);
	else if (colormode == 2)
		c = compl(COLOR5, COLOR6);
	else
		c = compl(COLOR9, COLOR2);
	r = 0.9 * sin(interp_i((int)c.re >> 16, (int)c.im >> 16, perc / 3.0)
		* perc) * 120 + 135;
	g = 0.8 * sin(interp_i(((int)c.re >> 8) & 0xFF,
		((int)c.im >> 8) & 0xFF, perc / 2.0) * perc) * 120 + 135;
	b = 0.7 * sin(interp_i((int)c.re & 0xFF, (int)c.im & 0xFF, perc / 2.0)
		* perc) * 120 + 135;
	return ((r << 16) | (g << 8) | b);
}
