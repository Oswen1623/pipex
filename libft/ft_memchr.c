/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:56:39 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/10 15:41:47 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return (p);
		p++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*haystack;
	int		needle;
	char	*res;
	size_t	n;

	n = 4;
	haystack = "Bonjour je m'appelle Oswen.\n";
	needle = 'j';
	res = ft_memchr(haystack, needle, n);
	if (!res)
		printf("Pas trouvee.\n");
	else
		printf("Occurrence trouvee : %s\n", res);
}
*/