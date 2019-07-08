/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_etc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 07:36:05 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 18:02:09 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*handle_all(t_param *arg, va_list ap)
{
	t_func	func;
	char	*str;
	char	*man_prec;
	char	*man_flag;

	func = set_function(arg->type);
	str = func(arg, ap);
	man_prec = handle_precision(str, arg);
	man_flag = handle_flag(man_prec, arg);
	if (man_prec)
		free(man_prec);
	if (str)
		free(str);
	return (man_flag);
}

static char	*handle_dixou(char *str, t_param *arg)
{
	char	*zerofill;
	char	*result;
	int		strl;

	strl = (arg->flag.hash && arg->type == 'o')
		? (ft_strlen(str) + ft_strlen(get_hash(arg, str))) : (ft_strlen(str));
	if (arg->precision > strl)
	{
		ERR_CHECK((zerofill = ft_strnew(arg->precision - strl)));
		ft_memset(zerofill, '0', arg->precision - strl);
		result = ft_strjoin(zerofill, str);
		free(zerofill);
	}
	else if ((arg->precision == -2 || arg->precision == 0)
			&& !(ft_strcmp(str, "0")))
	{
		result = ft_strdup("");
		arg->checkzz++;
	}
	else
		result = ft_strdup(str);
	return (result);
}

static char	*handle_cs(char *str, t_param *arg)
{
	char	*result;

	if (arg->type == 'c' && !str[0])
	{
		result = ft_strnew(1);
		arg->nulcheck = 1;
	}
	else if (arg->type == 's' && (arg->precision < (int)ft_strlen(str))
			&& (arg->precision >= 0 || arg->precision == -2))
	{
		result = (arg->precision != -2) ? ft_strndup(str, arg->precision)
				: ft_strdup("");
	}
	else
		result = ft_strdup(str);
	return (result);
}

char		*handle_precision(char *str, t_param *arg)
{
	char	*merge_res;

	if (arg->type == 'd' || arg->type == 'i' || arg->type == 'x'
		|| arg->type == 'X' || arg->type == 'o' || arg->type == 'u'
		|| arg->type == 'U' || arg->type == 'p')
	{
		ERR_CHECK((merge_res = handle_dixou(str, arg)));
	}
	else if (arg->type == 'c' || arg->type == 's')
	{
		ERR_CHECK((merge_res = handle_cs(str, arg)));
	}
	else
		ERR_CHECK((merge_res = ft_strdup(str)));
	return (merge_res);
}
