/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 05:07:41 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/11 16:04:20 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*haystack;
	int		needle;
	char	*res;

	haystack = "Bonjour je m'appelle Oswen.\n";
	needle = 'j';
	res = ft_strchr(haystack, needle);
	if (!res)
		printf("Pas trouvee.\n");
	else
		printf("Occurrence trouvee : %s\n", res);
}
*/