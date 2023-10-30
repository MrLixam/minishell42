/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:12:41 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/30 15:54:15 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*new_data(void)
{
	t_data	*create;

	create = ft_calloc(1, sizeof(t_data));
	if (create == NULL)
		return (NULL);
	create->redir = NULL;
	create->command = NULL;
	create->arg = NULL;
	create->next = NULL;
	return (create);
}

int	data_len(t_data *line)
{
	int	i;

	i = 0;
	while (line != NULL)
	{
		i++;
		line = line->next;
	}
	return (i);
}

int	empty_data(t_data *data)
{
	if (data->redir != NULL)
		return (1);
	if (data->command != NULL)
		return (1);
	if (data->arg != NULL)
		return (1);
	return (0);
}

void	clear_data(t_data *data)
{
	ft_lstclear(&data->redir, *free);
	free(data->command);
	ft_lstclear(&data->arg, *free);
	if (data->next != NULL)
		clear_data(data->next);
	free(data);
}

int	new_arg(t_list **lst, char *arg)
{
	t_list	*new;
	char	*tmp;

	tmp = ft_strdup(arg);
	if (tmp == NULL)
		return (write(2, "malloc failed \n", 15));
	new = ft_lstnew(tmp);
	ft_lstadd_back(lst, new);
	return (0);
}
