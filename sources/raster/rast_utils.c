/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rast_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	imin2(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	imax2(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	imin3(int a, int b, int c)
{
	return (imin2(imin2(a, b), c));
}

int	imax3(int a, int b, int c)
{
	return (imax2(imax2(a, b), c));
}
