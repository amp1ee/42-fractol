#include "../fractol.h"

void		print_info(t_fractol *fr)
{
	char		*frstep;
	const char	*str[3] = {	" * 10^-3", 
							" * 10^-6",
							" * 10^-9" };
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

static void	put_pxl(t_fractol *fr, int x, int y, unsigned int c)
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
	int		i;
	int		x, y;
	float	ash, bsh;
	double	a, b, aa, bb, n;
	double	ca, cb;
	int		iter;
	t_fractol	*fr = (t_fractol *)fract;

	x = -WIDTH / 2; 
	ash = fr->ash;
	bsh = fr->bsh;
	n = fr->n;
	iter = fr->iter;
	while (x < WIDTH / 2)
	{
		y = fr->parth - HEIGHT /2;
		while (y <= fr->parth + HEIGHT / THREADS - HEIGHT /2)
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
				put_pxl(fr, x + WIDTH/2, y + HEIGHT/2, BLACK);
			else
				put_pxl(fr, x + WIDTH/2, y + HEIGHT/2, interp_color(0x45145A, 0xFF5300, ((float)i / iter)));
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
