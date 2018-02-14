#ifndef FRACTOL_H
# define FRACTOL_H

# ifdef __linux__
#  define KB_ESC				0xff1b
#  define KB_X					120
#  define KB_Z					122
#  define KB_UP					65362
#  define KB_DOWN				65364
#  define KB_LEFT				65361
#  define KB_RIGHT				65363
#  define KP_ADD				0xffab
#  define KP_SUBTRACT			0xffad
#  define KB_I					0x0069
#  define KB_U					0x0075
#  define KB_R					114
#  define KP_4					83
#  define KP_6					85
# elif __APPLE__
#  define KB_ESC				53
#  define KB_X					7
#  define KB_Z					6
#  define KB_UP					126
#  define KB_DOWN				125
#  define KB_LEFT				123
#  define KB_RIGHT				124
#  define KP_ADD				69
#  define KP_SUBTRACT			78
#  define KB_I					34
#  define KB_U					32
#  define KB_R					15 // Check this
#  define KP_4					86
#  define KP_6					88
#  define KP_8					91
#  define KP_2					84
#  define KB_W					13
#  define KB_S					1
#  define KB_H					4
# endif

/*								DELETE!										*/
# include <stdio.h>
/*								DELETE!										*/

# include "minilibx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>
# include "../libft/libft.h"

# define PI 3.141592654
# define WHITE 0xffffff
# define BLACK 0x000000

# define MLX_ERR "ERROR: mlx init failed"
# define PCREA_ERR "ERROR: pthread_create() returned "
# define PJOIN_ERR "ERROR: pthread_join() returned "

#define WIDTH					1200
#define HEIGHT					800
#define	ITERATIONS				50
#define THREADS					24

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pxl;
	int			bpp;
	int			s_line;
	int			ed;
	double		n;
	float		step;
	double		ash;
	double		bsh;
	double		ref;
	double		imf;
	int			iter;
	int			i;
	int			parth;
	}			t_mlx;

void			*drawthr(void *mlx_p);
void			get_threads(t_mlx *fr);
void			*exiterror(char *reason, t_mlx *fr);
int				key_handler(int keycode, void *param);
int				mouse_handler(int key, int mx, int my, void *p);

#endif
