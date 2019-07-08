/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_etc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:01:41 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 20:41:31 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_hash(t_param *arg, char *str)
{
	if ((arg->type == 'x' && (dup_check(str, '0') != (int)ft_strlen(str))
		&& *str) || arg->type == 'p')
		return ("0x");
	else if (arg->type == 'X' && *str
		&& (dup_check(str, '0') != (int)ft_strlen(str)))
		return ("0X");
	else if (arg->type == 'o' && ((arg->precision == -2 || arg->precision == 0)
			|| (*str && (dup_check(str, '0') != (int)ft_strlen(str)))))
		return ("0");
	else if (arg->type == 'f' || arg->type == 'e' || arg->type == 'E')
		return (".");
	else
		return ("");
}

char	*get_sign(t_param *arg)
{
	if (arg->neg)
		return ("-");
	if (arg->flag.positive && arg->type != 'c' && arg->type != 's'
		&& arg->type != '%' && arg->type != 'u' && arg->type != 'p'
		&& arg->type != 'U' && arg->type != 'o' && arg->type != 'x'
		&& arg->type != 'X')
	{
		return ("+");
	}
	if (arg->flag.space && arg->type != 'c' && arg->type != 's'
		&& arg->type != '%' && arg->type != 'u' && arg->type != 'p'
		&& arg->type != 'U' && arg->type != 'o' && arg->type != 'x'
		&& arg->type != 'X')
	{
		return (" ");
	}
	else
		return ("");
}

int		check_base(t_param *arg)
{
	int base;

	base = 0;
	if (arg->type == 'i' || arg->type == 'd'
		|| arg->type == 'u' || arg->type == 'U')
	{
		base = 10;
	}
	else if (arg->type == 'o')
		base = 8;
	else if (arg->type == 'x' || arg->type == 'X')
		base = 16;
	return (base);
}

void	count_dec(long double *dec, int *count)
{
	long double	tmp;

	tmp = (ft_checknegative(*dec)) ? -(*dec) : (*dec);
	while ((ft_countdigit(tmp, 10) != 1) || (long long)tmp == 0)
	{
		if (tmp >= 10)
		{
			tmp /= 10;
			(*count)++;
		}
		else if ((long long)tmp == 0)
		{
			tmp *= 10;
			(*count)--;
		}
	}
	*dec = (ft_checknegative(*dec)) ? -tmp : tmp;
}
