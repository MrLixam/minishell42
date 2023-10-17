/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/17 13:15:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

static void	redir_single(t_data *line)
{
	int	redir[2];

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

static int	no_pipe(t_data *line)
{
	char	**str;
	int		var[2];

	str = lst_to_str(line->arg, line->command);
	if (is_builtin(line->command))
	{
		redir_single(line);
		return (exec_builtin(str, line));
	}
	var[0] = fork();
	if (var[0] < 0)
		perror("minishell: fork failed");
	else if (!var[0])
	{
		redir_single(line);
		fix_path(&line);
		execve(line->command, str, g_env);
		perror_filename("minishell: execve", line->command);
		clear_data(line);
	}
	else
		waitpid(var[0], &var[1], 0);
	freetab(str);
	return (var[1]);
}

void	exec(t_data *line)
{
	t_group	*group;
	int		i;
	int		ret;

	i = 0;
	if (data_len(line) > 1)
	{
		group = ft_calloc(1, sizeof(t_group));
		group->child_pid = ft_calloc(data_len(line), sizeof(int));
		group->line = &line;
		ret = pipeline(group);
		if (!ret)
			while (i < data_len(line))
				waitpid(group->child_pid[i++], &ret, 0);
		free(group->child_pid);
		free(group);
	}
	else
		ret = no_pipe(line);
	g_exit = ret;
}
