/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 23:22:47 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/11 12:40:37 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	rlen;
	size_t	i;
	char	*out;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		rlen = 0;
	else if (slen - start < len)
		rlen = slen - start;
	else
		rlen = len;
	out = (char *)malloc(rlen + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < rlen)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

/*
#include <stdio.h>

int	main(void)
{
	char string[] = "hello world?";
	unsigned int start = 6;
	size_t len = 5;
	newstring = ft_substr(string, start, len);
	printf("%s\n", newstring);
	free(newstring);
}*/