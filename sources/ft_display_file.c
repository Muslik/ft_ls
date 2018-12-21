/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:31:17 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/21 18:04:22 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_files(size_t *vector, t_dir_info *dir_info)
{
	// CHOOSE OPTION OF PRINT
	ft_print_in_terminal(vector, dir_info);
}

int		cmp_alpha(void *data1, void *data2)
{
	return (ft_strcmp(((t_file_info *)data1)->name, ((t_file_info *)data2)->name));
}

int		rev_cmp_alpha(void *data1, void *data2)
{
	return (ft_strcmp(((t_file_info *)data2)->name, ((t_file_info *)data1)->name));
}

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

static void	ft_ls_sort(size_t *vector, t_dir_info *dir_info)
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

void	ft_rec_dirs(t_dir_info *dir_info, size_t **vector)
{
	size_t i;
	t_file_info *tmp;

	i = -1;
	ft_vector_to_array((void **)vector);
	if (dir_info->files_ammount > 1)
		ft_ls_sort(*vector, dir_info);
	ft_print_files(*vector, dir_info);
	if (flags & LS_RR)
	{
		while (++i < dir_info->files_ammount)
		{
			tmp = (t_file_info *)(*vector)[i];
			ft_open_dirs(tmp->rel_path, tmp->name);
		}
	}
	free(*vector);
}

static	t_file_info *ft_add_file(char *path,
		char *name)
{
	t_file_info		*file;
	struct stat		*stat;

	if (!(stat = (struct stat *)malloc(sizeof(struct stat))))
		exit(EXIT_FAILURE);
	if (!(file = (t_file_info *)malloc(sizeof(t_file_info)))
			|| (!(file->name = ft_strdup(name))))
		exit(EXIT_FAILURE);
	file->rel_path = ft_strjoin(path, "/", 0);
	file->rel_path = ft_strjoin(file->rel_path, name, 1);
	lstat(file->rel_path, stat);
	file->mode = stat->st_mode;
	file->st_nlink = stat->st_nlink;
	file->st_uid = stat->st_uid;
	file->st_gid = stat->st_gid;
	file->st_size = stat->st_size;
	file->st_rdev = stat->st_rdev;
	file->ftime = stat->st_mtimespec.tv_sec;
	file->ftime = (flags & LS_U) ? stat->st_atimespec.tv_sec : file->ftime;
	file->ftime = (flags & LS_UU) ? stat->st_birthtimespec.tv_sec : file->ftime;
	file->ftime = (flags & LS_C) ? stat->st_ctimespec.tv_sec : file->ftime;
	file->st_blocks = stat->st_blocks;
	file->file_len = ft_strlen(file->name);
	realpath(name, file->full_path);
	return (file);
}

int		ft_open_dirs(char *path, char *name)
{
	DIR				*dir;
	size_t			*vector;
	struct dirent	*pDirent;
	t_file_info		*tmp;
	t_dir_info		dir_info;

	dir_info.file_max_len = 0;
	if(!(dir = opendir(path)))
		return (ft_errno_error(path, name));
	vector = ft_vector_create(sizeof(size_t *));
	while ((pDirent = readdir(dir)) != NULL)
	{
		if (pDirent->d_name[0] != '.' || (flags & LS_A))
		{
			tmp = ft_add_file(path, pDirent->d_name);
			if (!(ft_vector_push_back((void **)&vector, &tmp)))
				exit(EXIT_FAILURE);
			dir_info.file_max_len = dir_info.file_max_len < tmp->file_len ?
				tmp->file_len : dir_info.file_max_len;
		}
	}
	dir_info.files_ammount = ft_vector_get_len(vector);
	ft_rec_dirs(&dir_info, &vector);
	return (closedir(dir));
}
