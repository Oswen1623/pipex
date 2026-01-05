/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:05:38 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/05 22:46:52 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	do_child(char **av, char **env, int *p)
{
	int	input;

	input = open(av[1], O_RDONLY);
	if (input == -1)
		exit_error("infile");
	dup2(input, STDIN_FILENO);
	dup2(p[1], STDOUT_FILENO);
	close(p[0]);
	close(p[1]);
	close(input);
	run_command(av[2], env);
}

static void	do_parent(char **av, char **env, int *p)
{
	int	output;

	output = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
		exit_error("outfile");
	dup2(p[0], STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(p[0]);
	close(p[1]);
	close(output);
	run_command(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		p[2];
	pid_t	pid;

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
	waitpid(pid, NULL, 0);
	do_parent(av, env, p);
	return (0);
}
