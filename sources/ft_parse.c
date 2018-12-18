/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:39:24 by dmorgil           #+#    #+#             */
/*   Updated: 2018/12/18 19:31:25 by dmorgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int ft_strchr_by_index(char *str, int c)
{
	int j;

	j = 0;
	while (str[j])
	{
		if (str[j] == c)
			return (j);
		j++;
	}
	return (-1);
}

void	ft_handle_errors(char *str, int err)
{
	err = 0;
	printf("ERROR:\n");
	ft_putstr_fd("./ft_ls: illegal option -- ", 2);
	ft_putchar_fd(*str, 2);
	ft_putstr_fd("\nusage: ls [-aflRrtG1Ss] [file ...]", 2);
}

static int	ft_add_flags(int *flags, char *str)
{
	int bit;

	while (*(++str))
	{
		if ((bit = ft_strchr_by_index("aflRrtG1Ss", *str)) == -1)
			ft_handle_errors(str, 0);
		*flags |= (1 << bit);
		if ((*str == 'l') || (*str == '1'))
			*flags &= (*str == 'l') ? ~LS_ONE : ~LS_L;
	}
	return (1);
}

int		ft_get_flags(int argc, char **argv, int *flags)
{
	int i;

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		if(!ft_add_flags(flags, argv[i]))
			return (-1);
		i++;
	}
	return (i);
}

