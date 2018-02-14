#include "../fractol.h"

static void	countzooms(t_mlx *fr, char action)
{
	if (action == '+' && fr->i < 9999)
	{
		fr->i++;
		if (fr->step > 0.001)
			fr->step *= 0.995f;
	}
	else if (action == '-' && fr->i > 50)
	{	
		fr->i--;
		if (fr->step < 10)
			fr->step *= 1.005f;
	}
}

void		reset_fractol(t_mlx *fr)
{
	fr->n = (double) HEIGHT / 2;
	fr->ash = -2;
	fr->bsh = 1;
	fr->step = 0.05;
	fr->iter = ITERATIONS;
}

int			key_handler(int key, void *param)
{
	t_mlx	*fr;
	float	step;		

//	printf("%d\n", key);
	fr = (t_mlx *)param;
	step = fr->step;
	if (key == KB_ESC)
	{
		exiterror("Exit by user", fr);
		return (1);
	}
	else if (key == KP_ADD)
		fr->step *= 10;
	else if (key == KP_SUBTRACT)
		fr->step /= 10;
	else if (key == KB_X)
	{
		(fr->n) += 0.5 / step;
		countzooms(fr, '+');
		if ((fr->i % 20) == 0 && fr->iter < 9999)
			fr->iter++;
	}
	else if (key == KB_Z)
	{
		(fr->n) -= 0.5 / step;
		countzooms(fr, '-');
		if ((fr->i % 20) == 0 && fr->iter > 50)
			fr->iter--;
	}
	else if (key == KB_RIGHT)
		(fr->ash) -= step;
	else if (key == KB_LEFT)
		(fr->ash) += step;
	else if (key == KB_UP)
		(fr->bsh) -= step;
	else if (key == KB_DOWN)
		(fr->bsh) += step;
	else if (key == KB_I && (1.1 * fr->iter) < 9999)
		fr->iter *= 1.1;
	else if (key == KB_U && (0.9 * fr->iter) > 50)
		fr->iter *= 0.9;
	else if (key == KB_R)
		reset_fractol(fr);
	get_threads(fr);
	return (0);
}

int			mouse_handler(int key, int mx, int my, void *p)
{
	t_mlx	*fr;

	(void)mx;
	(void)my;
	fr = (t_mlx *)p;

	if (key == 4 || key == 5)
	{
		if (key == 4)
		{
			fr->n += 0.5 / fr->step;
			countzooms(fr, '+');
			if ((fr->i % 20) == 0 && fr->iter < 9999)
				fr->iter++;
		}
		if (key == 5)
		{
			fr->n -= 0.5 / fr->step;
			countzooms(fr, '-');
			if ((fr->i % 20) == 0 && fr->iter > 50)
				fr->iter--;
		}
	}
	get_threads(fr);
	return (0);
}