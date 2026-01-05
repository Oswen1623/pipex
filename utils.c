/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:38:05 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/05 22:46:52 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	exit_error(char *s)
{
	perror(s);
	exit(1);
}

static char	*check_cmd(char **dirs, char *name)
{
	char	*tmp;
	char	*bin;
	int		i;

	i = -1;
	while (dirs[++i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		bin = ft_strjoin(tmp, name);
		free(tmp);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
	}
	return (NULL);
}

char	*find_bin(char *name, char **env)
{
	char	**dirs;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	dirs = ft_split(env[i] + 5, ':');
	bin = check_cmd(dirs, name);
	free_strs(dirs);
	return (bin);
}
