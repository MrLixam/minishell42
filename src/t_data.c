/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:12:41 by lvincent          #+#    #+#             */
/*   Updated: 2023/09/15 16:26:35 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*new_data(void)
{
	t_data	*create;

	create = ft_calloc(1, sizeof(t_data));
	if (create == NULL)
		return (NULL);
	create->input = NULL;
	create->output = NULL;
	create->command = NULL;
	create->arg = NULL;
	create->next = NULL;
	return(create);
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
	return (0);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	clear_data(t_data *data)
{
	ft_lstclear(&data->input, *free);
	ft_lstclear(&data->output, *free);
	free(data->command);
	ft_lstclear(&data->arg, *free);
	if (data->next != NULL)
		clear_data(data->next);
	free(data);
}
