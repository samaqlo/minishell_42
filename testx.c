char *revprint(char *str)
{
    int i = 0;
    while(str[i])
    {
        i++;
    }
    i--;
    while(i >= 0)
    {
        write(1, &str[i], 1);
        i--;
    }
    return(str);
}

int main(void)
{
    revprint("HELLO WORLD");
    write(1, "\n", 1);
    revprint("zabi ohoo");
    write(1, "\n", 1);
}