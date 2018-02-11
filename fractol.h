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

typedef struct	s_mlx
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*pxl;
	int		bpp;
	int		s_line;
	int		ed;
	int		n;
	float	step;
	float	ash;
	float	bsh;
	int		iter;

	int		mx;
	int		my;
	int		parth;
}				t_mlx;

#endif
