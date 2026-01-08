/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:38:05 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/08 17:54:08 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	exit_error(char *s)
{
	perror(s);
	exit(1);
}

char	*find_bin(char *name, char **env)
{
	char	**dirs;
	char	*path;
	int		i;
	int		j;

	if (ft_strchr(name, '/') && access(name, X_OK) == 0)
		return (ft_strdup(name));
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	dirs = ft_split(env[i] + 5, ':');
	j = 0;
	while (dirs[j])
	{
		path = ft_strjoin(ft_strjoin(dirs[j], "/"), name);
		if (path && access(path, X_OK) == 0)
			return (free_strs(dirs), path);
		free(path);
		j++;
	}
	free_strs(dirs);
	return (NULL);
}
