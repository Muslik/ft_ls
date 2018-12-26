/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 16:23:17 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/26 12:50:25 by narchiba         ###   ########.fr       */
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

static char	*init_buf(t_dir_info *dir_info, size_t *offset, size_t check)
{
	size_t		sum;
	size_t		buf_len;
	char		*total;
	size_t		len_total;
	char		*buf;

	if (!(total = ft_itoa(dir_info->total)))
		exit(EXIT_FAILURE);
	len_total = ft_strlen(total);
	sum = dir_info->major_max_len + dir_info->minor_max_len + 3;
	sum = (dir_info->size_max_len > (sum)) ? dir_info->size_max_len : sum;
	buf_len = dir_info->file_max_len + dir_info->links_max_len +
		dir_info->u_name_max_len + dir_info->g_name_max_len + sum + 32;
	if (!(buf = (char *)malloc(buf_len * dir_info->files_ammount + 7 + len_total
					+ dir_info->lnk_ammount * (dir_info->lnk_max_len + 4))))
		exit(EXIT_FAILURE);
	if (check)
	{
		ft_memmove(buf, "total ", 6);
		ft_memmove(buf + 6, total, len_total);
		*offset = 6 + len_total;
		buf[(*offset)++] = '\n';
	}
	free(total);
	return (buf);
}

static void	ft_print_long(size_t *vector, t_dir_info *dir_info, size_t check)
{
	t_file_info *tmp;
	size_t		i;
	char		*buf;
	size_t		offset;

	offset = 0;
	buf = init_buf(dir_info, &offset, check);
	i = -1;
	while (++i < dir_info->files_ammount)
	{
		tmp = (t_file_info *)(vector[i]);
		offset = ft_display_list(tmp, dir_info, buf, offset);
	}
	write(1, buf, offset);
	free(buf);
}

void		ft_print_files(size_t *vector, t_dir_info *dir_info, size_t check)
{
	if (g_flags & LS_L)
	{
		ft_print_long(vector, dir_info, check);
	}
	else
	{
		if (isatty(1))
			ft_print_in_terminal(vector, dir_info);
		else
			ft_print_in_pipe(vector, dir_info);
	}
}
