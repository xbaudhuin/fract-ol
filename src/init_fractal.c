/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:12:39 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 18:32:49 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	init_data(t_fractal *ft)
{
	t_data	*p;

	p = malloc(sizeof(t_data));
	if (!p)
		return (free_fractal(ft), 3);
	p->img = mlx_new_image(ft->win->p_mlx, 1920, 1080);
	if (!p->img)
	{
		mlx_destroy_window(ft->win->p_mlx, ft->win->p_win);
		mlx_destroy_display(ft->win->p_mlx);
		free_fractal(ft);
		return (3);
	}
	p->addr = mlx_get_data_addr(p->img, &(p->bit), &(p->len), &(p->end));
	ft->img = p;
	return (0);
}

static int	init_win(t_fractal *ft)
{
	ft->win = malloc(sizeof(t_win));
	if (!ft->win)
		return (free_fractal(ft), 2);
	ft->win->p_mlx = mlx_init();
	if (!ft->win->p_mlx)
		return (free_fractal(ft), 1);
	ft->win->p_win = mlx_new_window(ft->win->p_mlx, 1920, 1080, "julia");
	if (!ft->win->p_win)
	{
		mlx_destroy_display(ft->win->p_mlx);
		free_fractal(ft);
		return (2);
	}
	return (0);
}

int	init_fractal(t_fractal *ft)
{
	double	factor;

	ft->screen = malloc(sizeof(*(ft->screen)));
	if (!ft->screen)
		return (1);
	ft->screen->real_max = 1.05;
	ft->screen->real_min = -2.5;
	ft->screen->i_min = -1;
	factor = ((ft->screen->real_max - ft->screen->real_min) * 1080.0 / 1920.0);
	ft->screen->i_max = ft->screen->i_min + factor;
	if (init_win(ft))
		return (2);
	if (init_data(ft))
		return (3);
	return (0);
}
