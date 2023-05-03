#include "minishell.h"

int     quote_len(char *str, int flag, int *pos)
{
    int i;
    int len;

    i = (*pos) + 1;
    len = 0;
    while(str[i])
    {
        if (str[i] == '\'' && flag == 1 && ft_strchr("|>< \t\n", str[i + 1]))
            break;
        else if (str[i] == '\"' && flag == 2 && ft_strchr("|>< \t\n", str[i + 1]))
            break;
        else if (str[i] == '\"' && flag == 2)
            i++;
        else if (str[i] == '\'' && flag == 1)
            i++;
        // else
        // {
            len++;
            i++;
        // }
    }
        i++;
        *pos = i;
    return (len);
}
int word_len(char *str, int *pos, int *is_quote)
{
    int i;
    int len = 0;

    i = *pos;
    while(ft_strchr(" \t\n\v\f\r", str[i]))
        i++;
    while(str[i])
    {
        if (ft_strchr("<>", str[i]) && !ft_strchr(" \t\n\v\f\r><|&", str[i+1]))
            return ((*pos) = i + 1, 1);
        else if (*is_quote == 0 && str[i] == '\'')
            return (*pos = i, *is_quote = 1, quote_len(str, 1, pos));
        else if (*is_quote == 0 && str[i] == '\"')
            return (*pos = i, *is_quote = 2, quote_len(str, 2, pos));
        else if (ft_strchr(" \t\n\v\f\r", str[i]))
            break;
        else if (ft_strchr("<>|", str[i + 1]) || ft_strchr("|", str[i]))
        {
            if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '|'))
            {
                len++;
                i++;
            }
            len++;
            i++;
            break;
        }
        else {
            len++;
            i++;
        }
    }
    *pos = i;
    return (len);
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
    str = "find . -type f -name \'>*.txt\' -print0|xargs -0 >grep> -i \"search term\" >|> <djhcnjdnh>lcdk,cl,<>d;pl,c,;dl,c awk \'{print $1}\' | sort | uniq << results.txt 2>>&1";
    // printf("%c\n", str[46]);
    while(1)
    {
        start = pos;
        len = word_len(str, &pos, &is_quote);
        extractedstr = ft_substr(str, start, len, &is_quote);
            if (!extractedstr)
                break;
        printf("[%s]\n", extractedstr);
        free(extractedstr);
        i++;
    }
}
