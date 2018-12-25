/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narchiba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:59:25 by narchiba          #+#    #+#             */
/*   Updated: 2018/12/25 16:05:56 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			fill_file_long(struct stat *stat, t_file_info *file)
{
	file->mode = stat->st_mode;
	if (S_ISLNK(file->mode))
	{
		ft_memset(file->lnk, 0, PATH_MAX + 1);
		readlink(file->rel_path, file->lnk, PATH_MAX);
		file->lnk_len = ft_strlen(file->lnk);
	}
	else
		file->lnk_len = 0;
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
	file->ftime = (flags & LS_U) ? stat->st_atimespec.tv_sec : file->ftime;
	file->ftime = (flags & LS_UU) ? stat->st_birthtimespec.tv_sec : file->ftime;
	file->ftime = (flags & LS_C) ? stat->st_ctimespec.tv_sec : file->ftime;
	file->size_len = ft_strlen(file->str_size);
	file->nlink_len = ft_strlen(file->st_nlink);
	file->minor_len = ft_strlen(file->minor);
	file->major_len = ft_strlen(file->major);
}

static void			fill_file(struct stat *stat, t_file_info *file)
{
	if (flags & LS_L)
	{
		fill_file_long(stat, file);
	}
	else if (flags & LS_SS)
	{
		file->st_size = stat->st_size;
	}
	else if (flags & (LS_U | LS_UU | LS_C | LS_T))
	{
		file->ftime = stat->st_mtimespec.tv_sec;
		file->ftime = (flags & LS_U) ? stat->st_atimespec.tv_sec : file->ftime;
		file->ftime = (flags & LS_UU) ? stat->st_birthtimespec.tv_sec : file->ftime;
		file->ftime = (flags & LS_C) ? stat->st_ctimespec.tv_sec : file->ftime;
	}
}

t_file_info	*ft_add_file(char *path, struct dirent	*pDirent)
{
	t_file_info		*file;
	struct stat		*stat;

	if (!(file = (t_file_info *)malloc(sizeof(t_file_info))))
		exit(EXIT_FAILURE);
	ft_memset(file, 0, sizeof(t_file_info));
	if (!(file->name = ft_strdup(pDirent->d_name)))
		exit(EXIT_FAILURE);
	if (path[0] == '/' && path[1] == '\0')
		file->rel_path = ft_strjoin(path, "", 0);
	else
		file->rel_path = ft_strjoin(path, "/", 0);
	file->rel_path = ft_strjoin(file->rel_path, file->name, 1);
	file->type = pDirent->d_type;
	file->file_len = ft_strlen(file->name);
	realpath(file->name, file->full_path);
	if (flags & (LS_T | LS_UU | LS_U | LS_SS | LS_C | LS_L))
	{
		if (!(stat = (struct stat *)malloc(sizeof(struct stat))))
			exit(EXIT_FAILURE);
		ft_memset(stat, 0 , sizeof(struct stat));
		lstat(file->rel_path, stat);
		fill_file(stat, file);
		free(stat);
	}
	return (file);
}
