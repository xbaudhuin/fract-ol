/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:24:53 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/09 19:25:09 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <limits.h>

int	parse_arg(int ac, char **av, t_fractal *fractal)
{
	if (ft_strncmp(av[0], "Mandelbrot", 11) == 0)
	{
		if (!check_mandelbrot(ac, av, fractal))
			return (0);
		fractal->function = get_mandelbrot;
		return (1);
	}
	if (ft_strncmp(av[0], "Julia", 6) == 0)
	{
		if (!check_julia(ac, av, fractal))
			return (0);
		fractal->function = get_julia;
		return (2);
	}
	if (ft_strncmp(av[0], "Tricorn", 8) == 0)
	{
		if (!check_mandelbrot(ac, av, fractal))
			return (0);
		fractal->function = get_tricorn;
		return (3);
	}
	return (display_options(), 0);
}

int	ft_atoi_parse(char *s, int *check, int *index)
{
	int			i;
	long int	ret;

	i = 0;
	ret = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		ret = ret * 10 + s[i] - '0';
		i++;
	}
	if (s[i] || i > 11 || ret > INT_MAX || ret < INT_MIN)
		*check = 1;
	if (index)
		*index = i;
	return ((int)ret);
}

static void	init_atoi_parse(int *i, double *ret, double *divider, int *sign)
{
	*i = 0;
	*ret = 0;
	*divider = 10.0;
	*sign = 1;
}

double	atodouble_parse(char *s, int *check)
{
	int		i;
	double	ret;
	double	divider;
	int		sign;

	init_atoi_parse(&i, &ret, &divider, &sign);
	ret = (double)ft_atoi_parse(s, check, &i);
	if (s[i] == '.')
	{
		*check = 0;
		i++;
		while (ft_isdigit(s[i]))
		{
			ret += (double)(s[i] - '0') / divider;
			divider *= 10;
			i++;
		}
	}
	if (s[i])
		*check = 1;
	if (s[0] == '-')
		sign = -1;
	return (ret * sign);
}
