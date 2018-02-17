#include "fractol.h"

void	julia(t_fractol *fr, int x, int y)
{
	fr->c.re = -0.123;
	fr->c.im = 0.745;
	mandelbrot(fr, x, y);
}

void	mandelbrot(t_fractol *fr, int x, int y)
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

t_complex	compl(double re, double im)
{
	t_complex	new;

	new.re = re;
	new.im = im;
	return (new);
}

void	newton(t_fractol *fr, int x, int y)
{
	t_complex	z;
	int			i;
	double		a, b;

	t_complex roots[3] = //Roots (solutions) of the polynomial
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
	i = fr->iter;
	double tol = 0.000001;
	while ((i--) > 0)
	{
		a = z.re;
		b = z.im;
		z.re -= ((a*a*a - 3*a*b*b) - 1) / (3 * (a*a - b*b));
		z.im -= (3*a*a*b - b*b*b) / (6 * a*b);
		int j = 0;
		while (j < 3)
		{
			t_complex diff = compl(z.re - roots[j].re, z.im - roots[j].im);
			if (abs(diff.re) < tol && abs(diff.im) < tol)
			{
				put_pxl(fr, x, y, colors[j]);
				return ;
			}
			j++;
		}
	}
	put_pxl(fr, x, y, BLACK);
}