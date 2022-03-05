/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:41:02 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/05 21:56:49 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int show_command_error(t_shell *shell, char *cmd, char *msg, int exit_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd("", 2);
	shell->exit_status = exit_status;
	return (0);
}

void save_exit_status(t_shell *shell)
{
	if (get_env(shell, "?"))
		set_env(shell, ft_strdup("?"), ft_itoa(shell->exit_status));
	else
		add_env(shell, ft_strdup("?"), ft_itoa(shell->exit_status));
	shell->exit_status = 0;
}