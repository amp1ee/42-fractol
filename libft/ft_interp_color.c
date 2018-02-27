/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interp_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 20:54:14 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 20:54:17 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_interp_color(int c1, int c2, float perc)
{
	int		r;
	int		g;
	int		b;

	r = ft_interp_i(c1 >> 16, c2 >> 16, perc);
	g = ft_interp_i((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, perc);
	b = ft_interp_i(c1 & 0xFF, c2 & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}
