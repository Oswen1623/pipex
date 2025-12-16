/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:21:04 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/11 16:05:29 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;
	void	*content;

	if (!f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			if (content)
				del(content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}

/*
#include <stdio.h>

void	*add_42(void *p)
{
	size_t	len;
	char	*s;

	if (!p)
		return (NULL);
	len = strlen((char *)p);
	s = (char *)malloc(len + 4); // "42_" (3) + len + '\0'
	if (!s)
		return (NULL);
	strcpy(s, "42_");
	strcat(s, (char *)p);
	return (s);
}

void	del(void *p)
{
	free(p);
}

int	main(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;
	t_list	*new;
	t_list	*t;

	a = ft_lstnew(strdup("apple"));
	b = ft_lstnew(strdup("banana"));
	c = ft_lstnew(strdup("cherry"));
	a->next = b;
	b->next = c;
	new = ft_lstmap(a, add_42, del);
	t = new;
	while (t)
	{
		printf("%s\n", (char *)t->content);
		t = t->next;
	}
	ft_lstclear(&a, del);
	ft_lstclear(&new, del);
	return (0);
}
*/