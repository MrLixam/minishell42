/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/24 15:09:54 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include <fcntl.h>

static void	init_local(t_local *local, char **envp)
{
	local->child_pid = NULL;
	local->env = NULL;
	local->exit_code = 0;
	create_env(local, envp);
}

int	clear_local(t_local	*local, int exit_code)
{
	if (local->env)
		freetab(local->env);
	clear_data(local->data);
	if (local->child_pid)
		free(local->child_pid);
	free(local);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_local	*local;

	local = ft_calloc(1, sizeof(t_local));
	if (!local)
		return (1);
	init_local(local, envp);
	(void) argc;
	(void) argv;
	while (1)
	{
		str = readline("\e[94mminishell\e[0m$ ");
		if (str == NULL)
			return (1);
		if (ft_strncmp(str, "\0", 2))
			add_history(str);
		parser(local, str);
		if (local->data == NULL)
			return (1);
		if (local->data->command != NULL)
			exec(local);
		clear_data(local->data);
		local->child_pid = NULL;
	}
}
