/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:38:05 by lucinguy          #+#    #+#             */
/*   Updated: 2026/01/06 17:37:44 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Libère un tableau de strings (char **)
** Libère chaque string puis le tableau lui-même
*/
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

/*
** Affiche une erreur système avec perror et quitte avec exit(1)
** À utiliser uniquement pour les erreurs système (open, pipe, fork, etc.)
*/
void	exit_error(char *s)
{
	perror(s);
	exit(1);
}

/*
** Vérifie si une commande existe dans les répertoires du PATH
** dirs: tableau de répertoires (ex: ["/bin", "/usr/bin", ...])
** name: nom de la commande à chercher (ex: "ls")
** Retourne: le chemin complet de la commande ou NULL si non trouvée
*/
static char	*check_cmd(char **dirs, char *name)
{
	char	*tmp;
	char	*bin;
	int		i;

	i = -1;
	while (dirs[++i])
	{
		/* Construire le chemin complet : dir + "/" + name */
		tmp = ft_strjoin(dirs[i], "/");
		bin = ft_strjoin(tmp, name);
		free(tmp);
		/* Vérifier si le fichier existe */
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
	}
	return (NULL);
}

/*
** Trouve le chemin complet d'une commande dans le PATH
** name: nom de la commande (ex: "ls")
** env: variables d'environnement contenant PATH
** Retourne: le chemin complet (ex: "/bin/ls") ou NULL si non trouvée
*/
char	*find_bin(char *name, char **env)
{
	char	**dirs;
	char	*bin;
	int		i;

	/* Chercher la variable PATH dans l'environnement */
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	/* Split PATH par ':' pour obtenir les répertoires */
	dirs = ft_split(env[i] + 5, ':');
	/* Chercher la commande dans chaque répertoire */
	bin = check_cmd(dirs, name);
	free_strs(dirs);
	return (bin);
}
