/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:05:38 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/09 17:13:18 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(int in, int out, char *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork");
	if (pid == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		close(in);
		close(out);
		run_command(cmd, env);
		exit_error("execve");
	}
	waitpid(pid, NULL, 0);
}

int	init_pipex(int ac, char **av, int *in_fd, int *out_fd)
{
	int	file1;
	int	file2;

	file1 = open(av[1], O_RDONLY);
	file2 = open(av[ac], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file1 == -1 || file2 == -1)
	{
		exit_error("open");
		return (1);
	}
	else
	{
		*in_fd = file1;
		*out_fd = file2;
		return (0);
	}
}

int	main(int ac, char **av, char **env)
{
	int		in_fd;
	int		out_fd;
	int		p[2];
	pid_t	pid;

	if (init_pipex(ac, av, &in_fd, &out_fd))
		return (1);
	if (pipe(p) == -1)
		exit_error("pipe");
	pid = fork();
	if (pid == -1)
		exit_error("fork");
	if (pid == 0)
	{
		close(p[0]);
		execute_cmd(in_fd, p[1], av[2], env);
	}
	close(p[1]);
	waitpid(pid, NULL, 0);
	execute_cmd(p[0], out_fd, av[3], env);
	return (0);
}
