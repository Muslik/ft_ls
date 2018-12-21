/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:31:17 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/21 10:53:42 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_files(size_t *vector, t_dir_info *dir_info)
{
	// CHOOSE OPTION OF PRINT
	ft_print_in_terminal(vector, dir_info);
}

void	ft_rec_dirs(t_dir_info *dir_info, size_t **vector, char *str)
{
	size_t i;
	char *str_tmp;
	t_file_info *tmp;

	i = -1;
	ft_vector_to_array((void **)vector);
	//Choose sort и отсортить
	ft_print_files(*vector, dir_info);
	while (++i < dir_info->files_ammount)
	{
		tmp = (t_file_info *)(*vector)[i];
		if (ft_strncmp(".", tmp->name, 1))
		{
			str_tmp = ft_strjoin(str, "/", 0);
			str_tmp = ft_strjoin(str_tmp, tmp->name, 1);
			ft_open_dirs(str_tmp);
		}
	}
	free(str);
	free(*vector);
}

static	t_file_info *ft_add_file(//char path[PATH_MAX],
		char *name)
{
	t_file_info *file;
	struct stat		*stat;

	if (!(stat = (struct stat *)malloc(sizeof(struct stat))))
		ft_handle_errors(name, MALLOC_ERR);
	lstat(name, stat);
	if (!(file = (t_file_info *)malloc(sizeof(t_file_info)))
			|| (!(file->name = ft_strdup(name))))
		ft_handle_errors(name, MALLOC_ERR);
	file->mode = stat->st_mode;
	file->st_nlink = stat->st_nlink;
	file->st_uid = stat->st_uid;
	file->st_gid = stat->st_gid;
	file->st_size = stat->st_size;
	file->st_rdev = stat->st_rdev;
	file->ftime = stat->st_mtimespec.tv_sec;
	file->ntime = stat->st_mtimespec.tv_nsec;
	file->st_blocks = stat->st_blocks;
	file->file_len = ft_strlen(file->name);
	/* realpath(path, file->full_path); */
	realpath(name, file->full_path);
	return (file);
}

void	ft_open_dirs(char *str)
{
	DIR				*dir;
	size_t			*vector;
	struct dirent	*pDirent;
	t_file_info		*tmp;
	t_dir_info		dir_info;

	dir_info.file_max_len = 0;
	if(!(dir = opendir(str)))
	{
		ft_handle_errors(str, ERROR);
		return ;
	}
	vector = ft_vector_create(sizeof(size_t *));
	while ((pDirent = readdir(dir)) != NULL)
	{
		if (pDirent->d_name[0] != '.' || (flags & LS_A))
		{
			tmp = ft_add_file(pDirent->d_name);
			ft_vector_push_back((void **)&vector, &tmp);
			dir_info.file_max_len = dir_info.file_max_len < tmp->file_len ?
				tmp->file_len : dir_info.file_max_len;
		}
	}
	dir_info.files_ammount = ft_vector_get_len(vector);
	ft_rec_dirs(&dir_info, &vector, str);
	closedir(dir);
}
