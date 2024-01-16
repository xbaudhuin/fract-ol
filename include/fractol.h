/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:33:56 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/16 17:08:15 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include "X11/keysym.h"
# include "X11/keysymdef.h"
# include <unistd.h>
# include <X11/X.h>

# define WIDTH 1920.0
# define HEIGHT 1080.0

typedef struct s_win
{
	void	*p_mlx;
	void	*p_win;
}				t_win;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bit;
	int		len;
	int		end;
}				t_data;

typedef struct s_complex
{
	double	real;
	double	i;
}				t_complex;

typedef struct s_screen
{
	double	real_min;
	double	real_max;
	double	i_min;
	double	i_max;
}				t_screen;

typedef struct s_fractal
{
	t_win		*win;
	t_data		*img;
	int			max_iter;
	t_complex	c;
	double		zoom;
	double		radius;
	t_complex	mouse;
	double		shift_x;
	double		shift_y;
	t_screen	*screen;
	int			(*function)(struct s_fractal *fractal);
	int			(*color)(int n, struct s_fractal *fractal);
}				t_fractal;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

int		color_rainbow(int n, t_fractal *fractal);
int		color_nice(int n, t_fractal *fractal);
int		shift_color(int red, int green, int blue);
int		color_red(int n, t_fractal *fractal);
int		color_blue(int n, t_fractal *fractal);
int		color_green(int n, t_fractal *fractal);

void	put_pixel(t_data *img, int x, int y, int color);
void	get_new_screen(t_fractal *f);
double	get_new_pos_real(double x, t_fractal *fractal);
double	get_new_pos_i(double y, t_fractal *fractal);

int		check_julia(int ac, char **av, t_fractal *fractal);
int		check_mandelbrot(int ac, char **av, t_fractal *fractal);
int		display_options(void);

int		get_mandelbrot(t_fractal *ft);
int		get_julia(t_fractal *ft);
int		get_tricorn(t_fractal *ft);

int		init_fractal(t_fractal *ft);

int		handle_input(int keysystm, t_fractal *fractal);
int		handle_input_iter(int keystm, t_fractal *ft);
int		handle_mouse(int button, int x, int y, t_fractal *fractal);

int		parse_arg(int ac, char **av, t_fractal *fractal);
double	atodouble_parse(char *s, int *check);
int		ft_atoi_parse(char *s, int *check, int *index);

void	free_fractal(t_fractal *fractal);
int		close_window(t_fractal *fractal);
void	reset_fractal(t_fractal *fractal);
#endif
