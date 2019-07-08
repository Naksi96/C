/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doyang <doyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 23:21:49 by doyang            #+#    #+#             */
/*   Updated: 2019/02/22 00:58:52 by doyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char *ccat;

	if (!s1 || !s2)
		return (NULL);
	ccat = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!ccat)
		return (NULL);
	ft_strcpy(ccat, s1);
	ft_strcat(ccat, s2);
	return (ccat);
}
