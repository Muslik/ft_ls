/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:47:31 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/12 20:46:23 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_LS
# define FT_LS
# define ARR_SIZE 10
# define A 1.5

#include "libft.h"

typedef	struct	s_flags
{
	char		l;
	char		R;
	char		a;
	char		r;
	char		t;
	char		u;
	char		f;
	char		g;
	char		d;
}				t_flags;

typedef struct	s_help
{
	char		*str;
}				t_help;

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
#endif
