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

#include "../fractol.h"

void				change_color(t_fractol *fr, int key)
{
	if (key == KP_4)
		if (fr->color == interp_color)
			fr->color = psy_color;
		else
			fr->color = interp_color;
	else if (key == KP_2)
		fr->colormode = !fr->colormode;
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
	const int	c1 = colormode ? COLOR3 : COLOR1;
	const int	c2 = colormode ? COLOR4 : COLOR2;
	int			r;
	int			g;
	int			b;

	perc = fabs(sin(perc * PI));
	r = interp_i(c1 >> 16, c2 >> 16, perc);
	g = interp_i((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, perc);
	b = interp_i(c1 & 0xFF, c2 & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}

int					psy_color(int colormode, float perc)
{
	const int	c1 = colormode ? COLOR7 : COLOR5;
	const int	c2 = colormode ? COLOR8 : COLOR6;
	int			r;
	int			g;
	int			b;

	r = sin(interp_i(c1 >> 16, c2 >> 16, perc)
		* perc) * 50;
	g = sin(interp_i((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, perc)
		* perc) * 120 + 135;
	b = sin(interp_i(c1 & 0xFF, c2 & 0xFF, perc)
		* perc) * 120 + 135;
	return ((r << 16) | (g << 8) | b);
}
