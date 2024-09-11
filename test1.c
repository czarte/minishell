#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdlib.h>

size_t	ft_skip_quote_count_tokens(char const *s, char c);
size_t	ft_skip_quote_token_len(char const *s, char c);
int	ft_skip_quote_create_tokens(char **result, char const *s, char c);

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*dest;
	const char		*source;
	unsigned int	i;

	dest = dst;
	source = src;
	i = 0;
	if (dest == 0 && source == 0)
		return (0);
	while (n > 0)
	{
		dest[i] = source[i];
		i++;
		n--;
	}
	return (dst);
}


char	**ft_skip_quote_split(char const *s, char c)
{
	size_t	num_words;
	char	**result;

	num_words = ft_skip_quote_count_tokens(s, c);
	printf("Number of tokens: %lu\n", num_words);
	result = malloc((num_words + 1) * sizeof(result));
	if (!result)
		return (free(result), NULL);
	if (ft_skip_quote_create_tokens(result, s, c) != 3)
		result[num_words] = NULL;
	else
		return (result = NULL);
	return (result);
}

size_t	ft_skip_quote_count_tokens(char const *s, char c)
{
	size_t	count;
	int		in_word;
	char	quote;

	count = 0;
	quote = '\0';
	in_word = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
			quote = '\0';
		}
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

size_t	ft_skip_quote_token_len(char const *s, char c)
{
	size_t	len;
	char	quote;

	quote = '\0';
	len = 0;
	while (*s && *s != c)
	{
		if (*s == '\"' || *s == '\'')
		{
			printf("quote found\n");
			if (!quote)
				quote = *s;
			s++;
			len++;
			while (*s && *s != quote)
			{
				printf("skip\n");
				len++;
				s++;
			}
			quote = '\0';
		}
		if (*s)
		{
			printf("noskip\n");
			len++;
			s++;
		}
	}
	return (len);
}

int	ft_skip_quote_create_tokens(char **result, char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			len = ft_skip_quote_token_len(s, c);
			result[i] = malloc((len + 1));
			if (!result[i])
			{
				while (i-- > 0)
					free(result[i]);
				return (free(result), 3);
			}
			ft_memcpy(result[i], s, len);
			result[i][len] = '\0';
			s += len;
			i++;
		}
	}
	return (0);
}


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

/*
void cmd_space_trim1(char *cmd)
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
}*/

char	*ft_skip_quote_strrchr(const char *s, int c)
{
	int		sl;
	int		i;
	char	*res;
	char	quote;

	sl = ft_strlen(s);
	i = sl;
	quote = '\0';
	res = NULL;
	if ((char) c == '\0')
		return ((char *)(s + sl));
	while (i >= 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i--;
			while (s[i] && s[i] != quote)
				i--;
			quote = '\0';
		}
		if (s[i] == (char) c)
		{
			res = ((char *) s + i);
			break ;
		}
		i--;
	}
	return ((char *)res);
}

int main(void)
{
    char    test1[] = "\"This is | ?? in quote\" and this isnt but there > ? < is \'delimiter?\'";
	char	**split;
	int		i;

	split = NULL;
	i = 0;
    // char    test2[] = "test    tohohle";
    // char    test3[] = "test   tamtoho    ";
    // char    test4[] = "      a jeste tohohle";

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

	// printf("sizof char *: %li\n", sizeof(int *));
 //    printf("|%s|\n", test1);
 //    cmd_space_trim1(test1);
 //    printf("|%s|\n", test1);
 //    printf("|%s|\n", test2);
 //    cmd_space_trim1(test2);
 //    printf("|%s|\n", test2);
 //    printf("|%s|\n", test3);
 //    cmd_space_trim1(test3);
 //    printf("|%s|\n", test3);
 //    printf("|%s|\n", test4);
 //    cmd_space_trim1(test4);
 //    printf("|%s|\n", test4);

	printf("strchr: %s\n", ft_skip_quote_strrchr(test1, '?'));
	split = ft_skip_quote_split(test1, '?');
	while (split[i])
	{
		printf("%i: %s\n", (i+1), split[i]);
		free(split[i]);
		i++;
	}
	free(split);

    return (0);
}
