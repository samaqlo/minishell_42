#include "minishel.h"

int     quote_len(char *str, int flag, int *pos)
{
    int i;
    int len;

    i = 1;
    len = 0;
    while(str[i])
    {
        printf("[%c]\n", str[i]);
        if (str[i] == '\'' && flag == 1 && ft_strchr("|>< \t\n", str[i + 1]))
            break;
        else if (str[i] == '\"' && flag == 2 && ft_strchr("|>< \t\n", str[i + 1]))
            break;
        else if (str[i] == '\"' && flag == 2)
            i++;
        else if (str[i] == '\'' && flag == 1)
            i++;
        else
        {
            len++;
            i++;
        }
    }
        *pos += i;
    return (len);
}
int main()
{
    int pos = 0;
    char *str = "\'jdhnfcjdh\'";
    printf("%d %d\n", quote_len("\'jdhnfcjdh\'f", 2, &pos), pos);
    printf("[%c]\n", str[pos]);
}