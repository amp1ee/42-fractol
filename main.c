#include <stdio.h>
#include <mlx.h>
#define WIDTH 1280
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
#define RED 16711680
#define BLUE 255

int	main(void)
{
	void	*mlx_id;
	void	*mlx_window;
	int		rgb;
	int		x;
	int		y;

	mlx_id = mlx_init();
	
	mlx_window = mlx_new_window(mlx_id, WIDTH, HEIGHT, "Fils de fer");
//	mlx_string_put(mlx_id, mlx_window, (WIDTH / 4), (3 * HEIGHT) / 4, RED, "Fils de fer");
	y = 0;
	while (y++ < HEIGHT)
	{
		x = 0;
		while (x++ < WIDTH)
		{
			rgb = 65536 * (x % 255) + 256 * (y % 255) + (y - x) % 255; 
			printf("%d\n", rgb);
			mlx_pixel_put(mlx_id, mlx_window, x, y, rgb);
		}
	}

	return (0);
}
