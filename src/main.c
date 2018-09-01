/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:58:06 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:58:09 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		*exiterror(char *reason, t_fractol *fr)
{
	ft_putendl(reason);
	if (fr)
	{
		ft_bzero(fr->pxl, WIDTH * HEIGHT * (fr->bpp / 8));
		mlx_destroy_window(fr->mlx, fr->win);
		mlx_destroy_image(fr->mlx, fr->img);
		free(fr);
	}
	exit(0);
	return (NULL);
}

bool		check_args(char *av, t_fractol *f)
{
	f->julia = 0;
	f->iter_fun = iter_mandelbrots;
	if (ft_strequ(av, MBROT))
		f->fun = mandelbrot;
	else if (ft_strequ(av, MBAR))
		f->fun = mandelbar;
	else if (ft_strequ(av, JULIA) || ft_strequ(av, JBAR))
	{
		f->julia = 1;
		f->fun = (ft_strequ(av, JULIA)) ? mandelbrot : mandelbar;
	}
	else if (ft_strequ(av, BSHIP))
		f->fun = burning;
	else if (ft_strequ(av, PSHIP))
		f->fun = perpend_bship;
	else if (ft_strequ(av, CELTIC))
		f->fun = celtic;
	else if (ft_strequ(av, NEWTON) || ft_strequ(av, ANEWTON))
	{
		f->alt_newton = ft_strequ(av, ANEWTON);
		f->iter_fun = iter_newtons;
	}
	else
		return (false);
	return (true);
}

void		reset_fractol(t_fractol *fr)
{
	fr->zoom = (double)HEIGHT / 2;
	fr->reoff = -3;
	fr->imoff = -2;
	fr->step = 0.1;
	fr->iter = ITERS_MIN;
	fr->julia_fixed = 0;
}

t_fractol	*init_fractol(char *av, int ac)
{
	t_fractol	*fr;
	char		*title;

	if ((fr = (t_fractol *)malloc(sizeof(*fr))) == NULL)
		return (exiterror(MLX_ERR, NULL));
	if (ac < 2 || ac > 2 || !(check_args(av, fr)))
		return (exiterror(USG_ERR, NULL));
	title = ft_strjoin("Fract`ol - ", av);
	if ((fr->mlx = mlx_init()) == NULL ||
	(fr->win = mlx_new_window(fr->mlx, WIDTH, HEIGHT, title)) == NULL ||
	(fr->img = mlx_new_image(fr->mlx, WIDTH, HEIGHT)) == NULL ||
	(fr->pxl = mlx_get_data_addr(fr->img, &(fr->bpp),
		&(fr->s_line), &(fr->ed))) == NULL)
		return (exiterror(MLX_ERR, fr));
	ft_strdel(&title);
	reset_fractol(fr);
	fr->hstep = HEIGHT / THREADS_NUM;
	fr->colormode = 0;
	fr->color = interp_color;
	return (fr);
}

int			main(int ac, char **av)
{
	t_fractol		*fractol;

	(void)(system("printf '\e[33m' && figlet -f lean '\tFract`ol'") + 1);
	(void)(system("printf '\e[0m'") + 1);
	if ((fractol = init_fractol(av[1], ac)) == NULL)
		return (-1);
	ft_putendl(CONTROLS);
	get_threads(fractol);
	mlx_hook(fractol->win, 2, 5, key_handler, fractol);
	mlx_hook(fractol->win, 4, (1L << 2), mouse_handler, fractol);
	mlx_hook(fractol->win, 6, (1L << 6), mouse_handler2, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
