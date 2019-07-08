/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_etc_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 12:01:14 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 22:21:43 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	size_adj(char *str, t_param *arg)
{
	int	i;

	i = 0;
	if (arg->flag.hash)
	{
		if ((arg->type == 'x' || arg->type == 'X')
			&& ft_strcmp(get_hash(arg, str), ""))
			i += 2;
		else if ((arg->type == 'e' || arg->type == 'E' || arg->type == 'f')
				&& !dup_check(str, '.'))
			i++;
		else if (arg->type == 'o' && ft_strcmp(get_hash(arg, str), ""))
			i++;
	}
	if ((arg->flag.space && arg->type != 'p') || arg->flag.positive || arg->neg)
		i++;
	if (arg->flag.positive && (arg->type == 'u' || arg->type == 'o'
		|| arg->type == 's' || arg->type == 'c' || arg->type == 'x'
		|| arg->type == 'X' || arg->type == 'p'))
		i--;
	if (arg->type == 'c' && arg->nulcheck)
		i++;
	if (arg->type == 'p')
		i += 2;
	return (i);
}

static char	*handle_fill(char *str, t_param *arg)
{
	char	*filler;
	int		wid_mod;

	wid_mod = arg->width - size_adj(str, arg);
	if ((int)ft_strlen(str) < wid_mod)
	{
		filler = ft_strnew(wid_mod - (int)ft_strlen(str));
		if (arg->flag.zero && !(arg->flag.negative)
			&& (arg->precision == -1 || arg->precision == -2))
			ft_memset(filler, '0', wid_mod - (int)ft_strlen(str));
		else
			ft_memset(filler, ' ', wid_mod - (int)ft_strlen(str));
	}
	else
		filler = ft_strdup("");
	return (filler);
}

static char	*handle_hash_e(t_param *arg, char *str)
{
	int		i;
	int		j;
	char	*hashed;
	int		len;

	i = 0;
	j = 0;
	ERR_CHECK(str);
	len = ft_strlen(str) + 1;
	ERR_CHECK((hashed = ft_strnew(len)));
	while (i < len && str[j])
	{
		if (str[j] == arg->type)
		{
			hashed[i] = '.';
			hashed[++i] = str[j];
		}
		else
			hashed[i] = str[j];
		i++;
		j++;
	}
	return (hashed);
}

static char	*handle_hash(t_param *arg, char *filler, char *str)
{
	if (arg->flag.zero && !(arg->flag.negative))
	{
		if ((arg->flag.hash && arg->type != 'f' && arg->type != 'e'
			&& arg->type != 'E' && *filler != ' ') || arg->type == 'p')
			return (ft_strjoin(get_hash(arg, str), filler));
		else if ((arg->flag.hash && arg->type != 'f' && arg->type != 'e'
			&& arg->type != 'E' && *filler == ' '))
			return (ft_strjoin(filler, get_hash(arg, str)));
		else
			return (ft_strdup(filler));
	}
	else if (arg->type == 'f' && !dup_check(str, '.'))
	{
		return ((arg->flag.hash) ? ft_strjoin(str, get_hash(arg, str))
			: ft_strdup(str));
	}
	else if ((arg->type == 'e' || arg->type == 'E') && !dup_check(str, '.'))
		return (handle_hash_e(arg, str));
	else
	{
		if ((arg->flag.hash) || arg->type == 'p')
			return (ft_strjoin(get_hash(arg, str), str));
		else
			return (ft_strdup(str));
	}
}

char		*handle_flag(char *str, t_param *arg)
{
	char	*flagged;
	char	*filler;
	char	*tmp;

	filler = handle_fill(str, arg);
	if (arg->flag.zero && !(arg->flag.negative))
	{
		tmp = handle_hash(arg, filler, str);
		flagged = (*filler == ' ') ? ft_strjoin(tmp, get_sign(arg))
					: ft_strjoin(get_sign(arg), tmp);
		free(tmp);
		tmp = ft_strjoin(flagged, str);
	}
	else
	{
		tmp = handle_hash(arg, filler, str);
		flagged = ft_strjoin(get_sign(arg), tmp);
		free(tmp);
		tmp = (arg->flag.negative) ? ft_strjoin(flagged, filler)
				: ft_strjoin(filler, flagged);
	}
	free(flagged);
	free(filler);
	return (tmp);
}
