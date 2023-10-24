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
#include <errno.h>

static void	exit_command(t_local *local, t_data *curr, int fd, int pipes[2])
{
	close_pipe(pipes);
	if (curr != local->data)
		close(fd);
	clear_data(local->data);
	free(local->child_pid);
	exit(127);
}

static void	do_logic(int pipes[2], int fd, t_data *curr, t_local *local)
{
	char	**str;
	int		i;

	link_redir(pipes, fd, curr, local);
	str = lst_to_str(curr->arg, curr->command);
	if (is_builtin(curr->command))
		exit(exec_builtin(local, str, curr));
	i = fix_path(&curr);
	if (i)
	{
		freetab(str);
		exit_command(local, curr, fd, pipes);
	}
	execve(curr->command, str, local->env);
	perror("minishell");
	freetab(str);
	clean_child(local, curr, pipes, fd);
}

static void	p_pass(t_local *local, t_data **curr, int *fd, int pipes[2])
{
	if (*curr != local->data)
		close(*fd);
	if ((*curr)->next != NULL)
	{
		*fd = pipes[0];
		close(pipes[1]);
	}
	*curr = (*curr)->next;
}

int	pipeline(t_local *local)
{
	int		pipes[2];
	int		fd_pid[2];
	int		i;
	t_data	*curr;

	curr = local->data;
	fd_pid[0] = STDIN_FILENO;
	i = 0;
	while (curr)
	{
		if (pipe(pipes) == -1)
			return (ft_error("minishell: pipe failed", local));
		fd_pid[1] = fork();
		if (fd_pid[1] < 0)
			return (ft_error("minishell: fork failed", local));
		else if (!fd_pid[1])
			do_logic(pipes, fd_pid[0], curr, local);
		else
		{
			p_pass(local, &curr, &fd_pid[0], pipes);
			local->child_pid[i++] = fd_pid[1];
		}
	}
	close_pipe(pipes);
	return (0);
}
