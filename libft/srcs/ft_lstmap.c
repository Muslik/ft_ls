/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 13:38:02 by dmorgil           #+#    #+#             */
/*   Updated: 2018/11/30 13:22:38 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem))
{
	t_list *tmplist;
	t_list *tmpres;
	t_list *res;

	if (!lst || !f)
		return (NULL);
	tmplist = (*f)(lst);
	res = ft_lstnew(tmplist->content, tmplist->content_size);
	if (res)
	{
		tmpres = res;
		lst = lst->next;
		while (lst)
		{
			tmplist = (*f)(lst);
			tmpres->next = ft_lstnew(tmplist->content, tmplist->content_size);
			if (!tmpres->next)
				return (NULL);
			tmpres = tmpres->next;
			lst = lst->next;
		}
	}
	return (res);
}
