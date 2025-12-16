/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 01:36:18 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/11 15:36:00 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*out;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	while (len--)
		out[len] = s1[start + len];
	out[end - start] = '\0';
	return (out);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	const char	*in[] = {"   Hello World   ", "\n\t 42 School \t\n",
			"Pas d'espace", "      ", "", NULL};
	size_t		i;
	char		*out;

	i = 0;
	while (i < sizeof(in) / sizeof(in[0]))
	{
		out = ft_strtrim(in[i]);
		printf("Input : [%s]\n", in[i] ? in[i] : "(NULL)");
		if (out)
		{
			printf("Output: [%s]\n", out);
			free(out);
		}
		else
			printf("Output: (NULL)\n");
		printf("----------\n");
		i++;
	}
	return (0);
}*/
