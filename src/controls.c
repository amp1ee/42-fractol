/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:58:23 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:58:25 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom(t_fractol *fr, int key)
{
	double		d;
	t_complex	corr;

	d = 2 * HEIGHT / fr->zoom;
	corr.re = fr->reoff + ((float)fr->mpos.re / WIDTH) * d * 1.5;
	corr.im = fr->imoff + ((HEIGHT - (float)fr->mpos.im) / HEIGHT) * d;
	if (key == KB_X || key == MWHEELUP)
	{
		fr->zoom *= 1.05;
		fr->step *= 0.95;
		if (fr->iter < ITERS_MAX)
			fr->iter += 2;
	}
	else
	{
		fr->zoom *= 0.95;
		fr->step *= 1.05;
		if (fr->iter > ITERS_MIN)
			fr->iter -= 2;
	}
	d = 2 * HEIGHT / fr->zoom;
	fr->reoff = corr.re - ((float)fr->mpos.re / WIDTH) * d * 1.5;
	fr->imoff = corr.im - ((HEIGHT - (float)fr->mpos.im) / HEIGHT) * d;
}

static void	move(t_fractol *fr, int key)
{
	if (key == KB_RIGHT)
		fr->reoff -= fr->step;
	else if (key == KB_LEFT)
		fr->reoff += fr->step;
	else if (key == KB_UP)
		fr->imoff -= fr->step;
	else if (key == KB_DOWN)
		fr->imoff += fr->step;
}

int			key_handler(int key, t_fractol *fr)
{
	if (key == KB_ESC)
		exiterror("\b", fr);
	else if (key == KP_ADD)
		fr->step *= 10;
	else if (key == KP_SUBTRACT)
		fr->step /= 10;
	else if (key == KB_X || key == KB_Z)
		zoom(fr, key);
	else if (key == KB_RIGHT || key == KB_DOWN ||
		key == KB_LEFT || key == KB_UP)
		move(fr, key);
	else if (key == KB_I && (1.05 * fr->iter) < 9999)
		fr->iter *= 1.05;
	else if (key == KB_U && (0.95 * fr->iter) > 50)
		fr->iter *= 0.95;
	else if (key == KB_R)
		reset_fractol(fr);
	else if (key == KB_F)
		fr->julia_fixed = !fr->julia_fixed;
	else if (key == KP_4 || key == KP_2)
		change_color(fr, key);
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
	if (key == 4 || key == 5)
	{
		fr->mpos = compl(mx, my);
		zoom(fr, key);
		get_threads(fr);
	}
	return (0);
}
