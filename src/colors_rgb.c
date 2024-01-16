/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:20:15 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 15:59:33 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color_red(int n, t_fractal *fractal)
{
	double	grad;
	t_color	rgb;

	grad = (double) n / (double)fractal->max_iter;
	rgb.red = (int)(255 * grad);
	rgb.blue = (int)(0);
	rgb.green = (int)(0);
	return (shift_color(rgb.red, rgb.green, rgb.blue));
}

int	color_blue(int n, t_fractal *fractal)
{
	double	grad;
	t_color	rgb;

	grad = (double) n / (double)fractal->max_iter;
	rgb.red = (int)(0);
	rgb.blue = (int)(255 * grad);
	rgb.green = (int)(0);
	return (shift_color(rgb.red, rgb.green, rgb.blue));
}

int	color_green(int n, t_fractal *fractal)
{
	double	grad;
	t_color	rgb;

	grad = (double) n / (double)fractal->max_iter;
	rgb.red = (int)(0);
	rgb.blue = (int)(0);
	rgb.green = (int)(255 * grad);
	return (shift_color(rgb.red, rgb.green, rgb.blue));
}
