/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:05:38 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/08 17:55:05 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(int in, int out, char *cmd, char **env)
{
	if (dup2(in, STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
		exit_error("dup2");
	run_command(cmd, env);
}

int	init_pipex(int ac, char **av, int *in_fd, int *out_fd)
{
	if (ac != 5)
		return (ft_putstr_fd("Ex: ./pipex file1 cmd1 cmd2 file2\n", 2), 1);
	*in_fd = open(av[1], O_RDONLY);
	if (*in_fd < 0)
		exit_error("infile");
	*out_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out_fd < 0)
		exit_error("outfile");
	return (0);
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
