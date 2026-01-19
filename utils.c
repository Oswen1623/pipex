/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:38:05 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/19 11:47:59 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*locate_command_executable(char *command, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
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
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

/*
** A simple error displaying function.
*/
void	handle_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

/*
** Function that takes the command and sends it to locate_command_executable
** before executing it.
*/
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
