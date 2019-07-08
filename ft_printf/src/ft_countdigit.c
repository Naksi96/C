/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:38:20 by doyang            #+#    #+#             */
/*   Updated: 2019/02/24 19:02:30 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_countdigit(unsigned long long nbr, unsigned int base)
{
	int					count;
	unsigned long long	digit;

	count = 1;
	digit = nbr;
	while (digit >= base)
	{
		digit /= base;
		count++;
	}
	return (count);
}
