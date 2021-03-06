/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:52:43 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/26 22:52:44 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_select.h"

int		ft_error(char *str)
{
	if (!ft_strcmp(str, "USAGE"))
		ft_putstr_fd("usage: ./ft_select files\n", 2);
	if (!ft_strcmp(str, "SPACE"))
		ft_putstr_fd("Not enough space\n", 2);
	return (0);
}
