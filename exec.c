/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:00:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/08 17:55:05 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_command(char *arg, char **env)
{
	char	**args;
	char	*bin;

	args = ft_split(arg, ' ');
	if (!args || !args[0])
		exit_error("empty command");
	if (ft_strchr(args[0], '/'))
		bin = ft_strdup(args[0]);
	else
		bin = find_bin(args[0], env);
	if (!bin)
		exit_error("command not found");
	execve(bin, args, env);
	exit_error("execve");
}
