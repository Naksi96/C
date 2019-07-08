/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_call.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 02:49:07 by doyang            #+#    #+#             */
/*   Updated: 2019/03/08 16:02:18 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		dictionary(t_func *function)
{
	function['d'] = &print_d_i;
	function['i'] = &print_d_i;
	function['o'] = &print_d_i;
	function['x'] = &print_d_i;
	function['X'] = &print_d_i;
	function['u'] = &print_d_i;
	function['U'] = &print_d_i;
	function['c'] = &print_c;
	function['s'] = &print_s;
	function['%'] = &print_c;
	function['f'] = &print_f_e;
	function['F'] = &print_f_e;
	function['e'] = &print_f_e;
	function['E'] = &print_f_e;
	function['p'] = &print_p;
}

t_param			*new_param(char *format)
{
	t_param	*arc;

	ERR_CHECK((arc = ft_memalloc(sizeof(t_param))));
	arc->str = format;
	arc->pos = 0;
	param_reset(arc);
	return (arc);
}

void			param_reset(t_param *arg)
{
	arg->length = 0;
	arg->width = 0;
	arg->precision = -1;
	arg->flag.negative = 0;
	arg->flag.positive = 0;
	arg->flag.space = 0;
	arg->flag.hash = 0;
	arg->flag.zero = 0;
	arg->type = '\0';
	arg->nulcheck = 0;
	arg->checkzz = 0;
	arg->neg = 0;
	arg->special = 0;
}

int				print_param(t_param *arg, va_list ap)
{
	int		count;
	t_func	func;
	char	*strstore;

	func = set_function(arg->type);
	if (func)
		strstore = handle_all(arg, ap);
	else if (arg->width > 0)
	{
		strstore = ft_strnew(arg->width);
		ft_memset(strstore, ' ', arg->width);
		count = (arg->flag.negative) ? 0 : (arg->width - 1);
		ft_memset(strstore + count, arg->type, 1);
	}
	else
	{
		strstore = ft_strnew(1);
		ft_memset(strstore, arg->type, 1);
	}
	count = (arg->nulcheck) ? (1 + ft_strlen(strstore)) : ft_strlen(strstore);
	if (arg->flag.negative && arg->nulcheck && (arg->special = 1))
		write(1, "\0", 1);
	write(1, strstore, count - (arg->special));
	free(strstore);
	return (count);
}

t_func			set_function(char c)
{
	int				param;
	static t_func	*func;

	if (!func)
	{
		ERR_CHECK((func = ft_memalloc(sizeof(*func) * 256)));
		if (func)
			dictionary(func);
	}
	param = (int)c;
	return (func[param]);
}
