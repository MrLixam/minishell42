/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:09:14 by marvin            #+#    #+#             */
/*   Updated: 2023/10/17 13:09:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	do_logic(int pipes[2], int fd, t_data *curr, t_group *group)
{
	char	**str;
	int		i;

	link_redir(pipes, fd, curr, group);
	str = lst_to_str(curr->arg, curr->command);
	if (is_builtin(curr->command))
		exit(exec_builtin(str, curr));
	i = fix_path(&curr);
	if (i)
	{
		freetab(str);
		clean_child(group, curr, pipes, fd);
		exit(127);
	}
	execve(curr->command, str, g_env);
	freetab(str);
	perror("minishell");
	clean_child(group, curr, pipes, fd);
}

static void	p_pass(t_group *group, t_data **curr, int *fd, int pipes[2])
{
	if (*curr != *group->line)
		close(*fd);
	if ((*curr)->next != NULL)
	{
		*fd = pipes[0];
		close(pipes[1]);
	}
	*curr = (*curr)->next;
}

int	pipeline(t_group *group)
{
	int		pipes[2];
	int		fd_pid[2];
	int		i;
	t_data	*curr;

	curr = *group->line;
	fd_pid[0] = STDIN_FILENO;
	i = 0;
	while (curr)
	{
		if (pipe(pipes) == -1)
			return (ft_error("minishell: pipe failed", group));
		fd_pid[1] = fork();
		if (fd_pid[1] < 0)
			return (ft_error("minishell: fork failed", group));
		else if (!fd_pid[1])
			do_logic(pipes, fd_pid[0], curr, group);
		else
		{
			p_pass(group, &curr, &fd_pid[0], pipes);
			group->child_pid[i++] = fd_pid[1];
		}
	}
	close_pipe(pipes);
	return (0);
}
