/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:40:07 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/02/08 04:47:11 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int contain_option(char **args)
{
	int i;

	i = 0;
	while (args[++i])
		if (str_compare(args[i], "-n") == 0)
			return (1);
	return (0);
}



int exec_echo(t_shell *shell, char **args)
{
	(void)shell;
	if (array_length(args) < 2)
		printf("\n");
	if (array_length(args) == 2 && !contain_option(args))
		printf("%s\n", args[1]);
	if (array_length(args) > 2 && !contain_option(args))
	{
		printf("%s", args[2]);
		if (!contain_option(args))
			printf("\n");
	}
	return (0);
}

/*
echo (nl)
echo -n (none)
echo hello (text + nl)
echo -n hello (text)
echo "welcome to $HOME"
echo -n "welcome to $HOME"
echo -n -n (none)
 */