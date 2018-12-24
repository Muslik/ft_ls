/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_part1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 16:11:25 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/24 16:11:51 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		rev_cmp_size(void *data1, void *data2)
{
	int sub;

	sub = (((t_file_info *)data1)->st_size - ((t_file_info *)data2)->st_size);
	if (sub)
		return (sub);
	return (rev_cmp_alpha(data1, data2));
}

int		cmp_size(void *data1, void *data2)
{
	int sub;

	sub = (((t_file_info *)data2)->st_size - ((t_file_info *)data1)->st_size);
	if (sub)
		return (sub);
	return (cmp_alpha(data1, data2));
}

int		rev_cmp_time(void *data1, void *data2)
{
	int sub;

	sub = (((t_file_info *)data1)->ftime - ((t_file_info *)data2)->ftime);
	if (sub)
		return (sub);
	return (rev_cmp_alpha(data1, data2));
}

int		cmp_time(void *data1, void *data2)
{
	int sub;

	sub = (((t_file_info *)data2)->ftime - ((t_file_info *)data1)->ftime);
	if (sub)
		return (sub);
	return (cmp_alpha(data1, data2));
}

void	ft_ls_sort(size_t *vector, t_dir_info *dir_info)
{
	if (flags & LS_F)
		return ;
	if (flags & LS_SS)
	{
		if (flags & LS_R)
			ft_merge_sort_ft_ls(vector, 0 , dir_info->files_ammount - 1, &rev_cmp_size);
		else
			ft_merge_sort_ft_ls(vector, 0 , dir_info->files_ammount - 1, &cmp_size);
		return ;
	}
	if (flags & LS_T)
	{
		if (flags & LS_R)
			ft_merge_sort_ft_ls(vector, 0 , dir_info->files_ammount - 1, &rev_cmp_time);
		else
			ft_merge_sort_ft_ls(vector, 0 , dir_info->files_ammount - 1, &cmp_time);
		return ;
	}
	if (flags & LS_R)
		ft_merge_sort_ft_ls(vector, 0 , dir_info->files_ammount - 1, &rev_cmp_alpha);
	else
		ft_merge_sort_ft_ls(vector, 0 , dir_info->files_ammount - 1, &cmp_alpha);
}
