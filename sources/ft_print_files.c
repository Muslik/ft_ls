/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 16:23:17 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/24 16:27:11 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_in_pipe(size_t *vector, t_dir_info *dir_info)
{
	size_t		i;
	t_file_info	*tmp;
	char		*buf;
	size_t		offset;
	size_t		buf_len;

	buf_len = (dir_info->file_max_len + 1) * (dir_info->files_ammount);
	if (!(buf = malloc(buf_len)))
		exit(EXIT_FAILURE);
	ft_memset(buf, 0, buf_len);
	i = -1;
	offset = 0;
	while (++i < dir_info->files_ammount)
	{
		tmp = (t_file_info *)(vector[i]);
		ft_memmove(buf + offset, tmp->name, tmp->file_len);
		offset += tmp->file_len;
		buf[offset++] = '\n';
	}
	write(1, buf, offset);
	free(buf);
}
void	ft_print_long(size_t *vector, t_dir_info *dir_info)
{
	t_file_info *tmp;
	size_t		i;
	char		*buf;
	size_t		offset;
	size_t		sum;
	size_t		buf_len;

	i = -1;
	(void)dir_info;
	sum = dir_info->major_max_len + dir_info->minor_max_len;
	sum = (dir_info->size_max_len > (sum)) ?  dir_info->size_max_len : sum;
	buf_len = dir_info->file_max_len + dir_info->links_max_len +
		dir_info->u_name_max_len + dir_info->g_name_max_len + sum + 32;
	offset = 0;
	if (!(buf = (char *)malloc(buf_len * dir_info->files_ammount)))
		exit(EXIT_FAILURE);
	ft_memset(buf, 0, buf_len);
	while (++i < dir_info->files_ammount)
	{
		tmp = (t_file_info *)(vector[i]);
		offset = ft_display_list(tmp, dir_info, buf, offset);
	}
	write(1, buf, offset);
	free(buf);
}

void	ft_print_files(size_t *vector, t_dir_info *dir_info)
{
	if (flags & LS_L)
	{
		/* ft_print_long(vector, dir_info); */
		return ;
	}
	else
	{
		if (isatty(1))
			ft_print_in_terminal(vector, dir_info);
		else
			ft_print_in_pipe(vector, dir_info);
	}
}
