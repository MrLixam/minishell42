/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:36:55 by lvincent          #+#    #+#             */
/*   Updated: 2023/09/21 01:10:25 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_data(t_data **line)
{
	t_data *cmd;

	cmd = *line;
	free(cmd->command);
	ft_lstclear(cmd->arg, free());
	ft_lstclear(cmd->input, free());
	ft_lstclear(cmd->output);
	ft_lstclear(cmd->option);
	ft_lstclear(cmd->redirection);
	*line = *line->next;
	free(cmd);
}

int	file_access(char *path)
{
	return (access(path, F_OK & R_OK & W_OK & X_OK));
}

void pipeline(t_data **line, char **envp)
{
	int pipes[2];
	int save[2];
	int pid;
	t_data *curr;
	int i;

	curr = *line;
	save[0] = dup(0);
	save[1] = dup(1);
	if (pipe(pipes) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (curr)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (!pid)
		{
			close(pipes[1]);
			if (i)
			{
				dup2(pipes[0], save[0]);
				close(pipes[0]);
			}
			if (curr->next != NULL)
			{
				dup2(pipes[1], save[1]);
				close(pipes[1]);
			}
			execve(curr->command, curr->arg, envp);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(pipes[1]);
			i++;
			curr = curr->next;
		}
	}
}

int main(int argc, char **argv, char **envp)
{

}