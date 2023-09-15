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

t_data  *new_data(void)
{
        t_data  *create;

        create = ft_calloc(1, sizeof(t_data));
        if (create == NULL)
                return (NULL);
        create->input = NULL;
        create->output = NULL;
        create->command = NULL;
        create->option = NULL;
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
}
