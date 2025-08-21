/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_div.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:46:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 13:47:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel.h"
/* 
*	This function iterate len points of the array and 
*	divide de z axis by divisor
*/

void	z_division(t_point *proyect, float divisor, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		proyect[i].axis[Z] = proyect[i].axis[Z] / divisor;
		i++;
	}
}
