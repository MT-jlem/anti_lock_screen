
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
//----------------------
#define WIN_WIDTH 5220
#define WIN_HEIGHT 2980
#define MAX_ITERATION 500
//----------------------
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct c_info
    {
    	void *mlx;
    	void *win;
		int x;
		int y;
		double a;
		double b;
		double	z_r;
	    double	z_i;
		double	real_start;
		double	real_end;
		double	re_origin;
		double	im_origin;
		double	zoom;
		double	imaginary_start;
		double	imaginary_end;
		double	c_r;
		double	c_i;
		
		int		iteration;
		int color;
		t_image	img;
        
    } t_init;
//----------------------
double	ft_map(double in, double in_end, double out_start, double out_end)
{
	return ((in) * (out_end - out_start) / (in_end) + out_start);
}

int close_win(void *param)
{
    t_init *data;
    data = param;
    mlx_destroy_image(data->mlx, data->win);
    exit(0);
}

int lock(int key, void *walo)
{
	system("pmset displaysleepnow");
	exit (-42);
	return (0);
}

int	key_hook(int keycode, t_init *vars)
{
	return (lock(1, NULL));
	return (0);
}


int	mouse_hook(int x, int y, void *param)
{
	return (lock(1, NULL));
}

int main()
{
	
    t_init data;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Mandelbrot");
    data.x = 0;
    while (data.x < WIN_WIDTH)
    {
        data.y = 0;
        while (data.y < WIN_HEIGHT)
        {
			data.a = ft_map(data.x, WIN_WIDTH, -2, 2);
            data.b = ft_map(data.y, WIN_HEIGHT, -2, 2);
            data.c_r = data.a;
            data.c_i = data.b;
            data.iteration = 0;
            while (data.iteration < MAX_ITERATION)
            {
                data.z_r = data.a * data.a - data.b * data.b;
                data.z_i = data.a * data.b * 2;
                data.a = data.z_r + data.c_r;
                data.b = data.z_i + data.c_i;
                data.iteration++;
                if (data.a * data .a + data.b *data.b > 4)
                    break ;
            }
            data.color = 0;
            if (data.iteration < MAX_ITERATION)
                data.color = data.iteration * 0xF0F8FF;
            mlx_pixel_put(data.mlx, data.win, data.x, data.y, data.color);
			data.y++;
		}
        data.x++;
		
    }
   	mlx_key_hook(data.win, key_hook, &data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 6, 0, mouse_hook, NULL);
    mlx_loop(data.mlx);
}
