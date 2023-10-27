/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/10/27 18:10:39 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

int	redir_single(t_data *line)
{
	int	redir[2];

	redirect(STDIN_FILENO, STDOUT_FILENO, line, redir);
	if (redir[0] == -1 || redir[1] == -1)
		return (1);
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
	return (0);
}

static void	test_perms_and_type(t_data *line, t_local *local, char **str)
{
	if (fix_path(local, line))
	{
		ft_cmd_error(line->command, "command not found", str);
		exit_command(local, 127);
	}
	if (((line->command[0] == '.' && line->command[1] == '/')
			|| line->command[0] == '/'))
	{
		if (!closedir(opendir(line->command)))
		{
			ft_cmd_error(line->command, "Is a directory", str);
			exit_command(local, 126);
		}
		if (access(line->command, F_OK))
		{
			ft_cmd_error(line->command, "No such file or directory", str);
			exit_command(local, 127);
		}
	}
	if (access(line->command, X_OK))
	{
		ft_cmd_error(line->command, "Permission denied", str);
		exit_command(local, 126);
	}
}

static void	fork_logic(t_local *local, char **str)
{
	signal(SIGQUIT, sig_child);
	if (redir_single(local->data))
	{
		freetab(str);
		exit_command(local, 1);
	}
	test_perms_and_type(local->data, local, str);
	hard_close(0);
	execve(local->data->command, str, local->env);
	hard_close(1);
	perror_filename("minishell: execve :", local->data->command);
	clear_local(local, 0);
}

static int	no_pipe(t_local *local)
{
	char	**str;
	int		var[2];
	int		save[2];

	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	if (local->data->command == NULL)
		return (no_command(local->data, save));
	str = lst_to_str(local->data->arg, local->data->command);
	if (is_builtin(local->data->command))
	{
		var[1] = 1;
		if (!redir_single(local->data))
			var[1] = exec_builtin(local, str, local->data, save);
		return (fix_single(save, str, var[1]));
	}
	var[0] = fork();
	if (var[0] < 0)
		perror("minishell: fork failed");
	else if (!var[0])
		fork_logic(local, str);
	else
		waitpid(var[0], &var[1], 0);
	freetab(str);
	return (var[1]);
}

void	exec(t_local *local)
{
	int		ret;

	ret = heredoc(local);
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	if (data_len(local->data) > 1 && !ret)
	{
		local->child_pid = ft_calloc(data_len(local->data), sizeof(int));
		ret = pipeline(local);
		if (ret == -1)
			return ;
		free(local->child_pid);
	}
	else if (!ret)
		ret = no_pipe(local);
	if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	local->exit_code = ret;
	clear_heredoc(local);
	hard_close(0);
	signal(SIGINT, sig_parent);
	signal(SIGQUIT, SIG_IGN);
}
