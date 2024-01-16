/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:01:29 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 16:03:21 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->len + x * (img->bit / 8.0));
	*(unsigned int *)(img->addr + offset) = color;
}

static double	inter(double start, double end, t_fractal *fractal)
{
	return (start + ((end - start) / fractal->zoom));
}

void	get_new_screen(t_fractal *f)
{
	double	interpolation;

	interpolation = f->zoom;
	f->screen->real_min = inter(f->mouse.real, f->screen->real_min, f);
	f->screen->real_max = inter(f->mouse.real, f->screen->real_max, f);
	f->screen->i_min = inter(f->mouse.i, f->screen->i_min, f);
	f->screen->i_max = inter(f->mouse.i, f->screen->i_max, f);
}

double	get_new_pos_real(double x, t_fractal *fractal)
{
	double	ret;
	double	factor;

	factor = (fractal->screen->real_max - fractal->screen->real_min);
	factor /= (1920.0 - 1.0);
	ret = fractal->screen->real_min + x * factor;
	return (ret);
}

double	get_new_pos_i(double y, t_fractal *fractal)
{
	double	ret;
	double	factor;

	factor = (fractal->screen->i_max - fractal->screen->i_min) / (1080.0 - 1.0);
	ret = fractal->screen->i_max - y * factor;
	return (ret);
}
