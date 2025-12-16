/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:04:19 by lucinguy          #+#    #+#             */
/*   Updated: 2025/12/16 15:10:38 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// Pipex

void	child(char **argv, char **envp, int *fd);
void	parent(char **argv, char **envp, int *fd);

// Utils

int		get_next_line(char **line);
void	execute(char *argv, char **envp);
void	error(void);
char	*find_path(char *cmd, char **envp);

#endif