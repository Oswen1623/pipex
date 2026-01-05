/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:05:38 by lucinguy          #+#    #+#             */
/*   Updated: 2025/12/24 21:05:20 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	setup_input_redir(char *infile, int *pipefd)
{
	int	fd_in;

	fd_in = open(infile, O_RDONLY);
	if (fd_in < 0)
		msg_error("Cannot open input file");
	if (dup2(fd_in, STDIN_FILENO) == -1)
		msg_error("dup2 failed");
	close(fd_in);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		msg_error("dup2 failed");
	close(pipefd[0]);
	close(pipefd[1]);
}

static void	setup_output_redir(char *outfile, int *pipefd)
{
	int	fd_out;

	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		msg_error("Cannot create output file");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		msg_error("dup2 failed");
	close(pipefd[0]);
	close(pipefd[1]);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		msg_error("dup2 failed");
	close(fd_out);
}

static void	first_cmd(char **av, char **env, int *pipefd)
{
	setup_input_redir(av[1], pipefd);
	run_cmd(av[2], env);
}

static void	second_cmd(char **av, char **env, int *pipefd)
{
	setup_output_redir(av[4], pipefd);
	run_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (ac != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	if (pipe(pipefd) == -1)
		msg_error("Pipe creation failed");
	pid = fork();
	if (pid == -1)
		msg_error("Fork failed");
	if (pid == 0)
		first_cmd(av, env, pipefd);
	waitpid(pid, NULL, 0);
	second_cmd(av, env, pipefd);
	return (0);
}
