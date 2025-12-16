/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 04:47:42 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/13 10:49:56 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;

	i = 0;
	while (i < dsize && dst[i] != '\0')
		i++;
	dst_len = i;
	j = 0;
	if (i == dsize)
		return (dsize + ft_strlen(src));
	while (src[j] != '\0' && (i + j + 1) < dsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i + j < dsize)
		dst[i + j] = '\0';
	return (dst_len + ft_strlen(src));
}
/*
#include <stdio.h>

int	main(void)
{
	char	dst[20] = "Hello";
	char	src[] = " World!";
	size_t	res;

	res = ft_strlcat(dst, src, sizeof(dst));
	printf("Result: %s | Total length: %zu\n", dst, res);
	return (0);
}
*/