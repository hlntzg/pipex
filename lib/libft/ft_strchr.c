/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:19:08 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 17:00:18 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	convert_c;

	convert_c = (char) c;
	while (*s != '\0' || *s == '\0')
	{
		if (*s == convert_c)
			return ((char *) s);
		else if (*s == '\0')
			break ;
		s++;
	}
	return (NULL);
}
/* The function returns a pointer to the first occurence of c 
 * (converted to unsigned char) in the strins s (if there is one).
 * Otherswise, it returns NULL. */
