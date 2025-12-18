/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:05:38 by lucinguy          #+#    #+#             */
/*   Updated: 2025/12/18 11:25:20 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

static void	fork_processes(int *fd, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		error();
	if (pid1 == 0)
		child(argv, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
		error();
	if (pid2 == 0)
		parent(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	child(char **argv, char **envp, int *fd)
{
	int	filein;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(filein);
	execute(argv[2], envp);
}

void	parent(char **argv, char **envp, int *fd)
{
	int	fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fileout);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		fork_processes(fd, argv, envp);
	}
	else
	{
		ft_putstr_fd("Error : Wrong arguments\n", 2);
		ft_putstr_fd("Proper use : <file1> <cmd1> <cmd2> <file2>\n", 2);
	}
	return (0);
}
