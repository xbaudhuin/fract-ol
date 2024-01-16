/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:28:21 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/12 15:45:39 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	free_fractal(t_fractal *fractal)
{
	if (fractal)
	{
		if (fractal->win)
		{
			if (fractal->win->p_mlx)
				free(fractal->win->p_mlx);
			free(fractal->win);
		}
		if (fractal->img)
			free(fractal->img);
		if (fractal->screen)
			free(fractal->screen);
	}
}

int	close_window(t_fractal *fractal)
{
	if (fractal->img->img)
	{
		mlx_destroy_image(fractal->win->p_mlx, fractal->img->img);
		fractal->img->img = NULL;
	}
	mlx_destroy_window(fractal->win->p_mlx, fractal->win->p_win);
	mlx_destroy_display(fractal->win->p_mlx);
	free_fractal(fractal);
	exit(1);
}

void	reset_fractal(t_fractal *fractal)
{
	double	factor;

	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->mouse.real = 0.0;
	fractal->mouse.i = 0.0;
	fractal->screen->real_max = 1.05;
	fractal->screen->real_min = -2.5;
	fractal->screen->i_min = -1;
	factor = (fractal->screen->real_max - fractal->screen->real_min);
	factor *= (1080.0 / 1920.0);
	fractal->screen->i_max = fractal->screen->i_min + factor;
}
