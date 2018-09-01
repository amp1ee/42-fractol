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

#include "fractol.h"

static inline void	put_pxl(t_fractol *fr, int x, int y, unsigned int c)
{
	int		i;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	i = (x * 4) + (y * fr->s_line);
	fr->pxl[i] = c;
	fr->pxl[++i] = c >> 8;
	fr->pxl[++i] = c >> 16;
}

void				iter_mandelbrots(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	if (fr->julia == 0)
		fr->c = compl(a.re, a.im);
	i = fr->iter;
	fr->fun(fr, &a, aa, &i);
	if (i < 0)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y, fr->color(fr->colormode, log_perc(fr->iter, i, a)));
}

void				iter_newtons(t_fractol *fr, int x, int y)
{
	const t_complex	roots[3] = {
		compl(1, 0),
		compl(-0.5, sqrt(3) / 2),
		compl(-0.5, -sqrt(3) / 2) };
	t_complex		z;
	int				i;
	int				j;

	z.re = fr->reoff + x * fr->centerx;
	z.im = fr->imoff + (HEIGHT - y) * fr->centery;
	i = 100;
	while ((i--) > 0)
	{
		z = cx_sub(z, cx_div(cx_func(z), cx_deriv(z)));
		j = -1;
		while ((++j) < 3)
		{
			if (IS_ROOT(z, roots))
				return (put_pxl(fr, x, y, fr->color(fr->colormode,
					(fr->alt_newton == 1) ? ((float)(fr->iter - i)
					- log2(log2(sqrt(z.re * z.re + z.im * z.im)))) / fr->iter :
					(float)i / 100)));
		}
	}
	put_pxl(fr, x, y, BLACK);
}

void				*draw_thread(void *fract)
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
			fr->iter_fun(fr, x, y);
			y++;
		}
		x++;
	}
	pthread_exit(0);
	return (NULL);
}

void				get_threads(t_fractol *fr)
{
	pthread_t		threads[THREADS_NUM];
	t_fractol		rows[THREADS_NUM];
	int				i;
	int				y;
	char			*iter;

	fr->centerx = (3 * HEIGHT / (fr->zoom * WIDTH));
	fr->centery = 2 / fr->zoom;
	i = -1;
	y = 0;
	while (++i < THREADS_NUM)
	{
		rows[i] = *fr;
		rows[i].parth = y;
		y += fr->hstep;
		if (pthread_create(&threads[i], NULL, draw_thread, (void *)&rows[i]))
			exiterror(PTHR_ERR, fr);
	}
	while (i-- > 0)
		if (pthread_join(threads[i], NULL))
			exiterror(PTHR_ERR, fr);
	mlx_put_image_to_window(fr->mlx, fr->win, fr->img, 0, 0);
	mlx_string_put(fr->mlx, fr->win, 20, 20, WHITE, (iter = ft_itoa(fr->iter)));
	ft_strdel(&iter);
}
