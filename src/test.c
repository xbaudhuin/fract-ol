#include <mlx.h>
#include "fract-ol.h"
#include <math.h>
#include <stdlib.h>
#include "X11/keysym.h"
#include "X11/keysymdef.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	printf("img.line_length=%d\n", img->line_length);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	is_circle(int x, int y)
{
	if (sqrt(((x - (1920/2))* (x - (1920/2))) + ((y - 1080/2) * (y - 1080/2))) <= 100)
		return (1);
	else
		return (0);
}

int	handle_no_event(void *data)
{
	return (0);
}
void	put_circle(t_win *win, int color)
{
	t_data img;

	img.img= mlx_new_image(win->mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int x = 0; int y = 0;
	while (x <= 1920)
	{
		y = 0;
		while (y <= 1080)
		{
			if (is_circle(x, y))
				my_mlx_pixel_put(&img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, img.img, 0, 0);
	mlx_destroy_image(win->mlx_ptr, img.img);
}

int	handle_input(int keysystm, t_win *win, t_data *img)
{
	if (keysystm == XK_Escape)
	{
		if (img->img)
		{
			printf("j'ai bien detruit img->img\n\n");
			mlx_destroy_image(win->mlx_ptr, img->img);
			img->img = NULL;
		}
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
		exit(1);
	}
	if (keysystm == XK_r)
	{
		put_circle(win, 0xFF0000);
	}
	if (keysystm == XK_b)
		put_circle(win, 0x0000FF);
	printf("%d\n", keysystm);
	return (0);
}


int main()
{
	t_win	win;
	t_data	img;

	win.mlx_ptr = mlx_init();
	if (!win.mlx_ptr)
		return (2);
	win.win_ptr = mlx_new_window(win.mlx_ptr, 1920, 1080, "Window");
	if (!win.win_ptr)
	{
		mlx_destroy_display(win.mlx_ptr);
		return (free(win.mlx_ptr), 2);
	}
	//mlx_loop_hook(win.mlx_ptr, &handle_no_event, &win);
	img.img = mlx_new_image(win.mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	printf("img.bits_per_pixel= %d\n", img.bits_per_pixel);
	printf("img.line_length = %d\n", img.line_length);
	mlx_key_hook(win.win_ptr, &handle_input, &win);
	if (img.img)
	{
		mlx_destroy_image(win.mlx_ptr, img.img);
		img.img = NULL;
	}
	mlx_loop(win.mlx_ptr);
	return (0);
}
