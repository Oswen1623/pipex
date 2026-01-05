/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:00:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/05 18:03:31 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *arg, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, ' ');
	if (!cmd || !cmd[0])
	{
		free_arr(cmd);
		ft_putstr_fd("Error: empty command\n", 2);
		exit(1);
	}
	path = get_path(cmd[0], envp);
	if (!path)
	{
		free_arr(cmd);
		ft_putstr_fd("Error: command not found\n", 2);
		exit(127);
	}
	execve(path, cmd, envp);
	free(path);
	free_arr(cmd);
	ft_error("execve");
}
