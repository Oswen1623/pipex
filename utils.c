/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:38:05 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/05 18:03:31 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_error(char *str)
{
	perror(str);
	exit(1);
}

static char	*try_path(char **paths, char *cmd)
{
	char	*dir;
	char	*full;
	int		i;

	i = -1;
	while (paths[++i])
	{
		dir = ft_strjoin(paths[i], "/");
		full = ft_strjoin(dir, cmd);
		free(dir);
		if (access(full, F_OK) == 0)
			return (full);
		free(full);
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*result;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	result = try_path(paths, cmd);
	free_arr(paths);
	return (result);
}
