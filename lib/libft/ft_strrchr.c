/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:27:12 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 15:37:55 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	convert_c;
	char	*res;

	convert_c = (char) c;
	res = 0;
	while (*s != '\0')
	{
		if (*s == convert_c)
			res = (char *) s;
		s++;
	}
	if (convert_c == '\0')
		res = (char *) s;
	return ((char *) res);
}
/* The function is similar to strchr, but locates the last occurence of c. */
