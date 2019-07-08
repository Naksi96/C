/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 07:32:24 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 22:18:08 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		check_flag(t_param *arg)
{
	while ((arg->str)[arg->pos] == '-' || (arg->str)[arg->pos] == '+'
		|| (arg->str)[arg->pos] == ' ' || (arg->str)[arg->pos] == '#'
		|| (arg->str)[arg->pos] == '0' || (arg->str)[arg->pos] == '\'')
	{
		if ((arg->str)[arg->pos] == '-')
			arg->flag.negative = 1;
		if ((arg->str)[arg->pos] == '+')
			arg->flag.positive = 1;
		if ((arg->str)[arg->pos] == ' ')
			arg->flag.space = 1;
		if ((arg->str)[arg->pos] == '#')
			arg->flag.hash = 1;
		if ((arg->str)[arg->pos] == '0')
			arg->flag.zero = 1;
		arg->pos++;
	}
}

void		check_width(t_param *arg, va_list ap)
{
	if (ft_isdigit((arg->str)[arg->pos]) || (arg->str)[arg->pos] == '*')
	{
		if ((arg->str)[arg->pos] == '*')
		{
			arg->width = va_arg(ap, int);
			arg->pos++;
		}
		else
		{
			arg->width = ft_atoi(&((arg->str)[arg->pos]));
			arg->pos += ft_countdigit(arg->width, 10);
		}
		if (ft_checknegative(arg->width))
		{
			arg->width = -(arg->width);
			arg->flag.negative = 1;
		}
	}
}

void		check_precision(t_param *arg, va_list ap)
{
	if ((arg->str)[arg->pos] == '.')
	{
		arg->pos++;
		if ((arg->str)[arg->pos] == '*')
		{
			arg->precision = va_arg(ap, int);
			arg->pos++;
		}
		else if (!(ft_isdigit((arg->str)[arg->pos])))
		{
			arg->precision = -2;
			return ;
		}
		else
		{
			arg->precision = ft_atoi(&((arg->str)[arg->pos]));
			arg->pos += ft_countdigit(arg->precision, 10);
		}
		if (ft_checknegative(arg->precision))
			arg->precision = -1;
	}
}

static void	check_size_ext(t_param *arg)
{
	if (!ft_strncmp(&((arg->str)[arg->pos]), "L", 1))
	{
		arg->length = 5;
		arg->pos += 1;
	}
	else if (!ft_strncmp(&((arg->str)[arg->pos]), "j", 1))
	{
		arg->length = 6;
		arg->pos += 1;
	}
	else if (!ft_strncmp(&((arg->str)[arg->pos]), "z", 1))
	{
		arg->length = 7;
		arg->pos += 1;
	}
}

void		check_size(t_param *arg)
{
	if (!ft_strncmp(&((arg->str)[arg->pos]), "hh", 2))
	{
		arg->length = 1;
		arg->pos += 2;
	}
	else if (!ft_strncmp(&((arg->str)[arg->pos]), "ll", 2))
	{
		arg->length = 4;
		arg->pos += 2;
	}
	else if (!ft_strncmp(&((arg->str)[arg->pos]), "h", 1))
	{
		arg->length = 2;
		arg->pos += 1;
	}
	else if (!ft_strncmp(&((arg->str)[arg->pos]), "l", 1))
	{
		arg->length = 3;
		arg->pos += 1;
	}
	else
		check_size_ext(arg);
}
