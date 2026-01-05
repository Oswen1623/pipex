/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:05:38 by lucinguy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/12/24 21:05:20 by lucinguy         ###   ########.fr       */
=======
/*   Updated: 2025/12/18 15:09:33 by lucinguy         ###   ########.fr       */
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

<<<<<<< HEAD
static void	setup_input_redir(char *infile, int *pipefd)
=======
static void	child(char **argv, char **envp, int *fd)
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f
{
	int	fd_in;

<<<<<<< HEAD
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
=======
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

static void	parent(char **argv, char **envp, int *fd)
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f
{
	int	fd_out;

<<<<<<< HEAD
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
=======
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

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f

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
<<<<<<< HEAD
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
=======
		if (pipe(fd) == -1)
			error();
		fork_processes(fd, argv, envp);
	}
	else
	{
		ft_putstr_fd("Error : Wrong arguments\n", 2);
		ft_putstr_fd("Proper use : <file1> <cmd1> <cmd2> <file2>\n", 2);
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f
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
