#include "fractol.h"

t_matrix	*init_trnsl(double x, double y, t_matrix *mtrx)
{
	mtrx->x[2] = x;
	mtrx->y[2] = y;
	return (mtrx);
}

t_matrix	*init_identity(t_matrix *mtrx)
{
	mtrx->x[0] = 1;
	mtrx->x[1] = 0;
	mtrx->x[2] = 0;

	mtrx->y[0] = 0;
	mtrx->y[1] = 1;
	mtrx->y[2] = 0;

	mtrx->w[0] = 0;
	mtrx->w[1] = 0;
	mtrx->w[2] = 1;

	return (mtrx);
}

t_matrix	*mul(t_matrix m0, t_matrix m1)
{
	t_matrix	*res;
	double		mt[3];
	double		*res_[3];
	int			i;
	int			j;

	if ((res = new_matrix()) == NULL)
		return (NULL);
	mt[0] = *m0.x;
	mt[1] = *m0.y;
	mt[2] = *m0.w;
	res_[0] = res->x;
	res_[1] = res->y;
	res_[2] = res->w;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			(res_[i])[j] = mt[i] * m1.x[j] +
					mt[i] * m1.y[j] +
					mt[i] * m1.w[j];
			j++;
		}
		i++;
	}
	return (res);
}

t_matrix	*new_matrix(void)
{
	t_matrix	*m;

	if ((m = (t_matrix *)malloc(sizeof(t_matrix))) == NULL)
		return (NULL);
	return (init_identity(m));
}