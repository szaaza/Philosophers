/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazanjan <<sazanjan@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:32:49 by sazanjan          #+#    #+#             */
/*   Updated: 2025/07/22 16:59:16 by sazanjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_digits(char *str, unsigned int num, long int idx)
{
	while (num > 0)
	{
		str[idx--] = 48 + (num % 10);
		num = num / 10;
	}
	return (str);
}

static long int	count_length(int n)
{
	long int	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n != 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		length;
	unsigned int	num;
	int				sign;

	sign = 1;
	length = count_length(n);
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	str[length--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		sign = -1;
		num = n * -1;
		str[0] = '-';
	}
	else
		num = n;
	return (fill_digits(str, num, length));
}
