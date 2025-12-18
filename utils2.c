/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:40:52 by lucinguy          #+#    #+#             */
/*   Updated: 2025/12/18 11:40:35 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	read_line(char *buffer, int *i)
{
	int		r;
	char	c;

	*i = 0;
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[*i] = c;
		(*i)++;
		r = read(0, &c, 1);
	}
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;

	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	read_line(buffer, &i);
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (i);
}
