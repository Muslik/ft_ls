/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:04:09 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/26 08:59:09 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_vec_of_files(size_t len, size_t *vector)
{
	size_t		i;
	t_file_info *tmp;

	i = -1;
	while (++i < len)
	{
		tmp = (t_file_info *)(vector)[i];
		free(tmp->name);
		free(tmp->u_name);
		free(tmp->g_name);
		free(tmp->rel_path);
		free(tmp->str_size);
		free(tmp->minor);
		free(tmp->major);
		free(tmp->st_nlink);
		free(tmp);
	}
	free(vector);
}

void	ft_vector_free(void **ft_vector)
{
	size_t	**arr;

	arr = (size_t **)(ft_vector);
	if (!(arr))
		return ;
	free(*arr);
	*arr = NULL;
}
