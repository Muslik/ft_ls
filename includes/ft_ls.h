/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:47:31 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/18 19:40:28 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define ARR_SIZE 10
# define A 1.5

# include "libft.h"

#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

# define LS_A	1
# define LS_L	2
# define LS_RR	4
# define LS_R	8
# define LS_T	16
# define LS_F	32
# define LS_G	64
# define LS_ONE 128
# define LS_SS	256
# define LS_S	512

typedef	struct	s_ft_merge_info_ft_ls
{
	size_t		*to_sort;
	size_t		*buf;
	int			(*cmp)(void *data1, void *data2);
}				t_ft_merge_info_ft_ls;

/*
** blkcnt_t     - block size
** mode_t       - file permissions
** nlink_t      - number of hard links
** uid_t        - owner name
** gid_t        - owner group
** off_t        - file size
** dev_t        - device type
** time_t       - last modification time
** long         - time and long ntime
** char *name   - file name
*/

typedef struct	s_file_info
{
	blkcnt_t			st_blocks;
	mode_t				mode;
	nlink_t				st_nlink;
	uid_t				st_uid;
	gid_t				st_gid;
	off_t				st_size;
	dev_t				st_rdev;
	time_t				ftime;
	long				ntime;
	char				*name;
	char				full_path[PATH_MAX];
	size_t				file_len;
}				t_file_info;

/*
 ** VECTORS
*/

int		ft_vector_to_array(void **ft_vector);
void	*ft_vector_create(size_t elem_byte_size);
int		ft_vector_push_back(void **ft_vector, const void *data);
void	ft_vector_free(void **ft_vector);
long double	ft_ceill(long double x);
long double	ft_floorl(long double x);
void	*ft_vector_get_elem_n(void *ft_vector, size_t nbr);
void	*ft_vector_get_last_elem(void *ft_vector);
void	*ft_vector_get_first_elem(void *ft_vector);
size_t	ft_vector_get_len(void *ft_vector);

void	ft_open_dirs(char *str, int *flags);
void	ft_rec_dirs(size_t len, size_t **vector, char *str, int *flags);

/*
 ** FLAGS PARSER
*/

int		ft_get_flags(int argc, char **argv, int *flags);
void	ft_handle_errors(char *str, int err);

/*
 **
*/
void	print_files(size_t *vector, size_t len, int *flags);
void	ft_rec_dirs(size_t len, size_t **vector, char *str, int *flags);
#endif
