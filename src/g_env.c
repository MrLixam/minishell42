#include "minishell.h"

int	env_lst(char **c_env, t_list **lst)
{
		int	i;
		
		i = -1;
		while (c_env[++i])
				if (new_arg(lst, c_env[i]))
						return (1);
		return (0);
}
