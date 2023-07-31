/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouzet <gpouzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:28:26 by gpouzet           #+#    #+#             */
/*   Updated: 2023/07/31 13:30:38 by gpouzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* to do in parser // 
 * 
 * check number of ' and "			/ done
 * split 							/
 * swap env var 					/
 * make a char* 					/
 * split modified handle ' and " 	/ done
 * dispatch in right order in struct/
 * check argument					/
 * histori with readline			/ done i think
 */ 
 
int check_quote(char *readline) 
{
	int	one;
	int	two; 
	int	i;
 
	i = -1;
	one = 1;
	two = 1; 

	while (readline[++i])
	{
		if (readline[i] == 39 && two > 0)
			one *= -1;
		else if (readline[i] == 34 && one > 0)
			two *= -1;
	}
	if (one < 0 || two < 0)
		return (1);
	return (0); 
} 
/* 
int swap_env_var(char **) 
{ 
}
*/
