/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:18:40 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 16:00:12 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	shift_color(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

int	color_nice(int n, t_fractal *fractal)
{
	double	grad;
	t_color	rgb;

	grad = (double) n / (double)fractal->max_iter;
	rgb.red = (int)(255 * grad);
	rgb.blue = (int)(255 * grad);
	rgb.green = (int)(255 * grad);
	return (shift_color(rgb.red, rgb.green, rgb.blue));
}

int	color_rainbow(int n, t_fractal *fractal)
{
	int		palette[8];

	(void)fractal;
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
