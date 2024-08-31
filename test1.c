#include<stdio.h>
#include<stdbool.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	dsts(char *dest, const char *src, size_t l)
{
	size_t	i;

	i = 0;
	while (l > 0)
	{
		dest[i] = src[i];
		l--;
		i++;
	}
}

static void	sstd(char *dest, const char *src, size_t l)
{
	size_t	i;

	i = l - 1;
	while (l > 0)
	{
		dest[i] = src[i];
		l--;
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t l)
{
	if (dest == src)
		return (dest);
	if (dest < src)
	{
		dsts((char *)dest, (const char *)src, l);
		return (dest);
	}
	if (dest > src)
	{
		sstd((char *)dest, (const char *)src, l);
		return (dest);
	}
	return (NULL);
}

void	cmd_space_trim1(char *cmd)
{
	int	i;
	int	last_space_pos;
    char    *src;
    bool    first_letter;

	i = 0;
	last_space_pos = 0;
    first_letter = false;
    src = NULL;
	if (!cmd || !*cmd)
		return ;
	while (cmd[i])
	{
        if ((!first_letter && cmd[i] != ' '))
        {
            if (!first_letter)
                src = (cmd + i);
            first_letter = true;
        }
		if (i)
		{
			if (cmd[i] == ' ' && cmd[i - 1] != ' ')
				last_space_pos = i;
		}
		i++;
	}
	if (cmd[i - 1] == ' ')
		cmd[last_space_pos] = '\0';
    cmd = ft_memmove(cmd, src, (ft_strlen(src) + 1));
}

void	cmd_space_trim(char *cmd)
{
	int	i;
	int	last_space_pos;

	i = 0;
	last_space_pos = 0;
	if (!cmd || !*cmd)
		return ;
	while (cmd[i])
	{
		if (i)
		{
			if (cmd[i] == ' ' && cmd[i - 1] != ' ')
				last_space_pos = i;
		}
		i++;
	}
	// if (cmd[i - 1] == ' ')
		cmd[last_space_pos] = '\0';
}


void cmd_space_trim(char *cmd)
{
    char *dest;
    char *src;
    int len;

    len = 0;
    dest = cmd;
    while (*cmd == ' ')
        cmd++;
    src = cmd;
    while(*cmd !='\0')
    {
        cmd++;
        len++;
    }
    while(*cmd == ' ')
    {
        cmd--;
        len--;
    }
    ft_memmove(dest, src, len);
    dest[len] = '\0';
    cmd = dest;
}

int main(void)
{
    char    test1[] = "     test       tohle    ";
    char    test2[] = "test    tohohle";
    char    test3[] = "test   tamtoho    ";
    char    test4[] = "      a jeste tohohle";

/*
    printf("|%s|\n", test1);
    ft_trim(test1);
    printf("|%s|\n", test1);
    printf("|%s|\n", test2);
    ft_trim(test2);
    printf("|%s|\n", test2);
    printf("|%s|\n", test3);
    ft_trim(test3);
    printf("|%s|\n", test3);
    printf("|%s|\n", test4);
    ft_trim(test4);
    printf("|%s|\n", test4);
*/


    printf("|%s|\n", test1);
    cmd_space_trim1(test1);
    printf("|%s|\n", test1);
    printf("|%s|\n", test2);
    cmd_space_trim1(test2);
    printf("|%s|\n", test2);
    printf("|%s|\n", test3);
    cmd_space_trim1(test3);
    printf("|%s|\n", test3);
    printf("|%s|\n", test4);
    cmd_space_trim1(test4);
    printf("|%s|\n", test4);

    return (0);
}
