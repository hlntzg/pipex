/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:23:06 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 12:56:29 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		a;
	int		z;

	a = 0;
	z = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	while (a <= z && ft_strchr(set, s1[a]))
		a++;
	if (a > z)
		return (ft_strdup(s1 + z + 1));
	while (z >= 0 && ft_strchr(set, s1[z]))
		z--;
	trim = ft_substr(s1, a, (z - a + 1));
	return (trim);
}
/* The function removes any chacacter of set only from the start and
 * end of s2 and returns a new string. It iterates through the start of
 * s1 until it finds a character that is not in the set and next does
 * the same from back to front, decrementing z. */
