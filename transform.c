#include "fractol.h"

t_transform	*init_transform(double x, double y, double w)
{
	t_transform		*tform;
	t_vector		*trnsl;
	t_vector		*rotat;
	t_vector		*scale;

	if ((trnsl = new_vector(0, 0)) == NULL ||
		(rotat = new_vector(0, 0)) == NULL ||
		(scale = new_vector(1, 1)) == NULL)
		return (NULL);
	if ((tform = (t_transform *)malloc(sizeof(t_transform))) == NULL)
		return (NULL);
	tform->trnsl = *trnsl;
	tform->rotat = *rotat;
	tform->scale = *scale;
	return (tform);
}
