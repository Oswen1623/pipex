/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:00:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/07 11:55:55 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Parse et exécute une commande avec ses arguments
// arg: commande sous forme de string (ex: "ls -la")
// env: variables d'environnement pour trouver le PATH

void	run_command(char *arg, char **env)
{
	char	**args;
	char	*bin;

	args = ft_split(arg, ' ');
	if (!args || !args[0])
	{
		free_strs(args);
		ft_putstr_fd("Error: empty command\n", 2);
		exit(1);
	}
	if (ft_strchr(args[0], '/'))
		bin = ft_strdup(args[0]);
	else
		bin = find_bin(args[0], env);
	if (!bin)
	{
		free_strs(args);
		ft_putstr_fd("Error: command not found\n", 2);
		exit(127);
	}
	execve(bin, args, env);
	free(bin);
	free_strs(args);
	exit_error("execve");
}
