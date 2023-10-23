/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:03:11 by gpouzet           #+#    #+#             */
/*   Updated: 2023/10/23 15:10:04 by r                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include <fcntl.h>

static void	clear_local(t_local	*local)
{
	free(local);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_local	*local;

	local = ft_calloc(1, sizeof(t_local));
	if (!local)
		return (1);
	create_env(local, envp);
	local->exit_code = 0;
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
	}
	clear_local(local);
}
