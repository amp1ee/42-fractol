/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:58:15 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:58:17 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void		put_pxl(t_fractol *fr, int x, int y, unsigned int c)
{
	int		i;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	i = (x * 4) + (y * fr->s_line);
	fr->pxl[i] = c;
	fr->pxl[++i] = c >> 8;
	fr->pxl[++i] = c >> 16;
}

void		*drawthr(void *fract)
{
	int			x;
	int			y;
	t_fractol	*fr;

	fr = (t_fractol *)fract;
	x = 0;
	while (x < WIDTH)
	{
		y = fr->parth;
		while (y <= fr->parth + fr->hstep)
		{
			fr->fun(fr, x, y);
			y++;
		}
		x++;
	}
	pthread_exit(0);
	return (NULL);
}

void		get_threads(t_fractol *fr)
{
	pthread_t		thr[THREADS];
	t_fractol		frx[THREADS];
	int				i;
	int				y;
	char			*iter;

	fr->centerx = (3 * HEIGHT / (fr->zoom * WIDTH));
	fr->centery = 2 / fr->zoom;
	i = -1;
	y = 0;
	while (++i < THREADS)
	{
		frx[i] = *fr;
		frx[i].parth = y;
		y += fr->hstep;
		if (pthread_create(&thr[i], NULL, drawthr, (void *)&frx[i]))
			exiterror(PTHR_ERR, fr);
	}
	while (i-- > 0)
		if (pthread_join(thr[i], NULL))
			exiterror(PTHR_ERR, fr);
	mlx_put_image_to_window(fr->mlx, fr->win, fr->img, 0, 0);
	mlx_string_put(fr->mlx, fr->win, 20, 20, WHITE, (iter = ft_itoa(fr->iter)));
	ft_strdel(&iter);
}
