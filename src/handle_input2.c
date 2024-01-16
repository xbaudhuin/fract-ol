/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:51:29 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 18:28:15 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "X.h"
#include "fractol.h"

static int	handle_mouse_zoom(int button, int x, int y, t_fractal *fractal)
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

int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button5 || button == Button4)
		handle_mouse_zoom(button, x, y, fractal);
	if (button == Button1)
	{
		fractal->function = get_julia;
		reset_fractal(fractal);
		fractal->c.real = get_new_pos_real(x, fractal);
		fractal->c.i = get_new_pos_i(y, fractal);
		fractal->function(fractal);
	}
	return (0);
}

int	handle_input_iter(int keystm, t_fractal *ft)
{
	if (keystm == 105)
	{
		ft->max_iter += 1;
		if (ft->max_iter > 1000)
			ft->max_iter = 1000;
		ft->function(ft);
	}
	if (keystm == 111)
	{
		ft->max_iter -= 1;
		if (ft->max_iter < 1)
			ft->max_iter = 1;
		ft->function(ft);
	}
	return (0);
}
