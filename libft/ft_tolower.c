/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:06:57 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/10 15:29:34 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*
#include <stdio.h>

int	main(void)
{
	int		c;
	char	chav;
	char	chap;

	c = 'A';
	chav = c;
	printf("Avant : %c\n", chav);
	chap = ft_tolower(c);
	printf("Apres : %c\n", chap);
}
*/