/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 17:23:33 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/25 17:43:04 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_get_file_type(int mode)
{
	char		filetype;

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

char	ft_get_file_acl(char *path)
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

char *ft_show_time(t_file_info *file)
{
	char		*file_time;

	file_time = ctime(&(file->ftime)) + 4;
	return (file_time);
}
