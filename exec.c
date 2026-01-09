/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:00:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/09 16:51:28 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_command(char *arg, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(arg, ' ');
	if (!args)
		exit_error("split");
	path = find_bin(args[0], env);
	if (!path)
	{
		free_strs(args);
		exit_error("command not found");
	}
	if (execve(path, args, env) == -1)
	{
		free(path);
		free_strs(args);
		exit_error("execve");
	}
}
