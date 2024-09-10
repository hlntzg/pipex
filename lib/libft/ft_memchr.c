/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:42:07 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 16:53:24 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	convert_c;
	size_t			i;

	str = (unsigned char *) s;
	convert_c = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == convert_c)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
/* The funcion works alike the strchr, except that memchr has a third
 * parameter (n) as the function deals with byte string (void *). */
