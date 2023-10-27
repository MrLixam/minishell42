/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:53:33 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/27 18:07:54 by lvincent         ###   ########.fr       */
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

int	clear_local(t_local	*local, int exit_code)
{
	if (data_len(local->data) <= 1)
		clear_heredoc(local);
	hard_close(1);
	if (local->env)
		freetab(local->env);
	clear_data(local->data);
	if (local->child_pid)
		free(local->child_pid);
	free(local);
	return (exit_code);
}
