#include "../fractol.h"

void	*exiterror(char *reason, t_fractol *fr)
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

t_fractol	*init_fractol(char *title)
{
	t_fractol		*fr;

	if ((fr = (t_fractol *)malloc(sizeof(*fr))) == NULL ||
	(fr->mlx = mlx_init()) == NULL ||
	(fr->win = mlx_new_window(fr->mlx, WIDTH, HEIGHT, title)) == NULL ||
	(fr->img = mlx_new_image(fr->mlx, WIDTH, HEIGHT)) == NULL ||
	(fr->pxl = mlx_get_data_addr(fr->img, &(fr->bpp),
		&(fr->s_line), &(fr->ed))) == NULL)
		return (exiterror(MLX_ERR, fr));
	fr->zoom = (double) HEIGHT / 2;
	fr->reoff = -3;
	fr->imoff = -2;
	fr->step = 0.05;
	fr->hstep = HEIGHT / THREADS;
	fr->iter = ITERATIONS;
	fr->julia_fixed = 0;
	return (fr);
}

int		interp_i(int start, int end, double perc)
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

int		interp_color(int c1, int c2, float perc)
{
	int		r;
	int		g;
	int		b;

	r = interp_i(c1 >> 16, c2 >> 16, perc);
	g = interp_i((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, perc);
	b = interp_i(c1 & 0xFF, c2 & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}

void	check_args(int ac, char **av, t_fractol *f)
{
	f->julia = 0;
	if (ac > 1)
	{
		if (!(ft_strcmp(av[1], "newton")))
			f->fun = newton;
		else if (!(ft_strcmp(av[1], "julia")))
		{
			f->fun = julia;
			f->julia = 1;
		}
		else
			f->fun = mandelbrot;
	}
	else
		f->fun = mandelbrot;
}

int		main(int ac, char **av)
{
	t_fractol		*fractol;

 	if ((fractol = init_fractol("Fract'ol")) == NULL)
		return (-1);
	check_args(ac, av, fractol);
	get_threads(fractol);
	mlx_hook(fractol->win, 2, 5, &key_handler, fractol);
	mlx_hook(fractol->win, 4, (1L<<2), &mouse_handler, fractol);
	mlx_hook(fractol->win, 6, (1L<<6), &mouse_handler2, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}