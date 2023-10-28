/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:53:33 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/28 16:18:55 by lvincent         ###   ########.fr       */
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
	int i;

	i = redir_single(line);
	fix_fd(save);
	return (i);
}

void	freetab(char **tab)
{
	int	i;

	if (!tab)
		return ;
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
	freetab(local->env);
	if (local->data)
		clear_data(local->data);
	if (local->child_pid)
		free(local->child_pid);
	free(local);
	return (exit_code);
}

void	reset_redir(int *fd, int mode)
{
	close(*fd);
	if (mode)
		*fd = STDOUT_FILENO;
	else
		*fd = STDIN_FILENO;
}
