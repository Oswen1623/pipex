/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:09:58 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/10 15:30:17 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*
#include <stdio.h>

int	main(void)
{
	int		c;
	char	chav;
	char	chap;

	c = 'a';
	chav = c;
	printf("Avant : %c\n", chav);
	chap = ft_toupper(c);
	printf("Apres : %c\n", chap);
}
*/