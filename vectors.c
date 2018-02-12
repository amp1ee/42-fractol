#include "fractol.h"

double		to_rad(double deg)
{
	return (deg * PI / 180);
}

t_vector	*new_vector(double x, double y)
{
	t_vector	*n;

	if ((n = (t_vector *)malloc(sizeof(t_vector))) == NULL)
		return (NULL);
	n->x = x;
	n->y = y;
	return (n);
}

double		vlength(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double		vdot(t_vector v0, t_vector v1)
{
	return (v0.x * v1.x + v0.y * v1.y);
}

t_vector	*vadd_v(t_vector v0, t_vector v1)
{
	return (new_vector(v0.x + v1.x, v0.y + v1.y));
}

t_vector	*vadd_d(t_vector v, double d)
{
	return (new_vector(v.x + d, v.y + d));
}

t_vector	*vsub_v(t_vector v0, t_vector v1)
{
	return (new_vector(v0.x - v1.x, v0.y - v1.y));
}

t_vector	*vsub_d(t_vector v, double d)
{
	return (new_vector(v.x - d, v.y - d));
}

t_vector	*vmul_v(t_vector v0, t_vector v1)
{
	return (new_vector(v0.x * v1.x, v0.y * v1.y));
}

t_vector	*vmul_d(t_vector v, double d)
{
	return (new_vector(v.x * d, v.y * d));
}

t_vector	*vdiv_v(t_vector v0, t_vector v1)
{
	if (v1.x != 0.0 && v1.y != 0.0)
		return (new_vector(v0.x / v1.x, v0.y / v1.y));
	ft_putendl("Floating point exception: dividing by\
	 vector with zero coordinate");
	return (NULL);
}

t_vector	*vdiv_d(t_vector v, double d)
{
	if (d != 0.0)
		return (new_vector(v.x / d, v.y / d));
	ft_putendl("Floating point exception: dividing vector by 0");
	return (NULL);
}

t_vector	*vnormal(t_vector *v)
{
	double	vlen;

	vlen = vlength(*v);
	v->x /= vlen;
	v->y /= vlen;
	return  (v);
}

t_vector	*vrotat(double angle, t_vector v)
{
	double	rad;
	double	cosa;
	double	sina;

	rad = to_rad(angle);
	cosa = cos(rad);
	sina = sin(rad);
	return (new_vector((v.x * cosa - v.y * sina), (v.x * sina + v.y * cosa)));
}