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

static char ft_get_file_acl(char path[PATH_MAX])
{
	ssize_t		xattr;
	acl_entry_t dummy;
	acl_t		acl;
	char		sym;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
        acl_free(acl);
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	return (sym = (xattr > 0) ? '@' : ' ');
	return (sym = (acl != NULL) ? '+' : sym);
}

static void	ft_display_permissions(char rights[12], int mode, char path[PATH_MAX])
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
	rights[11] = '\0';
	if (mode & S_ISUID)
		rights[3] = ('x' == rights[3] ? 's' : 'S');
	if (mode & S_ISGID)
		rights[6] = ('x' == rights[6] ? 's' : 'S');
	if (mode & S_ISVTX)
		rights[9] = ('x' == rights[9] ? 't' : 'T');
	ft_putstr(rights);
}

static void ft_show_time(t_file_info *file)
{
	char		*file_time;

	file_time = ctime(&(file->ftime)) + 4;
	write(1, file_time, 12);
	write(1, " ", 1);
}

int ft_display_list(t_file_info *file)
{
	char		rights[12];
	char		buf[NAME_MAX + 1];

	(flags & LS_SS) ? printf("%zd", file->st_blocks) : 0;
	ft_display_permissions(rights, file->mode, file->full_path);
	printf("%zd ", file->st_nlink);
	fflush(stdout);
	printf("%s  ", (getpwuid(file->st_uid))->pw_name);
	fflush(stdout);
	printf("%s  ", (getgrgid(file->st_gid))->gr_name);
	fflush(stdout);
	if (rights[0] != 'b' && rights[0] != 'c')
		printf("%zd ", file->st_size);
	else
	{
		printf(" %zd,   ", major(file->st_rdev));
		printf("%zd ", minor(file->st_rdev));
	}
	fflush(stdout);
	ft_show_time(file);
	if (rights[0] != 'l')
	{
		printf("%s", file->name);
		fflush(stdout);
	}
	else
	{
		ft_bzero(buf, NAME_MAX + 1);
		readlink(file->full_path, buf, NAME_MAX);
		printf("%s -> %s", file->name, buf);
		fflush(stdout);
	}
	return (1);
}
