/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:12:06 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/09 17:25:30 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>

void	print(void *p)
{
	printf("%s\n", (char *)p);
}

int	main(void)
{
	t_list	*a;
	t_list	*b;

	a = ft_lstnew("Hello");
	b = ft_lstnew("World");
	a->next = b;
	ft_lstiter(a, print);
	free(b);
	free(a);
	return (0);
}
*/