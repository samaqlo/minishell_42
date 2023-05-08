#include "minishell.h"
#include<libc.h>

t_list_env	*ft_lstlast_env(t_list_env *lst)
{
	t_list_env	*plst;
	if (!lst)
		return (0);
	plst = lst;
	while (plst->next != NULL)
		plst = plst->next;
	return (plst);
}

void	ft_lstadd_back_env(t_list_env **lst, t_list_env *new)
{
	t_list_env	*lastlst;

	if (!*lst && new)
	{
		*lst = new;
		return ;
	}
    lastlst =ft_lstlast_env(*lst);
	lastlst->next = new;
}

t_list_env	*ft_lstnew_env(char *content, char *variable)
{
	t_list_env	*new;

	new = (t_list_env *) malloc (sizeof (t_list_env));
	if (!new)
		return (NULL);
    new->variable = variable;
    new->content = content;
	new->next = NULL;
	return (new);
}

int check_equal(char *env)
{
    int i;

    i = 0;
    while(env[i])
    {
        if(env[i] == '=')
            return(i);
        i++;
    }
    return(i);
}

void    grep_env(char **env, t_list_env **enev)
{
    int i;
    int len;
    int len_eq;
    char *content;
    char *variable;
    t_list_env *tmp;

    i = 0;
    tmp = NULL;
    while(env[i])
    {
        len_eq = check_equal(env[i]);
        len = ft_strlen(env[i]);
        variable = ft_substr(env[i], 0, check_equal(env[i]));
        content = ft_substr(env[i], check_equal(env[i]) + 1, ft_strlen(env[i]) - check_equal(env[i]));
        ft_lstadd_back_env(enev, ft_lstnew_env(variable, content));
        if (i == 0)
            tmp = *enev;
        i++;
    }
        free(variable);
        free(content);
    *enev = tmp;
}

int check_n(char *av)
{
    int i;
     i = 1;
    while(av[i])
    {
        if(av[i] != 'n')
            return(1);
        i++;
    }
    return(0);
}

void    built_echo(char **av)
{
    int i;
    int test;

    i = 1;
    test = 1;
    while(av[i])
    {
        if(!ft_strncmp(av[i], "-n", 2))
        {
            if (check_n(av[i]))
            {
                test = 1;
                printf("%s ", av[i]);
            }
            else
                test = 0;
        }
        else
            printf("%s ", av[i]);
        i++;
    }
    if (test == 1)
        printf("\n");
}

char *getpath(char **env)
{
    int i = 0;
    while(env[i])
    {
        if(strncmp(env[i], "PATH=", 5) == 0)
            return(env[i] + 5);
        i++;
    }
    return(NULL);
}

int main(int ac, char **av, char **env)
{
    char *path;
    char *line;
    char **args_1;
    t_list_env *enev = NULL;
    path = getpath(env);

    grep_env(env, &enev);
    if(!path)
        return(0);
    while(1){ 
        line = readline(BOLD YELLOW"minishell> "RESET);
        if(!*line)
            continue;
        else 
        {
            args_1 = ft_split(line, ' ');
            if(!(strncmp(args_1[0], "echo", 4)))
                built_echo(args_1);
        }
    }
        // while((enev))
        // {
        //     printf("[%s]\n", (enev)->content);
        //     printf("[%s]\n", (enev)->variable);
        //     (enev) = (enev)->next;
        // }
}