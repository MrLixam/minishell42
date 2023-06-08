/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:24:56 by gpouzet           #+#    #+#             */
/*   Updated: 2023/04/14 12:38:04 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../list.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (*lst != NULL && del != NULL)
	{
		tmp = *lst;
		while (tmp != NULL)
		{
			tmp = tmp->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
		}
	}
}
