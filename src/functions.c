#include "../fractol.h"

void		julia(t_fractol *fr, int x, int y)
{
	fr->c = fr->julia_c;
	mandelbrot(fr, x, y);
}

void		mandelbrot(t_fractol *fr, int x, int y)
{
	t_complex	a;
	t_complex	aa;
	int			i;

	a.re = fr->reoff + x * fr->centerx;
	a.im = fr->imoff + (HEIGHT - y) * fr->centery;
	!(fr->julia) ? fr->c.re = a.re : 0;
	!(fr->julia) ? fr->c.im = a.im : 0;
	i = fr->iter;
	while ((i--) > 0 && (a.re * a.re + a.im * a.im) < 4)
	{
		aa.re = a.re * a.re - a.im * a.im;
		aa.im = 2 * a.re * a.im;
		a.re = aa.re + fr->c.re;
		a.im = aa.im + fr->c.im;
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
	else
		put_pxl(fr, x, y,
			interp_color(0x45145A, 0xFF5300, ((float)(fr->iter - i) / fr->iter)));
}

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

void		newton(t_fractol *fr, int x, int y)
{
	t_complex		z;
	int				i;
	int				j;
	t_complex		diff;
	const t_complex	roots[3] =
	{
		compl(1, 0),
		compl(-0.5, sqrt(3)/2),
		compl(-0.5, -sqrt(3)/2)
	};
	int				colors[3] =
	{
		0xFF5533,
		0xFF55,
		0x3355FF
	};

	z = compl(fr->reoff + x * fr->centerx,
		fr->imoff + (HEIGHT - y) * fr->centery);
	i = fr->iter;
	while ((i--) > 0)
	{
		z = cx_sub(z, cx_div(cx_func(z), cx_deriv(z)));
		j = -1;
		while ((++j) < 3)
		{
			diff = compl(z.re - roots[j].re, z.im - roots[j].im);
			if (fabs(diff.re) < TOLER && fabs(diff.im) < TOLER)
				return (put_pxl(fr, x, y, colors[j]));
		}
	}
	put_pxl(fr, x, y, BLACK);
}
