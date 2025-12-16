/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:44:59 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/11 12:51:45 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	size_t	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

/*
#include <stdio.h>

int	main(void)
{
	char	test1[] = "234";
	char	test2[] = "+6543";
	char	test3[] = "--1234";
	char	test4[] = "9B123";
	int		a;
	int		b;
	int		c;
	int		d;

	a = ft_atoi(test1);
	b = ft_atoi(test2);
	c = ft_atoi(test3);
	d = ft_atoi(test4);
	printf("%d, %d, %d, %d\n", a, b, c, d);
	return (0);
}
*/