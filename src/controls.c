#include "../fractol.h"

static void	zoom(t_fractol *fr, char action)
{
	if (action == '+')
	{
		fr->zoom *= 1.05;
		fr->step *= 0.95;
		if (fr->iter < 9999)
				fr->iter += 4;
	}
	else if (action == '-')
	{	
		fr->zoom *= 0.95;
		fr->step *= 1.05;
		if (fr->iter > 50)
				fr->iter -= 4;
	}
}

void		reset_fractol(t_fractol *fr)
{
	fr->zoom = (double) HEIGHT / 2;
	fr->reoff = -3;
	fr->imoff = -2;
	fr->step = 0.1;
	fr->iter = ITERATIONS;
	fr->julia_fixed = 0;
}

int			key_handler(int key, t_fractol *fr)
{
	t_complex	corr;
	double		d;
	if (key == KB_ESC)
	{
		exiterror("Exit by user", fr);
		return (1);
	}
	else if (key == KP_ADD)
		fr->step *= 10;
	else if (key == KP_SUBTRACT)
		fr->step /= 10;
	else if (key == KB_X || key == KB_Z)
	{
		d = 2 * HEIGHT / fr->zoom;
		corr.re = fr->reoff + ((float)fr->mpos.re / WIDTH) * d * 1.5;
		corr.im = fr->imoff + ((HEIGHT - (float)fr->mpos.im) / HEIGHT) * d;
		if (key == KB_X)
			zoom(fr, '+');
		else
			zoom(fr, '-');
		d = 2 * HEIGHT / fr->zoom;
		fr->reoff = corr.re - ((float)fr->mpos.re / WIDTH) * d * 1.5;
		fr->imoff = corr.im - ((HEIGHT - (float)fr->mpos.im) / HEIGHT) * d;
	}
	else if (key == KB_RIGHT)
		(fr->reoff) -= fr->step;
	else if (key == KB_LEFT)
		(fr->reoff) += fr->step;
	else if (key == KB_UP)
		(fr->imoff) -= fr->step;
	else if (key == KB_DOWN)
		(fr->imoff) += fr->step;
	else if (key == KB_I && (1.05 * fr->iter) < 9999)
		fr->iter *= 1.05;
	else if (key == KB_U && (0.95 * fr->iter) > 50)
		fr->iter *= 0.95;
	else if (key == KB_R)
		reset_fractol(fr);
	else if (key == KB_F)
		fr->julia_fixed = !fr->julia_fixed;
	else if (key == KP_4)
		fr->color = interp_color;
	else if (key == KP_6)
		fr->color = interp_color2;
	get_threads(fr);
	return (0);
}

int			mouse_handler2(int mx, int my, t_fractol *fr)
{
	if (fr->julia_fixed == 0)
	{
		fr->c = compl(4 * ((float)mx / WIDTH - 0.5),
			4 * ((float)(HEIGHT - my) / HEIGHT - 0.5));
		get_threads(fr);
	}
	fr->mpos = compl(mx, my);
	return (0);
}

int			mouse_handler(int key, int mx, int my, t_fractol *fr)
{
	t_complex	corr;
	double		d;

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
		get_threads(fr);
	}
	return (0);
}