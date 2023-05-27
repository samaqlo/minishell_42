#include "minishell.h"

int white_sp_len(char *str, int *i)
{
    int len = 0;
    
    while(str[*i])
    {
        if (!ft_strchr(" \t\n\v\f\r", str[*i]))
            break;
        len++;
        (*i)++;
    }
    return (len);
}
int     dollar_len(char *str, int *i)
{           
    int len = 0;
    len++;
    (*i)++;
    while(str[*i])
    {
        if (str[*i - 1] == '$' && str[*i] == '$')
            return ((*i)++, 2);
        else if (!ft_isalnum(str[*i]) && str[*i] != '_')
            break;
        (*i)++;
        len++;
    }
    return len;
}
int     len_of_word(char *str, int *i)
{
    int len = 0;
    while(str[*i])
        {
            if (ft_strchr(" \t\n\v\f\r$", str[*i]))
                return (len);
            (*i)++;
            len++;
        }
    return (len);
}
int     get_len(char *str, int *i)
{
    while (str[*i])
    {
        if (ft_strchr(" \t\n\v\f\r", str[*i]))
            return (white_sp_len(str, i));
        else if(ft_strchr("$", str[*i]))
            return (dollar_len(str, i));
        else
            return (len_of_word(str, i));
        (*i)++;
    }
    return (0);
}

int main()
{
    int i = 0;
    // int flag = 0;
    int is_quote = 0;
    int pos = 0;
    int start = 0;
    int len = 0;
    char *extractedstr;
    char *str = malloc(200); 
    str = "egfdhgbefhegfehf hdbchdbc    $hh  ";
    // while(str[i])
    // {
    //     len = get_len(str, &i);
    //     if (!len)
    //         break;
    //         i++;
    //     printf("[%d]\n", len);
    // }
    printf("strlen --> [%zu]\n", ft_strlen(str));
    while(str[i])
    {
        start = i;
        len = get_len(str, &i);
    printf("len--> [%d]\n", len);
    printf("substr --> [%s]\n", ft_substr(str, start, len));
    printf("i--> [%d]\n", i);
    }
}
