/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:59:20 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 15:35:04 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp_lst;

	if (!lst)
		return (NULL);
	tmp_lst = lst;
	while (tmp_lst->next != NULL)
		tmp_lst = tmp_lst->next;
	return (tmp_lst);
}
/* The function receive a pointer to an actual linked list and returns the
 * last node of the list. Exists the while loop when tmp_lst->next= NULL. */
