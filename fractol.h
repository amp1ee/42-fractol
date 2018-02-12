#ifndef FRACTOL_H
# define FRACTOL_H

# ifdef __linux__
#  define 	KB_ESC					0xff1b
#  define	KB_X					120
#  define	KB_Z					122
#  define 	KB_UP					65362
#  define	KB_DOWN					65364
#  define 	KB_LEFT					65361
#  define	KB_RIGHT				65363
#  define 	KP_ADD                  0xffab
#  define	KP_SUBTRACT				0xffad
#  define 	KB_I                    0x0069
#  define	KB_U					0x0075
# elif __APPLE__
#  define KB_ESC					53
#  define KB_X						7
#  define KB_Z						6
#  define KB_UP						126
#  define KB_DOWN					125
#  define KB_LEFT					123
#  define KB_RIGHT					124
#  define KP_ADD					69
#  define KP_SUBTRACT				78
#  define KB_I						34
#  define KB_U						32
#  define KP_4						86
#  define KP_6						88
#  define KP_8						91
#  define KP_2						84
#  define KB_W						13
#  define KB_S						1
#  define KB_H						4
# endif

# include "minilibx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>
# include "../libft/libft.h"

# define PI 3.141592654

typedef struct	s_mlx
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*pxl;
	int			bpp;
	int			s_line;
	int			ed;
	int			n;
	float		step;
	double		ash;
	double		bsh;
	int			iter;

	int			mx;
	int			my;
	int			parth;
}				t_mlx;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_matrix
{
	double		x[3];
	double		y[3];
	double		w[3];
}				t_matrix;

typedef struct	s_transform
{
	t_vector	trnsl;
	t_vector	rotat;
	t_vector	scale;
	t_matrix	t_mtrx;
}				t_transform;

t_transform		*init_transform(double x, double y, double w);
t_vector		*new_vector(double x, double y);
t_matrix		*new_matrix(void);

t_vector		*vrotat(double angle, t_vector v);
t_vector		*vnormal(t_vector *v);
double			vlength(t_vector v);
double			vdot(t_vector v0, t_vector v1);
t_vector		*vadd_v(t_vector v0, t_vector v1);
t_vector		*vadd_d(t_vector v, double d);
t_vector		*vsub_v(t_vector v0, t_vector v1);
t_vector		*vsub_d(t_vector v, double d);
t_vector		*vmul_v(t_vector v0, t_vector v1);
t_vector		*vmul_d(t_vector v, double d);
t_vector		*vdiv_v(t_vector v0, t_vector v1);
t_vector		*vdiv_d(t_vector v, double d);

#endif
