/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/23 15:14:46 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

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

void	fix_fd(int save[2])
{
	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
	close(save[0]);
	close(save[1]);
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
		redir_single(local->data, save);
		var[1] = fix_path(&local->data);
		if (var[1])
		{
			clear_data(local->data);
			exit(127);
		}
		execve(local->data->command, str, local->env);
		perror_filename("minishell: execve ", local->data->command);
		clear_data(local->data);
	}
	else
		waitpid(var[0], &var[1], 0);
	freetab(str);
	return (var[1]);
}

void	exec(t_local *local)
{
	int		i;
	int		ret;

	i = 0;
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
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
	}
	else
	{
		ret = no_pipe(local);
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
	}
	local->exit_code = ret;
}
