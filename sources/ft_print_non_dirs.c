/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_non_dirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 09:21:35 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/26 14:49:11 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			is_link(t_file_info *file)
{
	if (S_ISLNK(file->mode))
	{
		ft_memset(file->lnk, 0, PATH_MAX + 1);
		readlink(file->rel_path, file->lnk, PATH_MAX);
		file->lnk_len = ft_strlen(file->lnk);
	}
	else
		file->lnk_len = 0;
}

static void			fill_file_long(struct stat *stat, t_file_info *file)
{
	file->mode = stat->st_mode;
	is_link(file);
	file->st_size = stat->st_size;
	file->u_name_len = ft_strlen(getpwuid(stat->st_uid)->pw_name);
	file->u_name = malloc(file->u_name_len);
	ft_memmove(file->u_name, getpwuid(stat->st_uid)->pw_name, file->u_name_len);
	file->g_name_len = ft_strlen(getgrgid(stat->st_gid)->gr_name);
	file->g_name = malloc(file->g_name_len);
	ft_memmove(file->g_name, getgrgid(stat->st_gid)->gr_name, file->g_name_len);
	file->str_size = ft_itoa(stat->st_size);
	file->minor = ft_itoa(minor(stat->st_rdev));
	file->major = ft_itoa(major(stat->st_rdev));
	file->st_nlink = ft_itoa(stat->st_nlink);
	file->st_blocks = stat->st_blocks;
	file->ftime = stat->st_mtimespec.tv_sec;
	file->ftime = (g_flags & LS_U) ? stat->st_atimespec.tv_sec : file->ftime;
	file->ftime = (g_flags & LS_UU) ? stat->st_birthtimespec.tv_sec :
		file->ftime;
	file->ftime = (g_flags & LS_C) ? stat->st_ctimespec.tv_sec : file->ftime;
	file->size_len = ft_strlen(file->str_size);
	file->nlink_len = ft_strlen(file->st_nlink);
	file->minor_len = ft_strlen(file->minor);
	file->major_len = ft_strlen(file->major);
}

static t_file_info	*ft_add_non_dirs(char *path)
{
	t_file_info		*file;
	struct stat		*stat;

	if (!(file = (t_file_info *)malloc(sizeof(t_file_info))))
		exit(EXIT_FAILURE);
	ft_memset(file, 0, sizeof(t_file_info));
	if (!(file->name = ft_strdup(ft_get_name(path))))
		exit(EXIT_FAILURE);
	file->file_len = ft_strlen(file->name);
	if (!(file->rel_path = ft_strdup(path)))
		exit(EXIT_FAILURE);
	if (g_flags & (LS_T | LS_UU | LS_U | LS_SS | LS_C | LS_L))
	{
		if (!(stat = (struct stat *)malloc(sizeof(struct stat))))
			exit(EXIT_FAILURE);
		ft_memset(stat, 0, sizeof(struct stat));
		lstat(file->rel_path, stat);
		fill_file_long(stat, file);
		free(stat);
	}
	return (file);
}

static t_dir_info	fill_vector(size_t i, size_t argc,
		char **argv, size_t **vector)
{
	t_file_info		*file;
	DIR				*dir;
	t_dir_info		dir_info;

	ft_init_dir_info(&dir_info);
	i--;
	while (++i < argc)
	{
		if ((dir = opendir(argv[i])) || errno == EACCES || errno == ENOENT)
		{
			if (errno == ENOENT)
				ft_errno_error(argv[i], ft_get_name(argv[i]));
			if (errno != EACCES && errno != ENOENT)
				closedir(dir);
		}
		else
		{
			file = ft_add_non_dirs(argv[i]);
			if (!(ft_vector_push_back((void **)vector, &file)))
				exit(EXIT_FAILURE);
			ft_fill_dir_info(&dir_info, file);
		}
	}
	dir_info.files_ammount = ft_vector_get_len(*vector);
	return (dir_info);
}

size_t				ft_print_non_dirs(size_t i, size_t argc, char **argv)
{
	size_t			*vector;
	t_dir_info		dir_info;

	vector = ft_vector_create(sizeof(size_t *));
	dir_info = fill_vector(i, argc, argv, &vector);
	ft_vector_to_array((void **)&vector);
	if (dir_info.files_ammount > 1)
		ft_sort_args(vector, dir_info.files_ammount);
	if (dir_info.files_ammount > 0)
		ft_print_files(vector, &dir_info, 0);
	ft_free_vec_of_files(dir_info.files_ammount, vector);
	return (dir_info.files_ammount);
}
