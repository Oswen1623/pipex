/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:00:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/06 17:37:44 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Parse et exécute une commande avec ses arguments
** arg: commande sous forme de string (ex: "ls -la")
** env: variables d'environnement pour trouver le PATH
*/
void	run_command(char *arg, char **env)
{
	char	**args;
	char	*bin;

	/* Split la commande par espaces pour obtenir les arguments */
	args = ft_split(arg, ' ');
	if (!args || !args[0])
	{
		free_strs(args);
		ft_putstr_fd("Error: empty command\n", 2);
		exit(1);
	}
	/* Si la commande contient '/', c'est un chemin absolu/relatif */
	if (ft_strchr(args[0], '/'))
		bin = ft_strdup(args[0]);
	/* Sinon, chercher dans le PATH */
	else
		bin = find_bin(args[0], env);
	/* Si la commande n'est pas trouvée, exit avec code 127 */
	if (!bin)
	{
		free_strs(args);
		ft_putstr_fd("Error: command not found\n", 2);
		exit(127);
	}
	/* Remplace le processus actuel par la commande */
	execve(bin, args, env);
	/* Si execve retourne, c'est qu'il y a eu une erreur */
	free(bin);
	free_strs(args);
	exit_error("execve");
}
