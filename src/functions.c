#include "fractol.h"

void		julia(t_fractol *fr, int x, int y)
{
	fr->c.re = -0.123;
	fr->c.im = 0.745;
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
/*	else if (i > 0.8 * fr->iter)
		put_pxl(fr, x, y, 0xFF5300 - ((float)(fr->iter - i) / fr->iter) * 0xFF5300);
*/
}

#define H 1e-8

t_complex	cx_func(t_complex z)
{
	z = cx_sub(cx_pow(z, 3), compl(1, 0));
	return (z);
}

t_complex	cx_prederiv(t_complex z)
{
	z = cx_add(z, compl(H, 0));
	return (cx_func(z));
}

t_complex	cx_deriv(t_complex z)
{
	t_complex	c;

	c = cx_prederiv(z);
	c = cx_sub(c, cx_func(z));
	c = cx_mul_sc(c, (1.0 / H));
	return (c);
}

void		newton(t_fractol *fr, int x, int y)
{
	t_complex	z;

	t_complex roots[3] =
	{
		compl(1, 0),
		compl(-0.5, sqrt(3)/2),
		compl(-0.5, -sqrt(3)/2)
	};
	int colors[3] =
	{
		0xFF0000,
		0xFF00,
		0xFF
	};
	z.re = ft_map(x, 0, WIDTH, -2.5, 1);
	z.im = ft_map(y, 0, HEIGHT, -1, 1);
	int i = 500; //fr->iter;
	double tol = 1e-6;
	while ((i--) > 0)
	{
		t_complex der = cx_deriv(z);
		t_complex fun = cx_func(z);
		z = cx_sub(z, cx_div(fun, der));
		int j = 0;
		while (j < 3)
		{
			t_complex diff = compl(z.re - roots[j].re, z.im - roots[j].im);
			if (fabs(diff.re) < tol && fabs(diff.im) < tol)
			{
				put_pxl(fr, x, y, colors[j]);
				i = -2;
				break ;
			}
			j++;
		}
	}
	if (i == -1)
		put_pxl(fr, x, y, BLACK);
}
