#include "../fractol.h"

t_complex	compl(double re, double im)
{
	t_complex	new;

	new.re = re;
	new.im = im;
	return (new);
}

t_complex	cx_add(t_complex c0, t_complex c1)
{
	return (compl(c0.re + c1.re, c0.im + c1.im));
}

t_complex	cx_sub(t_complex c0, t_complex c1)
{
	return (compl(c0.re - c1.re, c0.im - c1.im));
}

t_complex	cx_mul_cx(t_complex c0, t_complex c1)
{
	return (compl(c0.re * c1.re - c0.im * c1.im, c0.re * c1.im + c0.im * c1.re));
}

t_complex	cx_mul_sc(t_complex c, double scalar)
{
	return (compl(c.re * scalar, c.im * scalar));
}

t_complex	cx_div(t_complex c0, t_complex c1)
{
	t_complex c;

	c = cx_mul_sc(cx_conj(c1), (1.0 / (c1.re * c1.re + c1.im * c1.im)));
	return (cx_mul_cx(c0, c));
}

t_complex	cx_pow(t_complex c, int pow)
{
	t_complex	res;

	res = c;
	while (--pow)
		res = cx_mul_cx(res, c);
	return (res);
}

t_complex	cx_conj(t_complex c)
{
	return (compl(c.re, c.im * -1));
}
