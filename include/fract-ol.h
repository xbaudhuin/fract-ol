/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:39:29 by xabaudhu          #+#    #+#             */
/*   Updated: 2023/12/21 14:57:22 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include  <mlx.h>
# include <math.h>
# include <stdlib.h>
# include "X11/keysym.h"
# include "X11/keysymdef.h"
# include <unistd.h>
# include <X11/X.h>

# define WIDTH 1920.0
# define HEIGHT 1080.0

typedef struct	s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_win;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_complex
{
	double	real;
	double	i;
}				t_complex;

typedef	struct	s_screen
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
	int (*function)(struct s_fractal *fractal);
	int (*color)(int n, t_complex za, struct s_fractal *fractal);
}				t_fractal;


typedef struct	s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

#endif
