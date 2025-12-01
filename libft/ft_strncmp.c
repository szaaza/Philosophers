/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazanjan <<sazanjan@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:12:13 by szanjani          #+#    #+#             */
/*   Updated: 2025/07/22 17:00:14 by sazanjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		result = (unsigned char)s1[i] -(unsigned char) s2[i];
		if (result == 0)
			i++;
		else
			return (result);
	}
	if (i < n)
	{
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		return (0);
	}
	return (result);
}
