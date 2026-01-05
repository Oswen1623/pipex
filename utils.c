/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:38:05 by lucinguy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/12/24 21:05:20 by lucinguy         ###   ########.fr       */
=======
/*   Updated: 2025/12/18 11:25:20 by lucinguy         ###   ########.fr       */
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

<<<<<<< HEAD
static char	*get_env_path(char **env)
{
	int	idx;

	idx = 0;
	while (env[idx])
=======
static void	free_paths(char **paths)
{
	free_split(paths);
}

static char	*check_path(char **paths, char *cmd)
{
	char	*part_path;
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f
	{
		if (ft_strncmp(env[idx], "PATH=", 5) == 0)
			return (env[idx] + 5);
		idx++;
	}
	return (NULL);
<<<<<<< HEAD
=======
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	path = check_path(paths, cmd);
	free_paths(paths);
	return (path);
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*resolve_cmd_path(char *cmd, char **env)
{
	char	**dirs;
	char	*full_path;
	char	*tmp;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (!get_env_path(env))
		return (NULL);
	dirs = ft_split(get_env_path(env), ':');
	i = -1;
	while (dirs[++i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_tab(dirs);
			return (full_path);
		}
		free(full_path);
	}
	free_tab(dirs);
	return (NULL);
}

void	msg_error(char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	run_cmd(char *arg, char **env)
{
<<<<<<< HEAD
	char	**args;
	char	*bin_path;

	args = ft_split(arg, ' ');
	if (!args || !args[0])
	{
		free_tab(args);
		msg_error("empty command");
	}
	bin_path = resolve_cmd_path(args[0], env);
	if (!bin_path)
	{
		free_tab(args);
		msg_error("command not found");
	}
	if (execve(bin_path, args, env) == -1)
	{
		free(bin_path);
		free_tab(args);
		msg_error("execution failed");
=======
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		free_split(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_split(cmd);
		free(path);
		error();
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f
	}
}
