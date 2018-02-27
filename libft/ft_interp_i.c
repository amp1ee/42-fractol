/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interp_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 14:33:26 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/19 14:33:29 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_interp_i(int start, int end, double perc)
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
