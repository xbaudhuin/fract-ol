/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:15:58 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 19:43:33 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "ft_printf.h"

static int	check_iter_radius(int ac, char **av, t_fractal *fractal)
{
	int	check;

	check = 0;
	if (ac >= 2)
	{
		fractal->max_iter = ft_atoi_parse(av[0], &check, NULL);
		if (fractal->max_iter > 1000)
			fractal->max_iter = 1000;
	}
	else
		fractal->max_iter = 100;
	if (check)
		return (check);
	if (ac == 3)
		fractal->radius = atodouble_parse(av[1], &check);
	else
		fractal->radius = 2;
	return (check);
}

int	check_julia(int ac, char **av, t_fractal *fractal)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (ac > 5 || ac < 3)
		return (display_options(), 0);
	fractal->c.real = atodouble_parse(av[1], &check);
	if (check || fractal->c.real > 2.0 || fractal->c.real < -2.0)
		return (display_options(), 0);
	fractal->c.i = atodouble_parse(av[2], &check);
	if (check || fractal->c.i > 2.0 || fractal->c.i < -2.0)
		return (display_options(), 0);
	if (check_iter_radius(ac - 2, &av[3], fractal))
		return (display_options(), 0);
	return (2);
}

int	check_mandelbrot(int ac, char **av, t_fractal *fractal)
{
	if (ac > 3)
		return (display_options(), 0);
	if (check_iter_radius(ac, &av[1], fractal))
		return (display_options(), 0);
	return (2);
}

int	display_options(void)
{
	ft_printf("Available fractals: <Mandelbrot> <Julia> <Tricorn>\n"
		"For Julia fractal, add 2 double number,"
		" both must be between 2.0 and -2.0\n"
		"Exemple:\nJulia 0.285 0.01\n"
		"For all fractals, you can add 2 more arguments, "
		"the first is an int and "
		"corresponds to the precision of the fractal(max is 1000)\n"
		"The second is a double and correspond to "
		"the size of the escape radius\n"
		"Avaible actions:			-arrow keys to move inside the screen\n"
		"					-left click to see the Julia "
		"fractal at the click coordinates\n"
		"					-zoom on the cursor with the mouse wheel\n"
		"					-zoom with the '+' and '-' keys\n"
		"					-backspace to reset the current fractal\n"
		"					-switch fractal with 'm' for mandebrot\n"
		"					-switch fractal with 't' for tricorn\n"
		"					-switch fractal with 'j' for julia "
		"with defaults settings\n"
		"					-switch colors with '1', '2', '3', '4', '5'\n"
		"					-change definition(max iterations) "
		"with 'i' (add until 1000)\n"
		"									   with 'o' (decrease until 0)\n");
	return (1);
}
