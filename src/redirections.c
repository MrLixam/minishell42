/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:05:22 by marvin            #+#    #+#             */
/*   Updated: 2023/10/17 12:05:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_strcut(char *str, char *set)
{
	if (!ft_strncmp(str, set, ft_strlen(set)))
		return(ft_substr(str, ft_strlen(set), ft_strlen(str)));
	return (ft_strdup(str));
}

static int	redir_in(t_data *command, int in)
{
	t_list	*input;
	int		i;
	char	*tmp;

	input = command->input;
	if (!input)
		return (in);
	i = 0;
	while (input->next)
	{	
		tmp = ft_strcut(input->content, "./");
		if (i % 2 != 0 && access(tmp, F_OK | R_OK))
		{
			free(tmp);
			return (perror_filename("minishell : ", input->content));
		}
		free(tmp);
		input = input->next;
		i++;
	}
	tmp = ft_strcut(input->content, "./");
	if (!access(tmp, F_OK | R_OK))
	{
		i = open(tmp, O_RDONLY);
		free(tmp);
		return (i);
	}
	free(tmp);
	return (perror_filename("minishell : ", input->content));
}

static int	outfile_logic(int *fd, int *i, t_list **output, char **tmp)
{
	if (*i % 2 != 0)
	{
		if (ft_strlen(*tmp) == 1)
			*fd = open((*output)->content, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else
			*fd = open((*output)->content, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (*fd == -1)
			return (1);
		if ((*output)->next)
			close(*fd);
	}
	else
	{
		free(*tmp);
		*tmp = ft_strdup((*output)->content);
	}
	*output = (*output)->next;
	(*i)++;
	return (0);
}

static int	redir_out(t_data *command, int out)
{
	t_list	*output;
	int		i;
	int		fd;
	char	*tmp;

	output = command->output;
	if (!output)
		return (out);
	i = 1;
	tmp = ft_strdup(output->content);
	output = output->next;
	while (output)
	{
		if (outfile_logic(&fd, &i, &output, &tmp))
			return (perror_filename("minishell : ", output->content));
	}
	free(tmp);
	return (fd);
}

void	redirect(int in, int out, t_data *curr, int redir[2])
{
	redir[0] = redir_in(curr, in);
	redir[1] = redir_out(curr, out);
}

void	link_redir(int pipes[2], int fd, t_data *curr, t_local *local)
{
	int	redir[2];
	int fds[3];

	fds[0] = pipes[0];
	fds[1] = pipes[1];
	fds[2] = fd;
	redirect(fd, pipes[1], curr, redir);
	if (redir[0] == -1 || redir[1] == -1)
		exit_command(local, curr, fds, 1);
	if (curr->next != NULL)
	{
		if (redir[0] != STDIN_FILENO)
		{
			dup2(redir[0], STDIN_FILENO);
			close(redir[0]);
			close(pipes[0]);
		}
		dup2(redir[1], STDOUT_FILENO);
		close(redir[1]);
		close(pipes[1]);
	}
	if (curr != local->data)
	{
		if (redir[1] != pipes[1])
		{
			dup2(redir[1], STDOUT_FILENO);
			close(redir[1]);
			close(pipes[1]);
		}
		dup2(redir[0], STDIN_FILENO);
		close(redir[0]);
		close(pipes[0]);
	}
}