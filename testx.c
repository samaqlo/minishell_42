char	*revprint(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	i--;
	while (i >= 0)
	{
		write(1, &str[i], 1);
		i--;
	}
	return (str);
}

int	main(void)
{
	revprint("HELLO WORLD");
	write(1, "\n", 1);
	revprint("zabi ohoo");
	write(1, "\n", 1);
}

shlvl_i = ft_atoi(shlvl) + 1;
shlvl = ft_itoa(shlvl_i);
change_env(enev, "SHLVL", shlvl);
free(shlvl);