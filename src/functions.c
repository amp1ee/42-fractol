#include "../fractol.h"

t_complex	cx_func(t_complex z)
{
	z = cx_sub(cx_pow(z, 3), compl(1, 0));
	return (z);
}

t_complex	cx_prederiv(t_complex z)
{
	z = cx_add(z, compl(TOLER, 0));
	return (cx_func(z));
}

t_complex	cx_deriv(t_complex z)
{
	t_complex	c;

	c = cx_prederiv(z);
	c = cx_sub(c, cx_func(z));
	c = cx_mul_sc(c, (1.0 / TOLER));
	return (c);
}

void		mandelbrot(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	if (fr->julia == 0)
		fr->c = compl(a.re, a.im);
	i = fr->iter;
	while ((i--) > 0 && (a.re * a.re + a.im * a.im) < 4)
	{
		aa = cx_pow(a, 2);
		a = cx_add(aa, fr->c);
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y, fr->color(fr->colormode,
			((float)(fr->iter - i) / fr->iter)));
}

void		something(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	fr->c = compl(a.re, a.im);
	i = fr->iter;
	while ((i--) > 0 && (a.re * a.re + a.im * a.im) < 4)
	{
		aa = cx_cos(cx_pow(a, 3));
		a = cx_add(aa, fr->c);
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y, fr->color(fr->colormode,
			((float)(fr->iter - i) / fr->iter)));
}

void		mandelbar(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	fr->c = compl(a.re, a.im);
	i = fr->iter;
	while ((i--) > 0 && (a.re * a.re + a.im * a.im) < 4)
	{
		aa = cx_pow(a, 2);
		a = (cx_add(cx_conj(aa), fr->c));
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y, fr->color(fr->colormode,
			((float)(fr->iter - i) / fr->iter)));
}

void		burning(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	fr->c = compl(a.re, a.im);
	i = fr->iter;
	while ((i--) > 0 && (a.re * a.re + a.im * a.im) < 4)
	{
		aa.re = (a.re * a.re) - (a.im * a.im);
		aa.im = -2 * fabs(a.re) * fabs(a.im);
		a = cx_add(aa, fr->c);
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y, fr->color(fr->colormode,
			((float)(fr->iter - i) / fr->iter)));
}

void		newton(t_fractol *fr, int x, int y)
{
	const t_complex	roots[3] = {
		compl(1, 0),
		compl(-0.5, sqrt(3) / 2),
		compl(-0.5, -sqrt(3) / 2) };
	const int		colors[3] = {
		0xFF5533, 0xFF55, 0x33FF };
	t_complex		z;
	int				i;
	int				j;

	z = compl(fr->reoff + x * fr->centerx,
		fr->imoff + (HEIGHT - y) * fr->centery);
	i = fr->iter;
	while ((i--) > 0)
	{
		z = cx_sub(z, cx_div(cx_func(z), cx_deriv(z)));
		j = -1;
		while ((++j) < 3)
		{
			if (fabs(z.re - roots[j].re) < TOLER &&
				fabs(z.im - roots[j].im) < TOLER)
				return (put_pxl(fr, x, y, colors[j]));
		}
	}
	put_pxl(fr, x, y, BLACK);
}
