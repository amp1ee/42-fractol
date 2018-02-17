#include "../fractol.h"

void		print_info(t_fractol *fr)
{
	char		*frstep;
	const char	*str[3] = {	" * 10e-3", 
							" * 10e-6",
							" * 10e-9" };
	const int	len = snprintf(NULL, 0, "%.3f %s", fr->step, str[0]);
	const int	prefix[3] = {1000, pow(1000, 2), pow(1000, 3)};
	int			i;

	frstep = ft_strnew(len);
	if (fr->step >= 0.001)
		i = 0;
	else if (fr->step < 0.001 && fr->step >= 0.000001)
		i = 1;
	else
		i = 2;
	snprintf(frstep, len + 3, "%.3f%s", prefix[i] * fr->step, str[i]);
	mlx_string_put(fr->mlx, fr->win, 20, 40, WHITE, frstep);

}

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
	int			x, y;	

	t_fractol	*fr = (t_fractol *)fract;
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
	int				ret;
	int				y;

	fr->centerx = (3 * HEIGHT / (fr->zoom * WIDTH));
	fr->centery = 2 / fr->zoom;
	i = 0;
	y = 0;
	while (i < THREADS)
	{	
		frx[i] = *fr;
		frx[i].parth = y;
		y += fr->hstep;
		if ((ret = pthread_create(&thr[i], NULL, drawthr, (void *)&frx[i])))
			exiterror(ft_strjoin(PCREA_ERR, ft_itoa(ret)), fr);
		i++;
	}
	while (i-- > 0)
		if ((ret = pthread_join(thr[i], NULL)))
			exiterror(ft_strjoin(PJOIN_ERR, ft_itoa(ret)), fr);
	mlx_put_image_to_window(fr->mlx, fr->win, fr->img, 0, 0);
	mlx_string_put(fr->mlx, fr->win, 20, 20, WHITE, ft_itoa(fr->iter));
	print_info(fr);
}

/*
void		*drawthr(void *fract)
{
	int			i;
	int			x, y;
	float		reoff, imoff;
	double		a, b, aa, bb, n;
	double		ca, cb;
	int			iter;
	t_fractol	*fr = (t_fractol *)fract;
	
	x = 0;
	ash = fr->ash;
	bsh = fr->bsh;
	n = fr->zoom;
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
			i = 0;
			while (i < iter && (a * a + b * b) <= 4)
			{
				aa = a * a - b * b;
				bb = 2 * a * b;
				a = aa + ca;
				b = bb + cb;
				i++;
			}
			if (i == iter)
				put_pxl(fr, x, y, BLACK);
			else
				put_pxl(fr, x, y,
					interp_color(0x45145A, 0xFF5300, ((float)i / iter)));
			y++;
		}
		x++;
	}
	pthread_exit(0);
	return (NULL);
}
*/