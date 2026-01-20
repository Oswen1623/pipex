/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:05:38 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/20 13:18:45 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_child_process(char **argv, char **envp, int *pipeline_fd)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		handle_error();
	dup2(pipeline_fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(pipeline_fd[0]);
	run_command_executable(argv[2], envp);
}

void	handle_parent_process(char **argv, char **envp, int *pipeline_fd)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		handle_error();
	dup2(pipeline_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(pipeline_fd[1]);
	run_command_executable(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipeline_fd[2];
	pid_t	child_pid;

	if (argc == 5)
	{
		if (pipe(pipeline_fd) == -1)
			handle_error();
		child_pid = fork();
		if (child_pid == -1)
			handle_error();
		if (child_pid == 0)
			handle_child_process(argv, envp, pipeline_fd);
		waitpid(child_pid, NULL, 0);
		handle_parent_process(argv, envp, pipeline_fd);
	}
	else
	{
		ft_putstr_fd("Error : Bad arguments\n", 2);
		ft_putstr_fd("Correct use : ./pipex <file1> <cmd1> <cmd2> <file2>\n",
			1);
	}
	return (0);
}
