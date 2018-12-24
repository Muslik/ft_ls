/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_term.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 10:44:36 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/24 11:33:42 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	find_row_ammount(size_t file_max_len, size_t files_ammount)
{
	size_t			i;
	size_t			k;
	size_t			sum;
	size_t			rows;

	rows = 0;
	sum = 0;
	while (++rows < files_ammount)
	{
		i = -1;
		sum = 0;
		k = 0;
		while (++i < files_ammount)
		{
			if (i && i % rows == 0)
				sum += file_max_len + 1;
		}
		sum += file_max_len + 1;
		if (sum <= g_term_col)
			break ;
	}
	return (rows);
}

static size_t	add_filename_to_string(t_file_info *file_info,
		size_t k, char *buf, t_dir_info *dir_info)
{
	size_t	len;

	ft_memmove(buf, file_info->name, file_info->file_len);
	len = 0;
	if (k + dir_info->term_rows < dir_info->files_ammount)
	{
		len = dir_info->file_max_len - file_info->file_len + 1;
		ft_memset(buf + file_info->file_len, ' ', len);
	}
	return (file_info->file_len + len);
}

static void		print_files(char *buf, size_t *vec_files,
		t_dir_info *dir_info)
{
	size_t	i;
	size_t	k;
	size_t	j;
	size_t	col;
	size_t	offset;

	col = (dir_info->files_ammount + dir_info->term_rows - 1) /
		dir_info->term_rows;
	i = -1;
	offset = 0;
	while (++i < dir_info->term_rows)
	{
		j = -1;
		while (++j < col)
		{
			k = i + j * dir_info->term_rows;
			if (k < dir_info->files_ammount)
				offset += add_filename_to_string((t_file_info *)vec_files[k],
						k, buf + offset, dir_info);
			if (k + dir_info->term_rows >= dir_info->files_ammount)
				break ;
		}
		buf[offset++] = '\n';
	}
	write(1, buf, offset);
}

void			ft_print_in_terminal(size_t *vec_files, t_dir_info *dir_info)
{
	char	*buf;
	size_t	len;

	len = (dir_info->file_max_len + 1) * dir_info->files_ammount + 1;
	if (!(buf = (char *)malloc(len + 1)))
		exit(EXIT_FAILURE);
	ft_memset(buf, '\0', len + 1);
	dir_info->term_rows = find_row_ammount(dir_info->file_max_len,
			dir_info->files_ammount);
	print_files(buf, vec_files, dir_info);
	free(buf);
}
