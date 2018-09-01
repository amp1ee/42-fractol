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

# include <pthread.h>
# include <stdbool.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "complex.h"

/*
**	Keycodes
*/
# ifdef __linux__
#  define KB_ESC		65307
#  define KB_X			120
#  define KB_Z			122
#  define KB_UP			65362
#  define KB_DOWN		65364
#  define KB_LEFT		65361
#  define KB_RIGHT		65363
#  define KP_ADD		65451
#  define KP_SUBTRACT	65453
#  define KB_I			105
#  define KB_U			117
#  define KB_R			114
#  define KP_4			65430
#  define KP_2			65433
#  define KB_F			102
# elif __APPLE__
#  define KB_ESC		53
#  define KB_X			7
#  define KB_Z			6
#  define KB_UP			126
#  define KB_DOWN		125
#  define KB_LEFT		123
#  define KB_RIGHT		124
#  define KP_ADD		69
#  define KP_SUBTRACT	78
#  define KB_I			34
#  define KB_U			32
#  define KB_R			15
#  define KP_4			86
#  define KP_2			84
#  define KB_F			3
# endif
# define MWHEELUP		4
# define MWHEELDN		5

# define WIDTH		900
# define HEIGHT		600

# define PI			3.141592
# define WHITE		0xFFFFFF
# define BLACK		0x000000
# define COLOR3		0x000618
# define COLOR4		0xFFF36C
# define COLOR1		0x680b00
# define COLOR2		0xFFD200
# define COLOR5		0x285540
# define COLOR6		0xFFF36C
# define COLOR7		0x3E2F5B
# define COLOR8		0x136F63
# define COLOR9		0x200750
# define COLOR10	0xCC8E52
# define COLOR11	0xBBD3FF

/*
**	Console text controls
*/
# define YEL		"\e[32m"
# define MAG		"\e[33m"
# define BOLD		"\e[1m\e[4m"
# define CLR		"\e[0m"
# define TABS		"\t\t  "

/*
**	Program arguments
*/
# define MBROT		"mbrot"
# define MBAR		"mbar"
# define JULIA		"julia"
# define JBAR		"jbar"
# define BSHIP		"bship"
# define PSHIP		"pship"
# define CELTIC		"celt"
# define NEWTON		"newton"
# define ANEWTON	"anewton"

/*
**	Messages
*/
# define MLX_ERR	"ERROR: mlx init failed"
# define USG_ERR	YEL "\n\tUsage:" MAG " ./fractol" YEL " [option]\n\n"	\
					MAG "\tAvailable options:\n" YEL						\
					TABS MBROT" - Mandelbrot\n"								\
					TABS MBAR " - Mandelbar\n"								\
					TABS JULIA " - Julia set\n"								\
					TABS JBAR " - Juliabar\n"								\
					TABS BSHIP " - Burning ship\n"							\
					TABS PSHIP " - Perpendicular burning ship\n"			\
					TABS CELTIC " - Celtic mandelbar\n"						\
					TABS NEWTON " - Newton's fractal\n"						\
					TABS ANEWTON " - Alternative Newton's fractal\n" CLR
# define PTHR_ERR	"ERROR: Some problem with pthread occured"
# define CONTROLS	"\n\t\t" YEL BOLD "Controls\n\n" CLR					\
					YEL "\tFix Julia set" MAG "\tF\n"						\
					YEL "\tReset view" MAG "\tR\n"							\
					YEL "\tMove" MAG "\t\tUp/Down/Left/Right\n"				\
					YEL "\tZoom" MAG "\t\tZ/X, Mouse wheel\n"				\
					YEL "\tColors" MAG "\t\tNumPad 2\n"						\
					YEL "\tPsymode" MAG "\t\tNumPad 4\n"					\
					YEL "\tModify iters" MAG "\tI/U\n" CLR

# define ITERS_MIN		50
# define ITERS_MAX		10000
# define THREADS_NUM	8
# define TOLER			1e-6

# define BAILOUT(a)			(((a).re * (a).re + (a).im * (a).im) >= 4)
# define IS_ROOT(z, roots)	(fabs((z).re - (roots)[j].re) < (TOLER) && \
							fabs((z).im - (roots)[j].im) < (TOLER))

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
	void		(*iter_fun)();
	int			(*color)(int, float);
	int			colormode;
	int			iter;
	int			parth;
	t_complex	c;
	int			hstep;
	t_complex	mpos;
	double		centerx;
	double		centery;
	bool		julia;
	bool		julia_fixed;
	bool		alt_newton;
}				t_fractol;

void			get_threads(t_fractol *fr);
void			*exiterror(char *reason, t_fractol *fr);
void			reset_fractol(t_fractol *fr);
int				key_handler(int keycode, t_fractol *fr);
int				mouse_handler(int key, int mx, int my, t_fractol *fr);
int				mouse_handler2(int mx, int my, t_fractol *fr);

void			change_color(t_fractol *fr, int key);
int				interp_color(int colormode, float perc);
int				psy_color(int colormode, float perc);
float			log_perc(int iter, int i, t_complex a);

void			mandelbrot(t_fractol *fr, t_complex *a, t_complex a2, int *i);
void			burning(t_fractol *fr, t_complex *a, t_complex a2, int *i);
void			mandelbar(t_fractol *fr, t_complex *a, t_complex a2, int *i);
void			perpend_bship(t_fractol *fr, t_complex *a,
													t_complex a2, int *i);
void			celtic(t_fractol *fr, t_complex *a, t_complex a2, int *i);
void			newton(t_fractol *fr, t_complex *a, t_complex a2, int *i);

void			iter_mandelbrots(t_fractol *fr, int x, int y);
void			iter_newtons(t_fractol *fr, int x, int y);

#endif
