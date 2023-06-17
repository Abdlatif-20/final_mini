/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 22:34:50 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/05 21:55:46 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_src;

	i = 0;
	j = 0;
	len_src = ft_strlen(src);
	if (size != 0)
	{
		while (src[i] && i < size - 1)
			dst[j++] = src[i++];
		dst[j] = '\0';
		i = 0;
	}
	return (len_src);
}
