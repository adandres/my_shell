/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strequ.c                                     /       \.'`  `',.--//   */
/*                                                    +:+ +:+         +:+     */
/*   By: adandres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 13:22:36 by adandres          #+#    #+#             */
/*   Updated: 2020/03/17 13:17:32 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

#include "my_str.h"

int		my_strequ(char const *s1, char const *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (my_strcmp(s1, s2) == 0)
		return (1);
	else
		return (0);
}
