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

#include "../fractol.h"

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

int			check_args(char **av, t_fractol *f)
{
	f->julia = 0;
	if (ft_strequ(av[1], "mandelbrot"))
		f->fun = mandelbrot;
	else if (ft_strequ(av[1], "mandelbar"))
		f->fun = mandelbar;
	else if (ft_strequ(av[1], "julia") || (ft_strequ(av[1], "juliabar")))
	{
		f->julia = 1;
		if (ft_strequ(av[1], "julia"))
			f->fun = mandelbrot;
		else
			f->fun = mandelbar;
	}
	else if (ft_strequ(av[1], "bship"))
		f->fun = burning;
	else if (ft_strequ(av[1], "newton"))
		f->fun = newton;
	else if (ft_strequ(av[1], "strnewton"))
		f->fun = strnewton;
	else if (ft_strequ(av[1], "smth"))
		f->fun = something;
	else
		return (0);
	return (1);
}

void		reset_fractol(t_fractol *fr)
{
	fr->zoom = (double)HEIGHT / 2;
	fr->reoff = -3;
	fr->imoff = -2;
	fr->step = 0.1;
	fr->iter = ITERATIONS;
	fr->julia_fixed = 0;
}

t_fractol	*init_fractol(char *title, char **av, int ac)
{
	t_fractol	*fr;

	if ((fr = (t_fractol *)malloc(sizeof(*fr))) == NULL)
		return (exiterror(MLX_ERR, NULL));
	if (ac == 1 || ac > 2 || (check_args(av, fr)) == 0)
		return (exiterror(USG_ERR, NULL));
	if ((fr->mlx = mlx_init()) == NULL ||
	(fr->win = mlx_new_window(fr->mlx, WIDTH, HEIGHT, title)) == NULL ||
	(fr->img = mlx_new_image(fr->mlx, WIDTH, HEIGHT)) == NULL ||
	(fr->pxl = mlx_get_data_addr(fr->img, &(fr->bpp),
		&(fr->s_line), &(fr->ed))) == NULL)
		return (exiterror(MLX_ERR, fr));
	fr->zoom = (double)HEIGHT / 2;
	fr->reoff = -3;
	fr->imoff = -2;
	fr->step = 0.1;
	fr->hstep = HEIGHT / THREADS;
	fr->colormode = 0;
	fr->iter = ITERATIONS;
	fr->julia_fixed = 0;
	fr->color = interp_color;
	return (fr);
}

int			main(int ac, char **av)
{
	t_fractol		*fractol;

	if ((fractol = init_fractol("Fract'ol", av, ac)) == NULL)
		return (-1);
	ft_putendl(CONTROLS);
	get_threads(fractol);
	mlx_hook(fractol->win, 2, 5, key_handler, fractol);
	mlx_hook(fractol->win, 4, (1L << 2), mouse_handler, fractol);
	mlx_hook(fractol->win, 6, (1L << 6), mouse_handler2, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
