/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 10:25:46 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/20 14:37:54 by narchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include "libft.h"
#include <unistd.h>

size_t			g_term_col;

typedef	struct	s_dir_info
{
	size_t	file_max_len;
	size_t	term_rows;
	size_t	files_ammount;
}				t_dir_info;

typedef	struct	s_file_info
{
	char	*s;
	size_t	len;
}				t_file_info;

void	find_term_col_ammount(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	g_term_col = w.ws_col;
}

size_t	find_row_ammount(size_t file_max_len, size_t files_ammount)
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

	ft_memmove(buf, file_info->s, file_info->len);
	len = 0;
	if (k + dir_info->term_rows < dir_info->files_ammount)
	{
		len = dir_info->file_max_len - file_info->len + 1;
		ft_memset(buf + file_info->len, ' ', len);
	}
	return (file_info->len + len);
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
	write(1, buf, ft_strlen(buf));
}

void			print_in_terminal(size_t *vec_files, t_dir_info *dir_info)
{
	char	*buf;
	size_t	len;

	len = (dir_info->file_max_len + 1) * dir_info->files_ammount + 1;
	if (!(buf = malloc(len)))
		exit(0);
	ft_memset(buf, '\0', len);
	dir_info->term_rows = find_row_ammount(dir_info->file_max_len,
			dir_info->files_ammount);
	print_files(buf, vec_files, dir_info);
	free(buf);
}

int		main(void)
{
	DIR	*dir;
	struct dirent	*dp;
	size_t	*vec_files;
	t_dir_info	dir_info;
	t_file_info	*tmp;

	dir_info.file_max_len = 0;
	find_term_col_ammount();
	vec_files = (size_t *)ft_vector_create(sizeof(size_t));
	dir = opendir(".");
	while ((dp = readdir(dir)) != NULL)
	{
		tmp = (t_file_info *)malloc(sizeof(t_file_info));
		tmp->len = ft_strlen(dp->d_name);
		tmp->s = malloc(tmp->len + 1);
		ft_memmove(tmp->s, dp->d_name, tmp->len + 1);
		if (strncmp(tmp->s, ".", 1))
		{
			ft_vector_push_back((void **)&vec_files, &tmp);
			dir_info.file_max_len = dir_info.file_max_len < tmp->len ?
				tmp->len : dir_info.file_max_len;
		}
	}
	dir_info.files_ammount = ft_vector_get_len(vec_files);
	ft_vector_to_array((void **)&vec_files);
	print_in_terminal(vec_files, &dir_info);
}
