#include <stdio.h>
#include <mlx.h>
#define WIDTH 1080
#define HEIGHT 720

static inline unsigned long long s_to_binary_(const char *s)
{
	unsigned long long i = 0;
	while (*s)
	{
		i <<= 1;
		i += *s++ - '0';
	}
	return (i);
}
 
#define BIN(x) s_to_binary_(#x)
#define RED BIN(0000111100000000)

int	main(void)
{
	void	*mlx_id;
	void	*mlx_window;	
	int x;
	int y;

	mlx_id = mlx_init();
	
	mlx_window = mlx_new_window(mlx_id, WIDTH, HEIGHT, "Fir de fler");
	x = 0;
	mlx_string_put(mlx_id, mlx_window, (WIDTH / 4), (3 * HEIGHT) / 4, RED, "Fir de fler");
	while (x++ < WIDTH)
	{
		y = 0;
		while (y++ < HEIGHT)
			mlx_pixel_put(mlx_id, mlx_window, x, y, (y % 255));
	}
	return (0);
}
