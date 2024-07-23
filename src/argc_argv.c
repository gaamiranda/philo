#include "../include/philo.h"

int		check_if_num(char *str)
{
	int		i;
	long	total;

	i = 0;
	total = 0;
	while (str[i])
	{
		if (str[i] - 48 < 0 || str[i] - 48 > 9)
			return 1;
		total = total * 10 + (str[i] - 48);
		i++;
		if (total > INT32_MAX)
			return 1;
	}
	return 0;
}

int		check_args(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc < 5 || argc > 6)
		return 1;
	while (argv[i])
	{
		if (check_if_num(argv[i]) != 0)
			return 2;
		i++;
	}
	return 0;
}

long	ft_atol(char *str)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (str[i])
	{
		total = total * 10 + (str[i] - 48);
		i++;
	}
	return total;
}