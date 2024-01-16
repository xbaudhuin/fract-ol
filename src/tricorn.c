/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:26:17 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 16:05:03 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_complex	tricorn(t_complex c, t_fractal *fractal, int *check)
{
	t_complex	z;
	t_complex	tmp;
	int			n;

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
			break ;
		}
		n++;
	}
	return (z);
}

int	get_tricorn(t_fractal *ft)
{
	int			x;
	int			y;
	t_complex	z;
	int			check;
	t_complex	za;

	y = -1;
	while (++y < 1080)
	{
		z.i = get_new_pos_i(y, ft) + ft->shift_y;
		x = -1;
		while (++x < 1920)
		{
			check = 0;
			z.real = get_new_pos_real(x, ft) + ft->shift_x;
			za = tricorn(z, ft, &check);
			if (!check)
				put_pixel(ft->img, x, y, 0x000000);
			else
				put_pixel(ft->img, x, y, ft->color(check, ft));
		}
	}
	mlx_put_image_to_window(ft->win->p_mlx, ft->win->p_win, ft->img->img, 0, 0);
	return (0);
}
