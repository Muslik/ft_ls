/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 09:21:35 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/26 14:00:10 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print_dir_argv(char *path, size_t check)
{
	size_t	len;
	char	*buf;

	len = ft_strlen(path);
	if (!(buf = malloc(len + 3)))
		exit(EXIT_FAILURE);
	if (check)
	{
		ft_memmove(buf, "\n", 1);
		ft_memmove(buf + 1, path, len);
		ft_memmove(buf + len + 1, ":\n", 2);
		write(1, buf, len + 3);
	}
	else
	{
		ft_memmove(buf, path, len);
		ft_memmove(buf + len, ":\n", 2);
		write(1, buf, len + 2);
	}
	free(buf);
}

static void	fill_file_stat(t_file_info *file)
{
	struct stat		*stat;

	if (g_flags & (LS_T | LS_UU | LS_U | LS_SS | LS_C))
	{
		if (!(stat = (struct stat *)malloc(sizeof(struct stat))))
			exit(EXIT_FAILURE);
		ft_memset(stat, 0, sizeof(struct stat));
		lstat(file->rel_path, stat);
		if (g_flags & LS_SS)
		{
			file->st_size = stat->st_size;
		}
		else if (g_flags & (LS_U | LS_UU | LS_C | LS_T))
		{
			file->ftime = stat->st_mtimespec.tv_sec;
			file->ftime = (g_flags & LS_U) ? stat->st_atimespec.tv_sec :
				file->ftime;
			file->ftime = (g_flags & LS_UU) ? stat->st_birthtimespec.tv_sec :
				file->ftime;
			file->ftime = (g_flags & LS_C) ? stat->st_ctimespec.tv_sec :
				file->ftime;
		}
		free(stat);
	}
}

static void	fill_vector(size_t i, size_t argc, char **argv, size_t **vector)
{
	t_file_info	*file;
	DIR			*dir;

	while (i < argc)
	{
		if ((dir = opendir(argv[i])) || errno == EACCES)
		{
			if (!(file = (t_file_info *)malloc(sizeof(t_file_info))))
				exit(EXIT_FAILURE);
			ft_memset(file, 0, sizeof(t_file_info));
			if (!(file->name = ft_strdup(ft_get_name(argv[i]))))
				exit(EXIT_FAILURE);
			file->file_len = ft_strlen(file->name);
			if (!(file->rel_path = ft_strdup(argv[i])))
				exit(EXIT_FAILURE);
			fill_file_stat(file);
			if (!(ft_vector_push_back((void **)vector, &file)))
				exit(EXIT_FAILURE);
			if (errno != EACCES)
				closedir(dir);
		}
		i++;
	}
}

void		ft_print_dirs(size_t i, size_t argc, char **argv, size_t check)
{
	size_t			*vector;
	t_file_info		*file;
	size_t			len;
	size_t			j;

	vector = ft_vector_create(sizeof(size_t *));
	fill_vector(i, argc, argv, &vector);
	len = ft_vector_get_len(vector);
	ft_vector_to_array((void **)&vector);
	if (len > 1)
		ft_sort_args(vector, len);
	j = -1;
	while (++j < len)
	{
		file = (t_file_info *)(vector[j]);
		if (i != argc - 1)
		{
			if (j == 0 && check == 0)
				ft_print_dir_argv(file->rel_path, 0);
			else
				ft_print_dir_argv(file->rel_path, 1);
		}
		ft_open_dirs(file->rel_path, file->name, 0);
	}
	ft_free_vec_of_files(len, vector);
}
