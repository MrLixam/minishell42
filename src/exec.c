/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/25 12:47:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

static void	redir_single(t_data *line, int save[2])
{
	int	redir[2];

	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	redirect(STDIN_FILENO, STDOUT_FILENO, line, redir);
	if (redir[0] != STDIN_FILENO)
	{
		dup2(redir[0], STDIN_FILENO);
		close(redir[0]);
	}
	if (redir[1] != STDOUT_FILENO)
	{
		dup2(redir[1], STDOUT_FILENO);
		close(redir[1]);
	}
}

static void	fork_logic(t_local *local, int save[2], char **str)
{
	redir_single(local->data, save);
	if (fix_path(local, local->data))
	{
		freetab(str);
		exit(clear_local(local, 127));
	}
	execve(local->data->command, str, local->env);
	perror_filename("minishell: execve ", local->data->command);
	clear_local(local, 0);
}

static void	parent_wait(int *ret, int pid)
{
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	waitpid(pid, ret, 0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_parent);
}

static int	no_pipe(t_local *local)
{
	char	**str;
	int		var[2];
	int		save[2];

	str = lst_to_str(local->data->arg, local->data->command);
	if (is_builtin(local->data->command))
	{
		redir_single(local->data, save);
		var[1] = exec_builtin(local, str, local->data);
		fix_fd(save);
		return (var[1]);
	}
	var[0] = fork();
	if (var[0] < 0)
		perror("minishell: fork failed");
	else if (!var[0])
	{
		signal(SIGQUIT, sig_child);
		fork_logic(local, save, str);
	}
	else
		parent_wait(&var[1], var[0]);
	freetab(str);
	return (var[1]);
}

void	exec(t_local *local)
{
	int		i;
	int		ret;

	i = parse_heredoc(&local->data);
	if (i)
		return ;
	if (data_len(local->data) > 1)
	{
		local->child_pid = ft_calloc(data_len(local->data), sizeof(int));
		ret = pipeline(local);
		if (ret == -1)
		{
			free(local->child_pid);
			return ;
		}
		while (i < data_len(local->data))
			waitpid(local->child_pid[i++], &ret, 0);
		free(local->child_pid);
	}
	else
		ret = no_pipe(local);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	local->exit_code = ret;
}
