/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:04:09 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/12 20:04:25 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "ft_ls.h"

void	ft_vector_free(void **ft_vector)
{
	size_t	**arr;

	arr = (size_t **)(ft_vector);
	if (!(arr))
		return ;
	free(*arr);
	*arr = NULL;
}
