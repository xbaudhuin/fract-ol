/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 23:02:00 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 18:28:58 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (ac < 2)
		return (display_options(), 1);
	if (init_fractal(&fractal))
		return (0);
	if (!parse_arg(ac - 1, &av[1], &fractal))
		return (close_window(&fractal));
	fractal.zoom = 1.0;
	fractal.mouse.i = 0.0;
	fractal.mouse.real = 0.0;
	fractal.shift_x = 0.0;
	fractal.shift_y = 0.0;
	fractal.color = color_nice;
	fractal.function(&fractal);
	mlx_mouse_hook(fractal.win->p_win, &handle_mouse, &fractal);
	mlx_key_hook(fractal.win->p_win, &handle_input, &fractal);
	mlx_hook(fractal.win->p_win, 17, 0L, close_window, &fractal);
	mlx_loop(fractal.win->p_mlx);
}
