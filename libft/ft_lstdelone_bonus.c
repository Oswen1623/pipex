/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:41:15 by lucienguyen       #+#    #+#             */
/*   Updated: 2025/11/09 17:21:42 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
void	del(void *p)
{
	(void)p;
}

#include <stdio.h>

int	main(void)
{
	t_list	*node;
	char	*content;

	content = strdup("Hello");
	node = ft_lstnew(content);
	printf("Avant suppression : %s\n", (char *)node->content);
	ft_lstdelone(node, del);
	printf("Après suppression : node libéré\n");
	return (0);
}
*/