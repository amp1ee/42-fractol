#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include "../libft/libft.h"

#define 	WIDTH						600
#define 	HEIGHT						400
#define 	KB_Esc						0xff1b
#define		KB_X						120
#define		KB_Z						122
#define 	KB_Up						65362
#define		KB_Down						65364
#define 	KB_Left						65361
#define		KB_Right					65363
#define 	KP_Add                      0xffab
#define		KP_Subtract					0xffad
#define 	KB_i                        0x0069
#define		KB_u						0x0075

#define		ITERATIONS					200

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
}				t_mlx;

void	*draw(t_mlx *mlx_p);

int		key_handler(int keycode, void *param)
{
	t_mlx	*p;
	float	step;		

	p = (t_mlx *)param;
	printf("n = %d\n", p->n);
	step = p->step;
	if (keycode == KB_Esc)
	{
		printf("Escape\n");
		mlx_destroy_window(p->mlx, p->window);
		p = NULL;
		exit(0);
	}
	else if (keycode == KP_Add) // Heavy Plus
		p->step *= 10;
	else if (keycode == KP_Subtract) // Heavy Minus
		p->step /= 10;
	else if (keycode == KB_X)
		(p->n) += 0.5 / step;
	else if (keycode == KB_Z)
		(p->n) -= 0.5 / step;
	else if (keycode == KB_Right)
		(p->ash) += step;
	else if (keycode == KB_Left)
		(p->ash) -= step;
	else if (keycode == KB_Up)
		(p->bsh) += step;
	else if (keycode == KB_Down)
		(p->bsh) -= step;
	else if (keycode == KB_i)
		p->iter *= 10;
	else if (keycode == KB_u)
		p->iter /= 10;
	if (p && keycode != 65293)
		draw(p);
	return (0);
}

int		rgb_to_int(int r, int g, int b)
{
	return (65536 * (r % 256) + 256 * (g % 256) + b % 256);
}

t_mlx	*init_fdf(void)
{
	void		*mlx;
	void		*window;
	t_mlx		*fdf;

	if (!(fdf = (t_mlx *)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx = mlx_init();
	window = mlx_new_window(mlx, WIDTH, HEIGHT, "Fils de fer");
	fdf->mlx = mlx;
	fdf->window = window;
	fdf->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	fdf->pxl = mlx_get_data_addr(fdf->img, &(fdf->bpp), &(fdf->s_line), &(fdf->ed));
	fdf->n = (double) HEIGHT / 2; // Size;
	fdf->ash = -2;
	fdf->bsh = 2;
	fdf->step = 0.05;
	fdf->iter = ITERATIONS;
	return (fdf);
}

int		main(void)
{
	t_mlx		*fdf;

	fdf = init_fdf();
	draw(fdf);
	mlx_key_hook(fdf->window, &key_handler, fdf);
	if (fdf)
		mlx_loop(fdf->mlx);
	return (0);
}

void	put_pxl(t_mlx *e, int x, int y, unsigned int c)
{
	int		i;

	if (x > WIDTH)
		x = WIDTH;
	if (y > HEIGHT)
		y = HEIGHT;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	i = (x * 4) + (y * e->s_line);
	e->pxl[i] = c;
	e->pxl[++i] = c >> 8;
	e->pxl[++i] = c >> 16;
}

void	*draw(t_mlx *fdf)
{
	int		i;
	int		x, y;
	float	ash, bsh;
	double	a, b, aa, bb, n;
	double	ca, cb;
	int		iter;

	x = 0;
	ash = fdf->ash;
	bsh = fdf->bsh;
	n = fdf->n;
	iter = fdf->iter;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
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
				put_pxl(fdf, x, y, 0);
			else
				put_pxl(fdf, x, y, 0xFFFFFF - (int) (((float)i / (float)iter) * 0xFFFFFF));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);

	return (NULL);
}