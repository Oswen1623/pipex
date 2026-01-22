/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:38:05 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/22 11:43:01 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*search_in_paths(char **paths, char *command)
{
	char	*path;
	char	*part;
	int		i;

	i = 0;
	while (paths[i])
	{
		part = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part, command);
		free(part);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (0);
}

char	*check_in_path(char *command, char **envp)
{
	char	**paths;
	char	*result;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (0);
	paths = ft_split(envp[i] + 5, ':');
	result = search_in_paths(paths, command);
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (result);
}

char	*locate_command_executable(char *command, char **envp)
{
	if (ft_strchr(command, '/') != NULL)
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		return (0);
	}
	return (check_in_path(command, envp));
}

void	handle_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	run_command_executable(char *argv, char **envp)
{
	char	**args;
	int		i;
	char	*path;

	i = -1;
	args = ft_split(argv, ' ');
	path = locate_command_executable(args[0], envp);
	if (!path)
	{
		while (args[++i])
			free(args[i]);
		free(args);
		handle_error();
	}
	if (execve(path, args, envp) == -1)
		handle_error();
}
