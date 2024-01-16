/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:29:26 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 18:28:40 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	handle_input_49_to_53(int keystm, t_fractal *ft)
{
	if (keystm == 49)
		ft->color = color_nice;
	if (keystm == 50)
		ft->color = color_rainbow;
	if (keystm == 51)
		ft->color = color_red;
	if (keystm == 52)
		ft->color = color_green;
	if (keystm == 53)
		ft->color = color_blue;
	ft->function(ft);
	return (0);
}

static int	handle_input_zoom(int keystm, t_fractal *ft)
{
	if (keystm == 61 || keystm == 65451)
	{
		if (ft->zoom < 1)
			ft->zoom = 1.0;
		ft->zoom *= 1.1;
		get_new_screen(ft);
	}
	if (keystm == 45 || keystm == 65453)
	{
		if (ft->zoom > 1)
			ft->zoom = 1.0;
		ft->zoom /= 1.1;
		get_new_screen(ft);
	}
	ft->function(ft);
	return (0);
}

static int	handle_input_shift(int keystm, t_fractal *ft)
{
	double	factor;

	if (keystm == 65361 || keystm == 65363)
	{
		factor = (ft->screen->real_max - ft->screen->real_min) / 1920.0;
		if (keystm == 65361)
			ft->shift_x -= 200 * factor;
		else
			ft->shift_x += 200 * factor;
	}
	if (keystm == 65362 || keystm == 65364)
	{
		factor = (ft->screen->i_max - ft->screen->i_min) / 1080.0;
		if (keystm == 65362)
			ft->shift_y += 100 * factor;
		else
			ft->shift_y -= 100 * factor;
	}
	ft->function(ft);
	return (0);
}

static int	handle_input_fractal(int keystm, t_fractal *ft)
{
	if (keystm == 109)
	{
		ft->function = get_mandelbrot;
		reset_fractal(ft);
		get_new_screen(ft);
	}
	if (keystm == 116)
	{
		ft->function = get_tricorn;
		reset_fractal(ft);
		get_new_screen(ft);
	}
	if (keystm == 106)
	{
		ft->function = get_julia;
		reset_fractal(ft);
		get_new_screen(ft);
	}
	ft->function(ft);
	return (0);
}

int	handle_input(int keystm, t_fractal *ft)
{
	if (keystm == XK_Escape)
		close_window(ft);
	if (keystm >= 49 && keystm <= 53)
		handle_input_49_to_53(keystm, ft);
	if (keystm == 45 || keystm == 61 || keystm == 65451 || keystm == 65453)
		handle_input_zoom(keystm, ft);
	if (keystm >= 65361 && keystm <= 65364)
		handle_input_shift(keystm, ft);
	if (keystm == 106 || keystm == 116 || keystm == 109)
		handle_input_fractal(keystm, ft);
	if (keystm == 105 || keystm == 111)
		handle_input_iter(keystm, ft);
	if (keystm == 65288)
	{
		reset_fractal(ft);
		ft->function(ft);
	}
	return (0);
}
