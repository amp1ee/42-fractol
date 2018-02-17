#include "../fractol.h"

static void	zoom(t_fractol *fr, char action)
{
	if (action == '+')
	{
		fr->zoom *= 1.05;
		if (fr->iter < 9999)
				fr->iter++;
	}
	else if (action == '-')
	{	
		fr->zoom *= 0.95;
		if (fr->iter > 50)
				fr->iter--;
	}
}

void		reset_fractol(t_fractol *fr)
{
	fr->zoom = (double) HEIGHT / 2;
	fr->reoff = -3;
	fr->imoff = -2;
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
		zoom(fr, '+');
	else if (key == KB_Z)
		zoom(fr, '-');
	else if (key == KB_RIGHT)
		(fr->reoff) -= step;
	else if (key == KB_LEFT)
		(fr->reoff) += step;
	else if (key == KB_UP)
		(fr->imoff) -= step;
	else if (key == KB_DOWN)
		(fr->imoff) += step;
	else if (key == KB_I && (1.05 * fr->iter) < 9999)
		fr->iter *= 1.05;
	else if (key == KB_U && (0.95 * fr->iter) > 50)
		fr->iter *= 0.95;
	else if (key == KB_R)
		reset_fractol(fr);
	get_threads(fr);
	return (0);
}

int			mouse_handler(int key, int mx, int my, void *p)
{
	t_fractol	*fr;
	t_complex	corr;
	double		d;

	fr = (t_fractol *)p;
	d =  2 * HEIGHT / fr->zoom;
	if (key == 4 || key == 5)
	{
		corr.re = fr->reoff + ((float)mx / WIDTH) * d * 1.5;
		corr.im = fr->imoff + ((HEIGHT - (float)my) / HEIGHT) * d;
		if (key == 4)
			zoom(fr, '+');
		if (key == 5)
			zoom(fr, '-');	
		d = 2 * HEIGHT / fr->zoom;
		fr->reoff = corr.re - ((float)mx / WIDTH) * d * 1.5;
		fr->imoff = corr.im - ((HEIGHT - (float)my) / HEIGHT) * d;
	}
	get_threads(fr);
	return (0);
}