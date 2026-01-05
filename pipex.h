/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:04:19 by lucinguy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/12/24 21:05:20 by lucinguy         ###   ########.fr       */
=======
/*   Updated: 2025/12/18 15:13:31 by lucinguy         ###   ########.fr       */
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

<<<<<<< HEAD
void	msg_error(char *msg);
void	run_cmd(char *arg, char **env);
=======
// Utils

void	execute(char *argv, char **envp);
void	error(void);
char	*find_path(char *cmd, char **envp);
void	free_split(char **split);
>>>>>>> 49cac18407d5011f3af52f4f79eadefdbae62d6f

#endif