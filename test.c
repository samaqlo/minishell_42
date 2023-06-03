#include "minishell.h"

// int white_sp_len(char *str, int *i)
// {
//     int len = 0;
    
//     while(str[*i])
//     {
//         if (!ft_strchr(" \t\n\v\f\r", str[*i]))
//             break;
//         len++;
//         (*i)++;
//     }
//     return (len);
// }
// int     dollar_len(char *str, int *i)
// {           
//     int len = 0;
//     len++;
//     (*i)++;
//     while(str[*i])
//     {
//         if (str[*i - 1] == '$' && str[*i] == '$')
//             return ((*i)++, 2);
//         else if (!ft_isalnum(str[*i]) && str[*i] != '_')
//             break;
//         (*i)++;
//         len++;
//     }
//     return len;
// }
// int     len_of_word(char *str, int *i)
// {
//     int len = 0;
//     while(str[*i])
//         {
//             if (ft_strchr(" \t\n\v\f\r$", str[*i]))
//                 return (len);
//             (*i)++;
//             len++;
//         }
//     return (len);
// }
// int     get_len(char *str, int *i)
// {
//     while (str[*i])
//     {
//         if (ft_strchr(" \t\n\v\f\r", str[*i]))
//             return (white_sp_len(str, i));
//         else if(ft_strchr("$", str[*i]))
//             return (dollar_len(str, i));
//         else
//             return (len_of_word(str, i));
//         (*i)++;
//     }
//     return (0);
// }
// int     count_words(char *str)
// {
//     int i = 0;
//     int count = 0;
//     while (str[i])
//     {
//         if (ft_strchr(" \t\n\v\f\r", str[i]))
//         {
//             count++;
//             white_sp_len(str, &i);
//         }
//         else if(ft_strchr("$", str[i]))
//         {
//             count++;
//             dollar_len(str, &i);
//         }
//         else
//         {
//             count++;
//             len_of_word(str, &i);
//         }
//     }
//     return (count);
// }
char  *replace_space(char *str)
{
    int i;
    int j;
    i = 0;
    j = 0;
    while(str[i])
    {
        while (ft_strchr(" \t\n\v\f\r", str[i]))
            i++;
        i++;
        j++;
    }
    j++;
    char *tmp = malloc(j);
    i = 0;
    j = 0;
    while(str[i])
    {
        if ((ft_strchr(" \t\n\v\f\r", str[i]) && (!ft_strchr(" \t\n\v\f\r", str[i + 1]) || !str[i + 1])) || !ft_strchr(" \t\n\v\f\r", str[i]))
        {
            tmp[j] = str[i];
             i++;
            j++;
            }
        else if (ft_strchr(" \t\n\v\f\r", str[i]))
            i++;
    }
    return tmp;
}
void    fill_here_doc(int fd, char *del)
{
    char *input;
    while (1)
    {
        input = readline(">");
        if (!input || !ft_strcmp(input, del))
            break;
        ft_putstr_fd(input, fd);
        ft_putchar_fd('\n', fd);
        free(input);
    }
}
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
int     count_words(char *str)
{
    int i = 0;
    int count = 0;
    while (str[i])
    {
        if (ft_strchr(" \t\n\v\f\r", str[i]))
        {
            count++;
            white_sp_len(str, &i);
        }
        else if(ft_strchr("$", str[i]))
        {
            count++;
            dollar_len(str, &i);
        }
        else
        {
            count++;
            len_of_word(str, &i);
        }
    }
    return (count);
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
    str = "\'$PWD\'\"$PW\"\"    \";\"";
    // while(str[i])
    // {
    //     len = get_len(str, &i);
    //     if (!len)
    //         break;
    //         i++;
    //     printf("[%d]\n", len);
    // }
    // printf("strlen --> [%d]\n", count_words(str));
    while(str[i])
    {
        start = i;
        len = get_len(str, &i);
        printf("len--> [%d]\n", len);
        printf("substr --> [%s]\n", ft_substr(str, start, len));
        printf("i--> [%d]\n", i);
    }
    // int fd = open("hh.txt", O_CREAT | O_RDWR);
    // fill_here_doc(fd, "hh");
    // printf("[%s]\n", replace_space("   hahahah       hahahah     "));
    // printf("count words : %d\n", count_words("\'$PWD\'\"$PW\"\"    \";\""));
}
