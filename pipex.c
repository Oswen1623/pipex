/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:05:38 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/06 17:28:19 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Processus enfant : lit depuis file1 et écrit dans le pipe
** Simule : < file1 cmd1 |
*/
static void	do_child(char **av, char **env, int *p)
{
	int	input;

	input = open(av[1], O_RDONLY);
	if (input == -1)
		exit_error("infile");
	dup2(input, STDIN_FILENO); /* Redirige stdin vers file1 */
	dup2(p[1], STDOUT_FILENO); /* Redirige stdout vers le pipe */
	close(p[0]);               /* Ferme la lecture du pipe (non utilisée) */
	close(p[1]);               /* Ferme l'écriture (déjà dupliquée) */
	close(input);              /* Ferme le fd original */
	run_command(av[2], env);   /* Exécute cmd1 */
}

/*
** Processus parent : lit depuis le pipe et écrit dans file2
** Simule : | cmd2 > file2
*/
static void	do_parent(char **av, char **env, int *p)
{
	int	output;

	output = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
		exit_error("outfile");
	dup2(p[0], STDIN_FILENO);    /* Redirige stdin vers le pipe */
	dup2(output, STDOUT_FILENO); /* Redirige stdout vers file2 */
	close(p[0]);                 /* Ferme la lecture (déjà dupliquée) */
	close(p[1]);                 /* Ferme l'écriture (non utilisée) */
	close(output);               /* Ferme le fd original */
	run_command(av[3], env);     /* Exécute cmd2 */
}

int	main(int ac, char **av, char **env)
{
	int		p[2];
	pid_t	pid;
	int		status;

	if (ac != 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
		return (1);
	}
	if (pipe(p) == -1)
		exit_error("pipe");
	pid = fork();
	if (pid == -1)
		exit_error("fork");
	if (pid == 0)
		do_child(av, env, p);
	close(p[1]);
	waitpid(pid, &status, 0);
	do_parent(av, env, p);
	return (0);
}
