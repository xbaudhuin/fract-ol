/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 23:02:00 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/12/22 18:27:01 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "X.h"
#include "fract-ol.h"
#include "libft.h"
#include "ft_printf.h"
#include <inttypes.h>
#include <mlx.h>

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_length + x * (img->bits_per_pixel / 8.0));
	*(unsigned int *)(img->addr + offset) = color;
}

t_complex	mandelbrot(t_complex c, t_fractal *fractal, int *check)
{
	t_complex	z;
	t_complex	tmp;		
	int	n;

	n = 0;
	z.real = 0;
	z.i = 0;
	tmp.real = 0;
	tmp.i = 0;
	while (n < fractal->max_iter)
	{
		z.i = 2 * z.i * z.real + c.i;
		z.real = tmp.real - tmp.i + c.real;
		tmp.real = z.real * z.real;
		tmp.i = z.i * z.i;
		if (tmp.i + tmp.real > 4)
		{
			*check = n + 1;
			break;
		}
		n++;
	}
	return (z);
}

double	interpolate(double start, double end, t_fractal *fractal)
{
	return (start + ((end - start) / fractal->zoom));
}

void	get_new_screen(t_fractal *fractal)
{
	double	interpolation = fractal->zoom;
	fractal->screen->real_min = interpolate(fractal->mouse.real, fractal->screen->real_min, fractal); //+ fractal->shift_x;
	fractal->screen->real_max = interpolate(fractal->mouse.real, fractal->screen->real_max, fractal); //+ fractal->shift_x;
	fractal->screen->i_min = interpolate(fractal->mouse.i, fractal->screen->i_min, fractal);// + fractal->shift_y;
	fractal->screen->i_max = interpolate(fractal->mouse.i, fractal->screen->i_max, fractal); //+ fractal->shift_y;
}

double	get_new_pos_real(double x, t_fractal *fractal)
{
	double	ret;

	ret = fractal->screen->real_min + x * (fractal->screen->real_max - fractal->screen->real_min) / (1920.0 - 1.0);
	return (ret);
}

double	get_new_pos_i(double y, t_fractal *fractal)
{
		double	ret;

	ret = fractal->screen->i_max - y * (fractal->screen->i_max - fractal->screen->i_min) / (1080.0 - 1.0);
	return (ret);
}

int	shift_color(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}


/*int	color_nice(int n, t_complex za, t_fractal *fractal)
{
	double	grad;
	t_color	rgb;
	int	color;

	(void)za;
	grad = (double)n / (double)fractal->max_iter;
	rgb.red = (int)(255 * grad);
	rgb.green = 0;
	rgb.blue = (int)(1 * (1 - grad) * grad * 255);
	color = shift_color( rgb.red, rgb.green, rgb.blue);
	return (color);
}*/
int	color_nice(int n, t_complex za, t_fractal *fractal)
{
	double grad;
	t_color rgb;

	grad = (double) n / (double)fractal->max_iter;
    rgb.red = (int)(255 * grad);
    rgb.blue = (int)(255* grad);
    rgb.green = (int)(255 * grad);
	return (shift_color(rgb.red, rgb.green, rgb.blue));
}

int	color_rainbow(int n, t_complex za, t_fractal *fractal)
{
	int		palette[8];
	int		color;

	(void)za;
	palette[0] = 0xFFFFFF;
	palette[1] = 0x9400D3;
	palette[2] = 0x4B0082;
	palette[3] = 0x0000FF;
	palette[4] = 0x00FF00;
	palette[5] = 0xFFFF00;
	palette[6] = 0xFF7F00;
	palette[7] = 0xFF0000;
	return (palette[n % 8]);
}

int color_red(int n, t_complex za, t_fractal *fractal)
{
    double grad;
	t_color rgb;

	grad = (double) n / (double)fractal->max_iter;
    rgb.red = (int)(255 * grad);
    rgb.blue = (int)(0);
    rgb.green = (int)(0);
	return (shift_color(rgb.red, rgb.green, rgb.blue));
}

int color_blue(int n, t_complex za, t_fractal *fractal)
{
    double grad;
	t_color rgb;

	grad = (double) n / (double)fractal->max_iter;
    rgb.red = (int)(0);
    rgb.blue = (int)(255 * grad);
    rgb.green = (int)(0);
	return (shift_color(rgb.red, rgb.green, rgb.blue));
}

int color_green(int n, t_complex za, t_fractal *fractal)
{
    double grad;
	t_color rgb;

	grad = (double) n / (double)fractal->max_iter;
    rgb.red = (int)(0);
    rgb.blue = (int)(0);
    rgb.green = (int)(255 * grad);
	return (shift_color(rgb.red, rgb.green, rgb.blue));
}


int	get_mandelbrot(t_fractal *fractal)
{
	int	x;
	int	y;
	t_complex z;
	int check;
	t_complex	za;
	
	x = 0;
	y = 0;
	while (y < 1080)
	{
		z.i = get_new_pos_i(y, fractal) + fractal->shift_y;
		x = 0;
		while (x < 1920)
		{
			check = 0;
			z.real = get_new_pos_real(x, fractal) + fractal->shift_x;
			za = mandelbrot(z, fractal, &check);
			if (!check)
				my_mlx_pixel_put(fractal->img, x, y, 0x000000);
			else
				my_mlx_pixel_put(fractal->img, x, y, fractal->color(check, za, fractal));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->win->mlx_ptr, fractal->win->win_ptr, fractal->img->img, 0, 0);
	return (0);
}

t_complex	julia(t_complex z, t_fractal *fractal, int *check)
{
	t_complex	tmp;
	int	n;

	n = 0;
	while (n < fractal->max_iter)
	{
		tmp.real = z.real * z.real;
		tmp.i = z.i * z.i;
		z.i = 2 * z.i * z.real + fractal->c.i;
		z.real = tmp.real - tmp.i + fractal->c.real;
		if (tmp.i + tmp.real > 4.0)
		{
			*check = n + 1;
			break;
		}
		n++;
	}
	return (z);
}

int	get_julia(t_fractal *fractal)
{
	int	x;
	int	y;
	t_complex z;
	int check;
	t_complex	za;
	
	x = 0;
	y = 0;
	while (y < 1080)
	{
		z.i = get_new_pos_i(y, fractal) + fractal->shift_y;
		x = 0;
		while (x < 1920)
		{
			check = 0;
			z.real = get_new_pos_real(x, fractal) + fractal->shift_x;
			za = julia(z, fractal, &check);
			if (!check)
				my_mlx_pixel_put(fractal->img, x, y, 0x000000);
			else
				my_mlx_pixel_put(fractal->img, x, y, fractal->color(check - 1, za, fractal));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->win->mlx_ptr, fractal->win->win_ptr, fractal->img->img, 0, 0);
	return (0);
}

t_complex	tricorn(t_complex c, t_fractal *fractal, int * check)
{
	t_complex	z;
	t_complex	tmp;
	int	n;

	n = 0;
	z.real = 0;
	z.i = 0;
	tmp.real = 0;
	tmp.i = 0;
	while (n < fractal->max_iter)
	{
		z.i = -2 * z.i * z.real + c.i;
		z.real = tmp.real - tmp.i + c.real;
		tmp.real = z.real * z.real;
		tmp.i = z.i * z.i;
		if (tmp.i + tmp.real > 4)
		{
			*check = n + 1;
			break;
		}
		n++;
	}
	return (z);
}

int	get_tricorn(t_fractal *fractal)
{
	int	x;
	int	y;
	t_complex z;
	int check;
	t_complex	za;
	
	x = 0;
	y = 0;
	while (y < 1080)
	{
		z.i = get_new_pos_i(y, fractal) + fractal->shift_y;
		x = 0;
		while (x < 1920)
		{
			check = 0;
			z.real = get_new_pos_real(x, fractal) + fractal->shift_x;
			za = tricorn(z, fractal, &check);
			if (!check)
				my_mlx_pixel_put(fractal->img, x, y, 0x000000);
			else
				my_mlx_pixel_put(fractal->img, x, y, fractal->color(check, za, fractal));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->win->mlx_ptr, fractal->win->win_ptr, fractal->img->img, 0, 0);
	return (0);


}

void	free_fractal(t_fractal *fractal)
{
	free(fractal->win->mlx_ptr);
	free(fractal->win);
	free(fractal->img);
	free(fractal->screen);
}

int	init_fractal(t_fractal *fractal)
{

	fractal->screen = malloc(sizeof(*(fractal->screen)));
	if (!fractal->screen)
		return (0);
	fractal->screen->real_max = 1.05;
	fractal->screen->real_min = -2.5;
	fractal->screen->i_min = -1;
	fractal->screen->i_max = fractal->screen->i_min + ((fractal->screen->real_max - fractal->screen->real_min) * 1080.0 / 1920.0);
	fractal->win = malloc(sizeof(t_win));
	if (!fractal->win)
		return (free_fractal(fractal), 2);
	fractal->img = malloc(sizeof(t_data));
	if (!fractal->img)
		return (free_fractal(fractal), 3);
	fractal->win->mlx_ptr = mlx_init();
	if (!fractal->win->mlx_ptr)
		return (1);
	fractal->win->win_ptr = mlx_new_window(fractal->win->mlx_ptr, 1920, 1080, "julia");
	if (!fractal->win->win_ptr)
	{
		mlx_destroy_display(fractal->win->mlx_ptr);
		free_fractal(fractal);
		return (2);
	}
	fractal->img->img = mlx_new_image(fractal->win->mlx_ptr, 1920, 1080);
	if (!fractal->img->img)
	{
		mlx_destroy_window(fractal->win->mlx_ptr, fractal->win->win_ptr);
		mlx_destroy_display(fractal->win->mlx_ptr);
		free_fractal(fractal);
		return (3);
	}
	fractal->img->addr = mlx_get_data_addr(fractal->img->img, &(fractal->img->bits_per_pixel), &(fractal->img->line_length), &(fractal->img->endian));
	return (0);
}

int	close_window(t_fractal *fractal)
{
	if (fractal->img->img)
	{
		mlx_destroy_image(fractal->win->mlx_ptr, fractal->img->img);
		fractal->img->img = NULL;
	}
	mlx_destroy_window(fractal->win->mlx_ptr, fractal->win->win_ptr);
	mlx_destroy_display(fractal->win->mlx_ptr);
	free_fractal(fractal);
	exit(1);
}
void	reset_fractal(t_fractal *fractal)
{
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->mouse.real = 0.0;
	fractal->mouse.i = 0.0;
	fractal->screen->real_max = 1.05;
	fractal->screen->real_min = -2.5;
	fractal->screen->i_min = -1;
	fractal->screen->i_max = fractal->screen->i_min + ((fractal->screen->real_max - fractal->screen->real_min) * 1080.0 / 1920.0);
}
int	handle_input(int keysystm, t_fractal *fractal)
{
	if (keysystm == XK_Escape)
		close_window(fractal);
	if (keysystm == 61 || keysystm == 65451)
	{
		if (fractal->zoom < 1)
			fractal->zoom = 1.0;
		fractal->zoom *= 1.1;
		get_new_screen(fractal);
		fractal->function(fractal);
	}
	if (keysystm == XK_minus || keysystm == 65453)
	{
		if (fractal->zoom > 1)
			fractal->zoom = 1.0;
		fractal->zoom /= 1.1;
		get_new_screen(fractal);
		fractal->function(fractal);
	}
	if (keysystm == 65361)
	{
		fractal->shift_x -= 200 * (fractal->screen->real_max - fractal->screen->real_min) / 1920.0;
		fractal->function(fractal);
	}
	if (keysystm == 65362)
	{
		fractal->shift_y += 100 * (fractal->screen->i_max - fractal->screen->i_min) / 1080.0;
		fractal->function(fractal);
	}
	if (keysystm == 65363)
	{
		fractal->shift_x += 200 *  (fractal->screen->real_max - fractal->screen->real_min) / 1920.0;
		fractal->function(fractal);
	}
	if (keysystm == 65364)
	{
		fractal->shift_y -= 100 *  (fractal->screen->i_max - fractal->screen->i_min) / 1080.0;
		fractal->function(fractal);
	}
	if (keysystm == 65288)
	{
		reset_fractal(fractal);
		fractal->function(fractal);
	}
	if (keysystm == 109)
	{
		fractal->function = get_mandelbrot;
		reset_fractal(fractal);
		get_new_screen(fractal);
		fractal->function(fractal);
	}
	if (keysystm == 116)
	{
		fractal->function = get_tricorn;
		reset_fractal(fractal);
		get_new_screen(fractal);
		fractal->function(fractal);
	}
	if (keysystm == 106)
	{
		fractal->function = get_julia;
		reset_fractal(fractal);
		get_new_screen(fractal);
		fractal->function(fractal);
	}
	if (keysystm == 49)
	{
		fractal->color = color_nice;
		fractal->function(fractal);
	}
	if (keysystm == 50)
	{
		fractal->color = color_rainbow;
		fractal->function(fractal);
	}
	if (keysystm == 51)
	{
		fractal->color = color_red;
		fractal->function(fractal);
	}
	if (keysystm == 52)
	{
		fractal->color = color_green;
		fractal->function(fractal);
	}
	if (keysystm == 53)
	{
		fractal->color = color_blue;
		fractal->function(fractal);
	}
	if (keysystm == 105)
	{
		fractal->max_iter += 1;
		if (fractal->max_iter > 1000)
			fractal->max_iter = 1000;
		fractal->function(fractal);
	}
	if (keysystm == 111)
	{
		fractal->max_iter -= 1;
		if (fractal->max_iter < 1)
			fractal->max_iter = 1;
		fractal->function(fractal);
	}
	printf("keysystm= %d\n", keysystm);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button4)
	{
		if (fractal->zoom < 1)
			fractal->zoom = 1;
		fractal->zoom *= 1.1;
		fractal->mouse.real = get_new_pos_real(x, fractal);
		fractal->mouse.i = get_new_pos_i(y, fractal);
		get_new_screen(fractal);
		fractal->function(fractal);
	}
	if (button == Button5)
	{
		if (fractal->zoom > 1)
			fractal->zoom = 1;
		fractal->zoom /= 1.1;
		fractal->mouse.real = get_new_pos_real(x, fractal);
		fractal->mouse.i = get_new_pos_i(y, fractal);
		get_new_screen(fractal);
		fractal->function(fractal);
	}
	return (0);
}

int	display_options(void)
{
	ft_printf("Please atleast add arguments like:\n<fractal_name> <real_part_number> <imaginary_part_number>\nAvailable fractals: <Mandelbrot> <Julia> <Tricorn>\n");
	ft_printf("For all fractals, you can add 2 more arguments, the first has to have only digits and corresponds to the precision of the fractal(max is 1000)\n");
	ft_printf("The second is the size of the radius to consider for the escape, wich is a double\n");
	ft_printf("Exemple:\nJulia 0.285 0.01\n");
	return (1);
}

int	ft_atoi_parse(char *s, int *check)
{
	int	i;
	int	ret;
	int	sign;

	i = 0;
	ret = 0;
	sign = 1;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		ret = ret * 10 + s[i] - '0';
		i++;
	}
	if (s[i])
		*check = 1;
	return (ret * sign);
}

double	atodouble_parse(char *s, int *check)
{
	int		i;
	double	ret;
	double	divider;

	i = 0;
	ret = 0;
	divider = 10.0;
	ret = (double)ft_atoi_parse(s, check);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '.')
	{
		*check = 0;
		i++;
		while (ft_isdigit(s[i]))
		{
			ret += (double)(s[i] - '0') / divider;
			divider *= 10;
			i++;
		}
	}
	if (s[i])
		*check = 1;
	return (ret);
}

int	check_iter_radius(int ac, char **av, t_fractal *fractal)
{
	int	check;

	check = 0;
	if (ac >= 2)
	{
		fractal->max_iter = ft_atoi_parse(av[1], &check);
		if (fractal->max_iter > 1000)
			fractal->max_iter = 1000;
	}
	else
		fractal->max_iter = 100;
	if (ac == 3)
		fractal->radius = atodouble_parse(av[2], &check);
	else
		fractal->radius = 2;
	return (check);
}

int	check_mandelbrot(int ac, char **av, t_fractal *fractal)
{
	if (ac > 3)
		return (display_options(), 0);
	if (check_iter_radius(ac, av, fractal))
		return (display_options(), 0);
	return (2);
}

int	check_julia(int ac, char **av, t_fractal *fractal)
{
	int	i;
	int check;

	i = 0;
	check = 0;
	if (ac > 5 || ac < 3)
		return (display_options(), 0);
	fractal->c.real = atodouble_parse(av[1], &check);
	fractal->c.i = atodouble_parse(av[2], &check);
	if (check_iter_radius(ac - 2, &av[2], fractal))
		return (display_options(), 0);
	return (2);
}

int	parse_arg(int ac, char **av, t_fractal *fractal)
{
	if (ft_strncmp(av[0], "Mandelbrot", 11) == 0)
	{
		if (!check_mandelbrot(ac, av, fractal))
			return (0);
		fractal->function = get_mandelbrot;
		return (1);
	}
	if (ft_strncmp(av[0], "Julia", 6) == 0)
	{
		if (!check_julia(ac, av, fractal))
			return (0);
		fractal->function = get_julia;
		return (2);
	}
	if (ft_strncmp(av[0], "Tricorn", 8) == 0)
	{
		if (check_mandelbrot(ac, av, fractal))
			return (0);
		fractal->function = get_tricorn;
		return (3);
	}
	return (display_options(), 0);
}

int main(int ac, char **av)
{
	t_fractal fractal;

	if (ac < 2)
		return (display_options(), 1);
	if (init_fractal(&fractal))
		return (0);
	if (!parse_arg(ac - 1, &av[1], &fractal))
		return (close_window(&fractal));
	fractal.zoom = 1.0;
	fractal.mouse.i = 0.0;
	fractal.mouse.real = 0.0;
	fractal.shift_x = 0.0;
	fractal.shift_y = 0.0;
	fractal.color = color_nice;
	fractal.function(&fractal);
	mlx_mouse_hook(fractal.win->win_ptr, &handle_mouse, &fractal);
	mlx_key_hook(fractal.win->win_ptr, &handle_input, &fractal);
	mlx_hook(fractal.win->win_ptr, 17, 0L, close_window, &fractal);
	mlx_loop(fractal.win->mlx_ptr);
}
