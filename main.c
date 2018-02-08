#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include "../libft/libft.h"

# define 	WIDTH					1280
# define 	HEIGHT					800

#ifdef __linux__
# define 	KB_ESC					0xff1b
# define	KB_X					120
# define	KB_Z					122
# define 	KB_UP					65362
# define	KB_DOWN					65364
# define 	KB_LEFT					65361
# define	KB_RIGHT				65363
# define 	KP_ADD                  0xffab
# define	KP_SUBTRACT				0xffad
# define 	KB_I                    0x0069
# define	KB_U					0x0075
#elif __APPLE__
# define KB_ESC						53
# define KB_X						7
# define KB_Z						6
# define KB_UP						126
# define KB_DOWN					125
# define KB_LEFT					123
# define KB_RIGHT					124
# define KP_ADD						69
# define KP_SUBTRACT				78
# define KB_I						34
# define KB_U						32
# define KP_4						86
# define KP_6						88
# define KP_8						91
# define KP_2						84
# define KB_W						13
# define KB_S						1
# define KB_H						4
#endif

#define	ITERATIONS				500
#define THREADS					16


typedef struct	s_mlx
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*pxl;
	int		bpp;
	int		s_line;
	int		ed;
	int		n;
	float	step;
	float	ash;
	float	bsh;
	int		iter;

	int		mx;
	int		my;
	int		parth;
	time_t	time;
}				t_mlx;

void	*draw(void *mlx_p);
void	get_threads(t_mlx *fr);

int		mouse_handler(int mx, int my, void *p)
{
	t_mlx	*fract;

	printf("T1 %ld\n", fract->time);
	if (fract->time == time(NULL))
	{
		printf("RET\n");
		return (0);
	}
	else
	{
		printf("GO ON\n");
		fract->time = time(NULL);
	}
	printf("Motion at %d, %d\n", mx, my);
	printf("T2 %ld\n", fract->time);
	fract = (t_mlx *)p;
	fract->mx = mx;
	fract->my = my;
	return (0);
}

int		key_handler(int keycode, void *param)
{
	t_mlx	*fract;
	float	step;		

	fract = (t_mlx *)param;

	step = fract->step;
	if (keycode == KB_ESC)
	{
		printf("Escape\n");
		mlx_destroy_window(fract->mlx, fract->window);
		fract = NULL;
		exit(0);
	}
	else if (keycode == KP_ADD) // Heavy Plus
		fract->step *= 10;
	else if (keycode == KP_SUBTRACT) // Heavy Minus
		fract->step /= 10;
	else if (keycode == KB_X)
		(fract->n) += 0.5 / step;
	else if (keycode == KB_Z)
		(fract->n) -= 0.5 / step;
	else if (keycode == KB_RIGHT)
		(fract->ash) -= step;
	else if (keycode == KB_LEFT)
		(fract->ash) += step;
	else if (keycode == KB_UP)
		(fract->bsh) -= step;
	else if (keycode == KB_DOWN)
		(fract->bsh) += step;
	else if (keycode == KB_I)
		fract->iter = 1.1 * fract->iter;
	else if (keycode == KB_U)
		fract->iter = 0.9 * fract->iter;
	if (fract && keycode != 65293)
		get_threads(fract);
	printf("%d\n", fract->iter);
	return (0);
}

int		rgb_to_int(int r, int g, int b)
{
	return (65536 * (r % 256) + 256 * (g % 256) + b % 256);
}

t_mlx	*init_fract(void)
{
	void		*mlx;
	void		*window;
	t_mlx		*fract;

	if (!(fract = (t_mlx *)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx = mlx_init();
	window = mlx_new_window(mlx, WIDTH, HEIGHT, "Fract'ol");
	fract->mlx = mlx;
	fract->window = window;
	fract->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	fract->pxl = mlx_get_data_addr(fract->img, &(fract->bpp), &(fract->s_line), &(fract->ed));
	fract->n = (double) HEIGHT / 2;
	fract->ash = -2;
	fract->bsh = 2;
	fract->step = 0.05;
	fract->iter = ITERATIONS;
	return (fract);
}

int		main(void)
{
	t_mlx		*fract;

	fract = init_fract();
	get_threads(fract);
	mlx_hook(fract->window, 2, 5, &key_handler, fract);

	fract->time = time(NULL);
	mlx_hook(fract->window, 6, (1L<<6), &mouse_handler, fract);
	if (fract)
		mlx_loop(fract->mlx);
	return (0);
}

void	put_pxl(t_mlx *fract, int x, int y, unsigned int c)
{
	int		i;

	if (x >= WIDTH || y >= WIDTH || x < 0 || y < 0)
		return ;
	i = (x * 4) + (y * fract->s_line);
	fract->pxl[i] = c;
	fract->pxl[++i] = c >> 8;
	fract->pxl[++i] = c >> 16;
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
//	printf("start=%d perc=%.3f res=%d\n", start, perc, res);
	return (res);
}

int		interp_color(int c1, int c2, float perc)
{
	int		r;
	int		g;
	int		b;

	r = interp_i(c1 >> 16, c2 << 16, perc);
	g = interp_i((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, perc);
	b = interp_i(c1 & 0xFF, c2 & 0xFF, perc);
	
	return ((r << 16) | (g << 8) | b);
}

void	*draw(void *fr)
{
	int		i;
	int		x, y;
	float	ash, bsh;
	double	a, b, aa, bb, n;
	double	ca, cb;
	int		iter;
	t_mlx	*fract = (t_mlx *)fr;

	x = 0 + fract->mx;
	ash = fract->ash;
	bsh = fract->bsh;
	n = fract->n;
	iter = fract->iter;
	while (x < WIDTH)
	{
		y = fract->parth + fract->my;
		while (y < fract->parth + HEIGHT / THREADS)
		{
			a = ash + (x / n);
			b = bsh - (y / n);
			ca = a;
			cb = b;
			i = 1;
			while (i <= iter)
			{
				aa = a * a - b * b;
				bb = 2 * a * b;
				a = aa + ca;
				b = bb + cb;
				if (a*a + b*b > 4)
					break;
				i++;
			}
			if (i == iter + 1)
				put_pxl(fract, x - fract->mx, y - fract->my, 0);
			else
//				put_pxl(fract, x, y, 0xFFFFFF - (int) (((float)i / (float)iter) * 0xd4c2e0));
				put_pxl(fract, x - fract->mx, y - fract->my, interp_color(0xFADCAB, 0x55CCAA, ((float)i / (float)iter)));
			y++;
		}
		x++;
	}
	return (NULL);
}

float		map(float value, float a0, float a1, float b0, float b1)
{
	float	perc;

	if (a0 == a1 || b0 == b1)
		return (b0);
	perc = value / (a1 - a0);
	if (perc == 0.0)
		return (b0);
	if (perc == 1.0)
		return (b1);
	return ((1 - perc) * b0 + perc * b1);
}


void		get_threads(t_mlx *fr)
{
	pthread_t		thr[THREADS];
	t_mlx			frax[THREADS];
	int				i;
	int				part;

	i = 0;
	int y = 0;
	while (i < THREADS)
	{	
		frax[i] = *fr;
		frax[i].parth = y;
		y = map(i + 1, 0, THREADS, 0, HEIGHT);
		pthread_create(&thr[i], NULL, draw, (void *)&frax[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(thr[i], NULL);
	mlx_put_image_to_window(fr->mlx, fr->window, fr->img, 0, 0);

}
/*
void threads_create(t_map *map)
{
 pthread_t threads[THREADS];
 t_map  info[THREADS];
 unsigned y;
 int   i;
 char  *str;

 i = -1;
 y = 0;
 while (++i < THREADS)
 {
  info[i] = *map;
  info[i].cunt = y;
  y += HEIGHT / THREADS;
  info[i].end = y;
  pthread_create(&threads[i], NULL,
        (void *(*)(void *))draw, (void *)&info[i]);
 }
 while (i-- > 0)
  map->status = pthread_join(threads[i], (void**)&map->status_addr);
 mlx_put_image_to_window(map->mlx, map->win, map->image_ptr, 0, 0);
 mlx_string_put(map->mlx, map->win, 10, 10, 0xFF0000,
        (str = ft_itoa(map->fps.frame_time)));
 ft_strdel(&str);
}

*/































