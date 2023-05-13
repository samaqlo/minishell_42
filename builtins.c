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
    new->c = 1;
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
        variable = ft_substr(env[i], 0, check_equal(env[i]) + 1);
        content = ft_substr(env[i], check_equal(env[i]) + 1, ft_strlen(env[i]) - check_equal(env[i]));
        ft_lstadd_back_env(enev, ft_lstnew_env(content, variable));
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
    int c;
    int test;

    i = 1;
    test = 1;
    c = 1;
    while(av[i])
    {
        while(!check_n(av[i]) && c)
        {
            test = 0;
            i++;
        }
        c = 0;
        printf("%s", av[i++]);
    }
    if (test == 1)
        printf("\n");
}
void built_pwd()
{
    char str[1024];
    if(getcwd(str, sizeof(str)))
        printf("%s\n", str);
    else
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

// unset don't remove $pwd $old_pwd $HOME
void    built_env(t_list_env *enev)
{
    while(enev)
    {
        if (enev->c)
        {printf("%s", enev->variable);
        printf("%s\n", enev->content);}
        enev = enev->next;
    }
}


void    built_unset(t_list_env *enev, char **av)
{
    int i;
    t_list_env *head;
    
    i = 1;
    head = enev;
    while(av[i])
    {
        while(enev)
        {
            if(!ft_strcmp(av[i], ft_substr(enev->variable, 0, ft_strlen(enev->variable) - 1)))
                enev->c = 0;
            enev = enev->next;
        }
        enev = head;
        i++;
    }
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
        if (!line)
            break ;
        if (!*line)
            continue;
        args_1 = ft_split(line, ' ');
        if(!(strcmp(args_1[0], "echo")))
            built_echo(args_1);
        else if(!(strcmp(args_1[0], "env")))
            built_env(enev);
        else if(!(strcmp(args_1[0], "pwd")))
                built_pwd();
         else if(!(strcmp(args_1[0], "unset")))
                built_unset(enev, args_1);
        
    
    }
}

