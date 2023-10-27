/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:53:33 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/27 02:42:42 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fix_single(int save[2], char **str, int retval)
{
	fix_fd(save);
	freetab(str);
	return (retval);
}

int	no_command(t_data *line, int save[2])
{
	redir_single(line);
	fix_fd(save);
	return (1);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
