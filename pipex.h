/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:04:19 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/08 17:55:05 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	exit_error(char *s);
void	run_command(char *arg, char **env);
void	free_strs(char **strs);
char	*find_bin(char *name, char **env);
void	execute_cmd(int in, int out, char *cmd, char **env);
int		init_pipex(int ac, char **av, int *in_fd, int *out_fd);

#endif
