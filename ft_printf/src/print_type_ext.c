/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 03:04:54 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 19:33:49 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*format_expo(int count)
{
	char	*expo;
	char	*zero;
	char	*digit;
	int		sign;

	sign = ft_checknegative(count);
	expo = ft_strnew(2);
	expo[0] = 'E';
	expo[1] = (sign ? '-' : '+');
	sign = (sign ? -count : count);
	digit = ft_itoa(sign, 10);
	if (sign < 10)
	{
		zero = ft_strjoin("0", digit);
		free(digit);
		digit = ft_strdup(zero);
		free(zero);
	}
	zero = ft_strjoin(expo, digit);
	free(expo);
	free(digit);
	return (zero);
}

static char	*check_e(long double dec, t_param *arg)
{
	int			count;
	char		*doub;
	char		*expo;
	char		*merg;

	count = 0;
	count_dec(&dec, &count);
	doub = ft_dtoa(dec, arg);
	expo = format_expo(count);
	merg = ft_strjoin(doub, expo);
	free(doub);
	free(expo);
	return (merg);
}

char		*print_f_e(t_param *arg, va_list ap)
{
	char		*st_int;
	char		*returner;
	long double	dec;

	if (arg->length == 0 || arg->length == 3)
		dec = va_arg(ap, double);
	else if (arg->length == 5)
		dec = va_arg(ap, long double);
	else
		dec = 0;
	if (arg->type == 'f' || arg->type == 'F')
		st_int = ft_dtoa(dec, arg);
	else if (arg->type == 'e' || arg->type == 'E')
		st_int = check_e(dec, arg);
	else
		return (NULL);
	if (arg->type == 'f' || arg->type == 'e')
		ft_tolower(st_int);
	returner = ft_strdup(st_int);
	free(st_int);
	return (returner);
}

char		*print_s(t_param *arg, va_list ap)
{
	wchar_t	*wstr;
	char	*store_str;
	char	*tmp;

	if (arg->length == 3)
	{
		if (!(wstr = va_arg(ap, wchar_t*)))
			tmp = ft_strdup("(null)");
		else
			tmp = ft_wstrdup(wstr);
	}
	else
	{
		if (!(store_str = va_arg(ap, char*)))
			tmp = ft_strdup("(null)");
		else
			tmp = ft_strdup(store_str);
	}
	return (tmp);
}

char		*print_c(t_param *arg, va_list ap)
{
	char	*store_str;

	if (arg->type == 'c' || arg->type == '%')
	{
		if (!(store_str = malloc(sizeof(char) * 2)))
			return (NULL);
		if (arg->type == '%')
			store_str[0] = '%';
		else if (arg->length == 3)
			store_str[0] = va_arg(ap, wchar_t);
		else
			store_str[0] = va_arg(ap, int);
		store_str[1] = '\0';
	}
	else
		return (NULL);
	return (store_str);
}
