#include <stdio.h>
#include <ctype.h>

double	atodouble_parse(char *s, int *check)
{
	int		i;
	double	ret;
	int		sign;
	double	divider;

	i = 0;
	ret = 0;
	sign = 1;
	divider = 1 / 10.0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (isdigit(s[i]))
	{
		ret = ret * 10 + s[i] - '0';
		i++;
	}
	if (s[i] == '.')
	{
		i++;
		while (isdigit(s[i]))
		{
			ret += (double)(s[i] - '0') * divider;
			divider /= 10.0;
			i++;
		}
	}
	if (s[i])
		*check = 1;
	return (ret * sign);
}

int main(int ac, char **av)
{
	int check = 0;
	printf("%f\n", atodouble_parse(av[1], &check));
	printf("%d",check);
	return (0);
}
