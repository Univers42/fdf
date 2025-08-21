/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:29:15 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/04 16:36:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel.h"

//int	limits(t_point *points, int len)
//{
//	int	i;
//	int	margin = FIT_MARGIN;
//
//	i = 0;
//	while (i < len)
//	{
//		if (points[i].paint)
//		{
//			if (points[i].axis[X] < MENU_WIDTH + margin || 
//				points[i].axis[X] > WINX - margin ||
//				points[i].axis[Y] < margin || 
//				points[i].axis[Y] > WINY - margin)
//				return (0);
//		}
//		i++;
//	}
//	return (1);
//}
//