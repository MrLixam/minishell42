/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:26:44 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/24 17:05:25 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../list.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}
