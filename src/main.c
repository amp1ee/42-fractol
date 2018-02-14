#include "../fractol.h"

void	*exiterror(char *reason, t_mlx *fr)
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

t_mlx	*init_fractol(void)
{
	t_mlx		*fr;

	if ((fr = (t_mlx *)malloc(sizeof(t_mlx))) == NULL ||
	(fr->mlx = mlx_init()) == NULL ||
	(fr->win = mlx_new_window(fr->mlx, WIDTH, HEIGHT, "Fract'ol")) == NULL ||
	(fr->img = mlx_new_image(fr->mlx, WIDTH, HEIGHT)) == NULL ||
	(fr->pxl = mlx_get_data_addr(fr->img, &(fr->bpp),
		&(fr->s_line), &(fr->ed))) == NULL)
		return (exiterror(MLX_ERR, fr));
	fr->n = (double) HEIGHT / 2;/*
	while (fr->w_height % THREADS != 0)
		fr->w_height++;*/
	fr->ash = -2;
	fr->bsh = 1;
	fr->step = 0.05;
	fr->iter = ITERATIONS;
	return (fr);
}

int		main(void)
{
	t_mlx		*fractol;

	if ((fractol = init_fractol()) == NULL)
		return (-1);
	get_threads(fractol);
	mlx_hook(fractol->win, 2, 5, &key_handler, fractol);
	mlx_hook(fractol->win, 4, (1L<<2), &mouse_handler, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}

void	put_pxl(t_mlx *fr, int x, int y, unsigned int c)
{
	int		i;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	i = (x * 4) + (y * fr->s_line);
	fr->pxl[i] = c;
	fr->pxl[++i] = c >> 8;
	fr->pxl[++i] = c >> 16;
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

void	*drawthr(void *fract)
{
	int		i;
	int		x, y;
	float	ash, bsh;
	double	a, b, aa, bb, n;
	double	ca, cb;
	int		iter;
	t_mlx	*fr = (t_mlx *)fract;

	x = 0; 
	ash = fr->ash;
	bsh = fr->bsh;
	n = fr->n;
	iter = fr->iter;
	while (x < WIDTH)
	{
		y = fr->parth;
		while (y <= fr->parth + HEIGHT / THREADS)
		{
			a = ash + (x / n);
			b = bsh - (y / n);
			ca = a;
			cb = b;
			i = 1;
			while (i <= iter && (a * a + b * b) <= 4)
			{
				aa = a * a - b * b;
				bb = 2 * a * b;
				a = aa + ca;
				b = bb + cb;
				i++;
			}
			if (i == iter + 1)
				put_pxl(fr, x, y, BLACK);
			else
				put_pxl(fr, x, y, interp_color(0x45145A, 0xFF5300, ((float)i / iter)));
			y++;
		}
		x++;
	}
	pthread_exit(0);
	return (NULL);
}

void		print_info(t_mlx *fr)
{
	char		*frstep;
	const char	*str[3] = {	" * 10^-3", 
							" * 10^-6",
							" * 10^-9" };
	const int	len = snprintf(NULL, 0, "%.3f %s", fr->step, str[0]);
	const int	prefix[3] = {1000, pow(1000, 2), pow(1000, 3)};
	int			i;

	frstep = ft_strnew(len);
	if (fr->step > 0.001)
		i = 0;
	else if (fr->step < 0.001 && fr->step > 0.000001)
		i = 1;
	else
		i = 2;
	snprintf(frstep, len + 3, "%.3f%s", prefix[i] * fr->step, str[i]);
	mlx_string_put(fr->mlx, fr->win, 20, 40, WHITE, frstep);

}

void		get_threads(t_mlx *fr)
{
	pthread_t		thr[THREADS];
	t_mlx			frx[THREADS];
	int				i;
	int				ret;
	int				y;

	i = 0;
	y = 0;
	while (i < THREADS)
	{	
		frx[i] = *fr;
		frx[i].parth = y;
		y = ft_map(i + 1, 0, THREADS, 0, HEIGHT);
		if ((ret = pthread_create(&thr[i], NULL, drawthr, (void *)&frx[i])))
			exiterror(ft_strcat(PCREA_ERR, ft_itoa(ret)), NULL);
		i++;
	}
	while (i-- > 0)
		if ((ret = pthread_join(thr[i], NULL)))
			exiterror(ft_strcat(PJOIN_ERR, ft_itoa(ret)), NULL);
	mlx_put_image_to_window(fr->mlx, fr->win, fr->img, 0, 0);
	mlx_string_put(fr->mlx, fr->win, 20, 20, WHITE, ft_itoa(fr->iter));
	print_info(fr);
}
