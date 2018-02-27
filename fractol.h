/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oahieiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:59:34 by oahieiev          #+#    #+#             */
/*   Updated: 2018/02/27 19:59:41 by oahieiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#  define KP_4					65430
#  define KP_2					65433
#  define KB_F					102
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
#  define KB_R					15
#  define KP_4					86
#  define KP_2					84
#  define KB_F					3
# endif

# define MWU 4
# define MWD 5

# include "minilibx/mlx.h"
# include <pthread.h>
# include "./libft/libft.h"
# include "complex.h"

# define PI 3.141592654
# define WHITE 0xffffff
# define BLACK 0x000000
# define COLOR1					0x740D00
# define COLOR2					0xFFD200
# define COLOR3					0x000618
# define COLOR4					0xFFF36C

# define COLOR5					0xC21500
# define COLOR6					0xFFD200
# define COLOR7					0x3E2F5B
# define COLOR8					0x136F63

# define MLX_ERR "ERROR: mlx init failed"
# define USG_ERR1 "Usage: ./fractol [option]\n"
# define USG_ERR2 "Available options:\n\tmandelbrot\n\tmandelbar\n\tjulia"
# define USG_ERR3 "\n\tjuliabar\n\tbship\n\tnewton\n\tstrnewton"
# define USG_ERR USG_ERR1 USG_ERR2 USG_ERR3
# define PCREA_ERR "ERROR: pthread_create() returned "
# define PJOIN_ERR "ERROR: pthread_join() returned "
# define WIDTH					1280
# define HEIGHT					720
# define ITERATIONS				50
# define THREADS				12
# define TOLER					1e-6

typedef struct	s_fractol
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pxl;
	int			bpp;
	int			s_line;
	int			ed;
	double		zoom;
	double		step;
	double		reoff;
	double		imoff;
	void		(*fun)();
	int			(*color)(int, float);
	int			colormode;
	int			iter;
	int			parth;
	t_complex	c;
	int			hstep;
	t_complex	mpos;
	double		centerx;
	double		centery;
	char		julia;
	char		julia_fixed;
}				t_fractol;

void			*drawthr(void *frac_p);
void			get_threads(t_fractol *fr);
void			*exiterror(char *reason, t_fractol *fr);
void			reset_fractol(t_fractol *fr);
int				key_handler(int keycode, t_fractol *fr);
int				mouse_handler(int key, int mx, int my, t_fractol *fr);
int				mouse_handler2(int mx, int my, t_fractol *fr);

void			change_color(t_fractol *fr, int key);
int				interp_color(int colormode, float perc);
int				psy_color(int colormode, float perc);

void			mandelbrot(t_fractol *fr, int x, int y);
void			newton(t_fractol *fr, int x, int y);
void			strnewton(t_fractol *fr, int x, int y);
void			burning(t_fractol *fr, int x, int y);
void			mandelbar(t_fractol *fr, int x, int y);
void			something(t_fractol *fr, int x, int y);

void			put_pxl(t_fractol *fr, int x, int y, unsigned int c);

#endif
