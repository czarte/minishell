/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:49:16 by smelicha          #+#    #+#             */
/*   Updated: 2024/07/22 14:21:53 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	getlen(int n);
static int	getdigit(int n, char *ptr, int neg, int l);
static char	*edge(void);
static void	*ft_calloc(size_t count, size_t size);

char	*ft_itoa(int n)
{
	int		l;
	char	*ptr;
	int		neg;
	size_t	i;

	neg = 0;
	i = 0;
	if (n == -2147483648)
		return (edge());
	if (n < 0)
	{
		n = (n * (-1));
		neg = 1;
	}
	l = getlen(n);
	if (neg)
		l++;
	ptr = ft_calloc(l + 1, sizeof(char));
	if (!ptr)
		return (0);
	getdigit(n, ptr, neg, l);
	return (ptr);
}

static void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (size)
	{
		size--;
		ptr[size] = '\0';
	}
	return ((void *)ptr);
}

static int	getlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static int	getdigit(int n, char *ptr, int neg, int l)
{
	size_t	i;

	i = 0;
	if (neg)
	{
		ptr[0] = '-';
	}
	if (n == 0)
		ptr[0] = '0';
	ptr[l] = '\0';
	while (n > 0)
	{
		ptr[l - 1] = ((n % 10) + '0');
		n = n / 10;
		l--;
	}
	return (0);
}

static char	*edge(void)
{
	char	*ptr;

	ptr = ft_calloc(12, sizeof(char));
	if (!ptr)
		return (0);
	ptr[11] = '\0';
	ptr[0] = '-';
	ptr[1] = '2';
	ptr[2] = '1';
	ptr[3] = '4';
	ptr[4] = '7';
	ptr[5] = '4';
	ptr[6] = '8';
	ptr[7] = '3';
	ptr[8] = '6';
	ptr[9] = '4';
	ptr[10] = '8';
	return (ptr);
}
