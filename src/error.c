/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 02:32:40 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 20:53:11 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_error(char *command, char *file, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

void	ft_cmd_error(char *cmd, char *error, char **str)
{
	freetab(str);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

int	ft_error(char *message)
{
	perror(message);
	return (-1);
}

int	perror_filename(char *command, char *filename)
{
	char	*err;

	err = ft_strjoin(command, filename);
	perror(err);
	free(err);
	return (-1);
}

int	err_dispatch(char *lex)
{
	if (lex[0] == '<' || lex[0] == '>' || lex[0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (lex[0] == '>')
			ft_putstr_fd(lex, 2);
		if (lex[0] == '<')
			ft_putstr_fd(lex, 2);
		if (lex[0] == '|')
			ft_putstr_fd(lex, 2);
		ft_putendl_fd("'", 2);
		return (2);
	}
	return (0);
}
