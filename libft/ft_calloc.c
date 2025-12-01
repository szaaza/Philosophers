/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazanjan <<sazanjan@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:50:55 by sazanjan          #+#    #+#             */
/*   Updated: 2025/07/22 17:00:49 by sazanjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			totall;
	unsigned char	*arr;
	size_t			i;

	i = 0;
	totall = 0;
	totall = (count * size);
	arr = malloc (totall);
	if (!arr)
		return (NULL);
	while (i < totall)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}
