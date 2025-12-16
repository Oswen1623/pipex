/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:01:43 by lucinguy          #+#    #+#             */
/*   Updated: 2025/10/14 22:18:26 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*newstring;
	size_t			size;

	i = 0;
	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	newstring = (char *)malloc((size + 1) * sizeof(char));
	if (!newstring)
		return (NULL);
	while (s[i])
	{
		newstring[i] = f(i, s[i]);
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
/*
char	toggle_case_i(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	main(void)
{
	char	string[] = "BonJour";
	char	*newstring;

	printf("Before : %s\n", string);
	newstring = ft_strmapi(string, toggle_case_i);
	printf("After : %s\n", newstring);
	free(newstring);
}
*/
