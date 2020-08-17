// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   execute.c                                          :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: maran <maran@student.codam.nl>               +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2020/07/27 13:01:30 by maran         #+#    #+#                 */
// /*   Updated: 2020/08/14 10:09:19 by maran         ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"


// void            builtin(int fd_0, int fd_1) 

static char             *execute_builtin(t_command **command)
{
    t_env *env;                         //kopie head
    env = save_env();

    char *buf;
    // buf = (char *)malloc(sizeof(char) * 1000);

    // printf("env = [%p]\n", env);
    printf("-----------In execute builtin----------------\n");
    // printf("--------ENV BEFORE---------\n");
    // execute_env(env);
    if ((*command)->builtin == builtin_echo)
        buf = execute_echo(command);
    if ((*command)->builtin == builtin_cd)
        execute_cd();
    if ((*command)->builtin == builtin_pwd)
        execute_pwd();
    if ((*command)->builtin == builtin_env)
        execute_env(env);
    if ((*command)->builtin == builtin_export)
        execute_export(&env);
    if ((*command)->builtin == builtin_unset)
        execute_unset(&env);
    if ((*command)->builtin == builtin_exit)
        execute_exit();
    // printf("--------ENV AFTER---------\n");
    // execute_env(env);

    printf("1. buf = [%s]\n", buf);
    buf = "EN DIT WEL?";
    printf("2. buf = [%s]\n", buf);
    return (buf);
}

/*
** Tel aantal nodes. Aantal nodes is aantal processen
** ; --> dan moeten alle processen los van elkaar worden uitgevoerd van links --> rechts, met enters ertussen
** | tussen processen dan moet proces 1 writen naar fd[1] en proces 2 readen van fd[0]
** > 
*/

/*
** id == 0, dan zit je in child.
*/

static int            execute_pipe(t_command **command)
{
    int fd[2];
    int id;
    char *buf;
    int ret;

    if (pipe(fd) == -1)
    {
        printf("ERROR in opening the pipe\n");
        return (1);
    }
    id = fork();
    if (id == -1)
        printf("ERROR with fork\n");
    if (id == 0)                                                        //child
    {
        close(fd[0]);
        buf = execute_builtin(command);
        printf("3. buf = [%s]\n", buf);
        write(fd[1], &buf, sizeof(buf));
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        char *buffer;
        buffer = (char *)malloc(sizeof(char) * 1000);
        read(fd[0], &buffer, sizeof(buffer));                         //lees van fd[0] en sla op in buffer
        printf("In parent proces: > via pipe van child proces ontvangen [%s]\n", buffer);
        close(fd[0]);
    }
    return (0);   
}

int             execute(t_command **command)
{
    // printf("-----------In execute----------------\n");
    // if ((*command)->pipe_after)
        execute_pipe(command);
    // execute_builtin(command);

    return (0);
}

