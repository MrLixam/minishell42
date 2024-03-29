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
#include <signal.h>

static void	test_perms_and_type(t_data *cmd, t_local *l, char **str)
{
	int	cond;

	cond = ((cmd->command[0] == '.' && cmd->command[1] == '/')
			|| cmd->command[0] == '/');
	if (fix_path(l, cmd))
	{
		ft_cmd_error(cmd->command, "command not found", str);
		exit_command(l, 127);
	}
	if (cond && !closedir(opendir(cmd->command)))
	{
		ft_cmd_error(cmd->command, "Is a directory", str);
		exit_command(l, 126);
	}
	if (cond && access(cmd->command, F_OK))
	{
		ft_cmd_error(cmd->command, "No such file or directory", str);
		exit_command(l, 127);
	}
	if (access(cmd->command, X_OK))
	{
		ft_cmd_error(cmd->command, "Permission denied", str);
		exit_command(l, 126);
	}
}

static void	do_logic(int pipes[2], int fd, t_data *curr, t_local *local)
{
	char	**str;
	int		i;

	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	if (curr->command == NULL)
		no_command_pipe(local, pipes, curr, fd);
	link_redir(pipes, fd, curr, local);
	str = lst_to_str(curr->arg, curr->command);
	if (is_builtin(curr->command))
	{
		i = exec_builtin(local, str, curr, pipes);
		freetab(str);
		exit_command(local, i);
	}
	test_perms_and_type(curr, local, str);
	hard_close(0);
	execve(curr->command, str, local->env);
	perror("minishell: execve: ");
	hard_close(1);
	freetab(str);
	exit_command(local, errno);
}

static void	p_pass(t_local *local, t_data **curr, int *fd, int pipes[2])
{
	if (*curr != local->data)
		close(*fd);
	if ((*curr)->next != NULL)
	{
		*fd = dup(pipes[0]);
		close_pipe(pipes);
	}
	*curr = (*curr)->next;
}

void	wait_and_close(t_local *local)
{
	int	i;

	i = 0;
	hard_close(0);
	while (i < data_len(local->data))
	{
		waitpid(local->child_pid[i], &local->exit_code, 0);
		i++;
	}
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
			return (ft_error("minishell: pipe failed"));
		fd_pid[1] = fork();
		if (fd_pid[1] < 0)
			return (ft_error("minishell: fork failed"));
		else if (!fd_pid[1])
			do_logic(pipes, fd_pid[0], curr, local);
		else
		{
			p_pass(local, &curr, &fd_pid[0], pipes);
			local->child_pid[i++] = fd_pid[1];
		}
	}
	wait_and_close(local);
	return (local->exit_code);
}
