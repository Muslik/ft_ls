/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detailed_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:10:01 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/25 21:20:55 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_fill_permissions(char *rights, int mode, char *path)
{
	rights[0] = ft_get_file_type(mode);
	rights[1] = (mode & S_IRUSR) ? 'r' : '-';
	rights[2] = (mode & S_IWUSR) ? 'w' : '-';
	rights[3] = (mode & S_IXUSR) ? 'x' : '-';
	rights[4] = (mode & S_IRGRP) ? 'r' : '-';
	rights[5] = (mode & S_IWGRP) ? 'w' : '-';
	rights[6] = (mode & S_IXGRP) ? 'x' : '-';
	rights[7] = (mode & S_IROTH) ? 'r' : '-';
	rights[8] = (mode & S_IWOTH) ? 'w' : '-';
	rights[9] = (mode & S_IXOTH) ? 'x' : '-';
	rights[10] = ft_get_file_acl(path);
	rights[11] = ' ';
	if (mode & S_ISUID)
		rights[3] = ('x' == rights[3] ? 's' : 'S');
	if (mode & S_ISGID)
		rights[6] = ('x' == rights[6] ? 's' : 'S');
	if (mode & S_ISVTX)
		rights[9] = ('x' == rights[9] ? 't' : 'T');
}

static void	ft_char_block(t_file_info *file, t_dir_info *dir_info, char *buf,
							size_t *offset)
{
	if (S_ISCHR(file->mode) || S_ISBLK(file->mode))
	{
		buf[(*offset)++] = ' ';
		ft_memset(buf + *offset, ' ', dir_info->major_max_len -
				file->major_len);
		*offset += dir_info->major_max_len - file->major_len;
		ft_memmove(buf + *offset, file->major, file->major_len);
		*offset += file->major_len;
		buf[(*offset)++] = ',';
		buf[(*offset)++] = ' ';
		ft_memset(buf + *offset, ' ', dir_info->minor_max_len -
				file->minor_len);
		*offset += dir_info->minor_max_len - file->minor_len;
		ft_memmove(buf + *offset, file->minor, file->minor_len);
		*offset += file->minor_len;
		buf[(*offset)++] = ' ';
	}
	else
	{
		ft_memset(buf + *offset, ' ', dir_info->size_max_len - file->size_len);
		*offset += dir_info->size_max_len - file->size_len;
		ft_memmove(buf + *offset, file->str_size, file->size_len);
		*offset += file->size_len;
		buf[(*offset)++] = ' ';
	}
}

static void	ft_lnk(t_file_info *file, char *buf, size_t *offset)
{
	if (file->lnk_len)
	{
		ft_memmove(buf + *offset, " -> ", 4);
		*offset += 4;
		ft_memmove(buf + *offset, file->lnk, file->lnk_len);
		*offset += file->lnk_len;
	}
}

int			ft_display_list(t_file_info *file, t_dir_info *dir_info, char *buf,
		size_t shft)
{
	ft_fill_permissions(buf + shft, file->mode, file->rel_path);
	shft += 12;
	ft_memset(buf + shft, ' ', dir_info->links_max_len - file->nlink_len);
	shft += dir_info->links_max_len - file->nlink_len;
	ft_memmove(buf + shft, file->st_nlink, file->nlink_len);
	shft += file->nlink_len;
	buf[shft++] = ' ';
	ft_memmove(buf + shft, file->u_name, file->u_name_len);
	shft += file->u_name_len;
	ft_memset(buf + shft, ' ', dir_info->u_name_max_len - file->u_name_len + 2);
	shft += dir_info->u_name_max_len - file->u_name_len + 2;
	ft_memmove(buf + shft, file->g_name, file->g_name_len);
	shft += file->g_name_len;
	ft_memset(buf + shft, ' ', dir_info->g_name_max_len - file->g_name_len + 2);
	shft += dir_info->g_name_max_len - file->g_name_len + 2;
	ft_char_block(file, dir_info, buf, &shft);
	ft_memmove(buf + shft, ft_show_time(file), 12);
	shft += 12;
	buf[shft++] = ' ';
	ft_memmove(buf + shft, file->name, file->file_len);
	shft += file->file_len;
	ft_lnk(file, buf, &shft);
	buf[shft++] = '\n';
	return (shft);
}
