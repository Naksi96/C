/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 23:01:08 by doyang            #+#    #+#             */
/*   Updated: 2019/02/22 01:03:45 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcpy(char *s1, const char *s2)
{
	int i;

	i = 0;
	while ((s1[i] = s2[i]) != '\0')
		i++;
	s1[i] = '\0';
	return (s1);
}
