/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detailed_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:10:01 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/18 20:12:18 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char ft_get_file_type(int mode)
{
	char		filetype;

	/* mode = mode & S_IFMT; */
	filetype = 0;
	filetype = (S_ISDIR(mode)) ? 'd' : filetype;
	filetype = (S_ISCHR(mode)) ? 'c' : filetype;
	filetype = (S_ISBLK(mode)) ? 'b' : filetype;
	filetype = (S_ISREG(mode)) ? '-' : filetype;
	filetype = (S_ISFIFO(mode)) ? 'p' : filetype;
	filetype = (S_ISLNK(mode)) ? 'l' : filetype;
	filetype = (S_ISSOCK(mode)) ? 's' : filetype;
	return (filetype);
}

static char ft_get_file_acl(char *path)
{
	ssize_t		xattr;
	acl_entry_t dummy;
	acl_t		acl;
	char		sym;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl = NULL;
	}
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	sym = (xattr > 0) ? '@' : ' ';
	sym = (acl != NULL) ? '+' : sym;
	acl_free(acl);
	return (sym);
}

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

static char *ft_show_time(t_file_info *file)
{
	char		*file_time;

	file_time = ctime(&(file->ftime)) + 4;
	return (file_time);
}

int ft_display_list(t_file_info *file, t_dir_info *dir_info, char *buf, size_t offset)
{
	/* char		link_buf[NAME_MAX + 1]; */

	ft_fill_permissions(buf + offset, file->mode, file->rel_path);
	offset += 12;
	ft_memset(buf + offset, ' ', dir_info->links_max_len - file->nlink_len);
	offset += dir_info->links_max_len - file->nlink_len;
	ft_memmove(buf + offset, file->st_nlink, file->nlink_len);
	offset += file->nlink_len;
	buf[offset++] = ' ';
	ft_memset(buf + offset, ' ', dir_info->u_name_max_len - file->u_name_len);
	offset += dir_info->u_name_max_len - file->u_name_len;
	ft_memmove(buf + offset, file->u_name, file->u_name_len);
	offset += file->u_name_len;
	buf[offset++] = ' ';
	buf[offset++] = ' ';
	ft_memset(buf + offset, ' ', dir_info->g_name_max_len - file->g_name_len);
	offset += dir_info->g_name_max_len - file->g_name_len;
	ft_memmove(buf + offset, file->g_name, file->g_name_len);
	offset += file->g_name_len;
	buf[offset++] = ' ';
	buf[offset++] = ' ';
	ft_memset(buf + offset, ' ', dir_info->size_max_len - file->size_len);
	offset += dir_info->size_max_len - file->size_len;
	ft_memmove(buf + offset, file->str_size, file->size_len);
	offset += file->size_len;
	buf[offset++] = ' ';
	ft_memmove(buf + offset, ft_show_time(file), 12);
	offset += 12;
	buf[offset++] = ' ';
	ft_memmove(buf + offset, file->name, file->file_len);
	offset += file->file_len;
	buf[offset++] = '\n';
	return (offset);
	/* if (rights[0] != 'b' && rights[0] != 'c') */
	/* 	printf("%s ", file->str_size); */
	/* else */
	/* { */
	/* 	printf(" %s,   ", file->major); */
	/* 	printf("%s ", file->minor); */
	/* } */
	/* if (rights[0] != 'l') */
	/* { */
	/* 	printf("%s", file->name); */
	/* 	fflush(stdout); */
	/* } */
	/* else */
	/* { */
	/* 	ft_memset(link_buf, 0, NAME_MAX + 1); */
	/* 	readlink(file->full_path, link_buf, NAME_MAX); */
	/* 	printf("%s -> %s", file->name, buf); */
	/* 	fflush(stdout); */
	/* } */
	return (1);
}
