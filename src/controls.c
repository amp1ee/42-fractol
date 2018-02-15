#include "../fractol.h"

static void	countzooms(t_fractol *fr, char action)
{
	if (action == '+' && fr->i < 9999)
	{
		fr->i++;
		if (fr->step > 0.0001)
			fr->step *= 0.995f;
	}
	else if (action == '-' && fr->i > 50)
	{	
		fr->i--;
		if (fr->step < 10)
			fr->step *= 1.005f;
	}
}

void		reset_fractol(t_fractol *fr)
{
	fr->n = (double) HEIGHT / 2;
	fr->ash = -0.5;
	fr->bsh = 0;
	fr->step = 0.05;
	fr->iter = ITERATIONS;
}

int			key_handler(int key, void *param)
{
	t_fractol	*fr;
	float	step;		

//	printf("%d\n", key);
	fr = (t_fractol *)param;
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
	else if (key == KB_I && (1.05 * fr->iter) < 9999)
		fr->iter *= 1.05;
	else if (key == KB_U && (0.95 * fr->iter) > 50)
		fr->iter *= 0.95;
	else if (key == KB_R)
		reset_fractol(fr);
	get_threads(fr);
	//printf("%.3f %.3f\n", fr->ash, fr->bsh);
	return (0);
}

int			mouse_handler(int key, int mx, int my, void *p)
{
	t_fractol	*fr;

	fr = (t_fractol *)p;
	//(void)mx, (void)my;
	if (key == 4 || key == 5)
	{
		fr->mx = mx;
		fr->my = my;
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
		get_threads(fr);
	}
	return (0);
}