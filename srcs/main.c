/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:57:03 by rpinto-r          #+#    #+#             */
/*   Updated: 2022/03/05 21:59:42 by rpinto-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_config(t_shell *shell)
{
    char cwd[256];

    ft_bzero(cwd, sizeof(cwd));
    if (getcwd(cwd, sizeof(cwd)))
        shell->config = str_joins(cwd, CONFIGFILE, "/");
}

void init_asciiart(void)
{
    printf("        _       _     \e[0;33m_          _ _ \e[0m\n");
    printf("  /\\/\\ (_)_ __ (_)\e[1;33m___| |__   ___| | |\e[0m\n");
    printf(" /    \\| | '_ \\| \e[0;33m/ __| '_ \\ / _ \\ | |\e[0m\n");
    printf("/ /\\/\\ \\ | | | | \e[0;33m\\__ \\ | | |  __/ | |\e[0m\n");
    printf("\\/    \\/_|_| |_|_\e[0;33m|___/_| |_|\\___|_|_|\e[0m\n");
    printf("\e[0;37mEmbrace the power of the command line ✨\e[0m\n");
    printf("version %s\n\n", VERSION);
    log_message("start " VERSION);
}

void init_prompt(t_shell *shell)
{
    char *prompt;

    while (1)
    {
        prompt = get_env(shell, "PWD");
        if (!prompt)
            prompt = ft_strjoin(NAME, DOLLAR);
        else
            prompt = str_joins(NAME, DOLLAR, get_env(shell, "PWD"));
        shell->cmdline = readline(prompt);
        if (*shell->cmdline)
        {
            add_history(shell->cmdline);
            if (parse_command_line(shell))
            {
                log_cmds(shell->cmds);
                handle_commands(shell);
                free_cmds(shell->cmds);
            }
            else
                show_command_error(shell, "minishell", "syntax error near unexpected token", 2);
        }
        free(shell->cmdline);
        free(prompt);
    }
}

int main(int argc, char *argv[], char *envs[])
{
    t_shell shell;

    (void)argc;
    (void)argv;
    // shell = ft_calloc(sizeof(t_shell), 1);
    // ft_memset(shell, 0, sizeof(shell));
    init_asciiart();
    init_envs(&shell, envs);

    // test env_utils
    // set_env(shell, ft_strdup("PATH"), str_joins(getenv("PATH"), getenv("PWD"), ":"));

    // add_env(shell, ft_strdup("OLDPWD"), ft_strdup("/"));
    // add_env(shell, ft_strdup("MARVIN"), ft_strdup("21"));
    //  printf("%s\n", get_env(shell, "MARVIN"));

    // set_env(shell, ft_strdup("MARVIN"), ft_strdup("42"));
    //  printf("%s\n", get_env(shell, "MARVIN"));

    // unset_env(shell, "MARVIN");
    // printf("%s\n", get_env(shell, "MARVIN"));
    // //print_array(shell.envs);

    // printf("%s\n", eval_variable(shell, "Hi $USERNAME, Welcome$FAKE to $HOME$FAKE!\0", 0));int g_num = 0;
  
    override_signals();
    init_config(&shell);
    init_prompt(&shell);

    // printf("%d\n", access("/bin/ls", F_OK));
    // printf("%d\n", access("ls", F_OK));
    // printf("%d\n", access("./Makefile", F_OK));
    // printf("%d\n\n", access("./srcs", F_OK));

    // printf("%d\n", access("/bin/ls", X_OK));
    // printf("%d\n", access("ls", X_OK));
    // printf("%d\n", access("./Makefile", X_OK));
    // printf("%d\n", access("./srcs", X_OK));
    // free_array(shell.envs);
    return (0);
}
