/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zbuffer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 00:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2026/07/12 00:00:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <wchar.h>

float	*gzbuf(void)
{
	static float	*zb;

	if (!zb)
		zb = (float *)malloc(sizeof(float) * WIN_WIDTH * WIN_HEIGHT);
	return (zb);
}

/*
 * +INF bit pattern (0x7F800000) fills via the same SIMD 4-byte pattern
 * fill as the background clear: every depth test passes on first touch.
 */
void	zbuf_clear(void)
{
	float	*zb;

	zb = gzbuf();
	if (!zb)
		return ;
	wmemset((wchar_t *)zb, (wchar_t)0x7F800000,
		(size_t)WIN_WIDTH * WIN_HEIGHT);
}

void	zbuf_free(void)
{
	free(gzbuf());
}
