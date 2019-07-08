/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:36:16 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 22:21:00 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		check_conversion(t_param *arg, va_list ap)
{
	arg->pos++;
	while ((arg->str)[arg->pos] && (ft_isdigit((arg->str)[arg->pos])
			|| dup_check("-+ #0*.lhLjz'", (arg->str)[arg->pos])))
	{
		if ((arg->str)[arg->pos])
			check_flag(arg);
		if ((arg->str)[arg->pos])
			check_width(arg, ap);
		if ((arg->str)[arg->pos])
			check_precision(arg, ap);
		if ((arg->str)[arg->pos])
			check_size(arg);
		if ((arg->str)[arg->pos] == '%')
			break ;
	}
	if ((arg->str)[arg->pos])
		arg->type = (arg->str)[arg->pos];
	if ((arg->str)[arg->pos])
		arg->pos++;
}

void		mem_free(t_param **arg)
{
	ft_memdel((void **)arg);
}

int			ft_printf(char *format, ...)
{
	va_list	ap;
	t_param	*arg;
	int		count;

	va_start(ap, format);
	arg = new_param(format);
	count = 0;
	while (arg->str[arg->pos])
	{
		while ((arg->str)[arg->pos] != '%' && (arg->str)[arg->pos])
		{
			ft_putchar((arg->str)[arg->pos]);
			arg->pos++;
			count++;
		}
		if ((arg->str)[arg->pos] == '%')
		{
			check_conversion(arg, ap);
			count = (arg->type) ? (count + print_param(arg, ap)) : (count + 0);
			param_reset(arg);
		}
	}
	va_end(ap);
	mem_free(&arg);
	return (count);
}
