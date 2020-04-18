/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strdup.c                                     /       \.'`  `',.--//   */
/*                                                    +:+ +:+         +:+     */
/*   By: adandres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:01:03 by adandres          #+#    #+#             */
/*   Updated: 2020/04/09 23:16:08 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"
#include "stdio.h"

char	*my_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*cpy;

	i = 0;
	len = my_strlen(s1);
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (cpy == NULL)
		return (NULL);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
