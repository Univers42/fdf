/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_background_system.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:13:51 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 13:14:37 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

/* table of background applicators wrapped in a singleton-style accessor */
static void	(**bg_apply_tbl(void))(uint32_t *buf)
{
	static void	(*tbl[DYNAMIC_BG_COUNT])(uint32_t *buf) = {
		NULL, /* DYNAMIC_BG_STATIC */
		apply_vibrant_gradient_bg,
		apply_dramatic_clouds_bg,
		apply_epileptic_flash_bg,
		apply_water_ripples_bg,
		apply_fire_plasma_bg,
		apply_matrix_rain_bg,
		apply_aurora_waves_bg,
		apply_cosmic_nebula_bg,
		apply_electric_storm_bg,
		apply_liquid_metal_bg,
		apply_rainbow_vortex_bg,
		apply_black_hole_bg
	};

	return (tbl);
}

static void	db_apply_current(t_dynamic_bg_system *db)
{
	void	(**tbl)(uint32_t *buf);
	int		idx;

	tbl = bg_apply_tbl();
	idx = (int)db->current_bg;
	if (idx > (int)DYNAMIC_BG_STATIC && idx < (int)DYNAMIC_BG_COUNT
		&& tbl[idx] != NULL)
		tbl[idx](db->bg_buffer);
}

/*
 * The black hole writes a complete frame each time, so it renders
 * straight into the framebuffer; the other modes keep their persistent
 * bg_buffer (e.g. matrix rain accumulates) and get memcpy'd over.
 */
void	dynamic_background_update(t_app *fdf)
{
	t_dynamic_bg_system	*db;

	db = gdynbg(NULL);
	if (db->current_bg == DYNAMIC_BG_STATIC)
		return ;
	if (!db->initialized)
	{
		db->bg_buffer = (uint32_t *)malloc(sizeof(uint32_t) * BG_W * BG_H);
		if (!db->bg_buffer)
			return ;
		ft_memset(db->bg_buffer, 0, sizeof(uint32_t) * BG_W * BG_H);
		db->initialized = true;
	}
	db->time_accumulator += WAVE_FREQUENCY * db->animation_speed;
	db->frame_counter++;
	if (db->current_bg == DYNAMIC_BG_BLACK_HOLE)
		return ((void)apply_black_hole_bg((uint32_t *)fdf->renderer.data));
	db_apply_current(db);
	bg_upscale(db->bg_buffer, (uint32_t *)fdf->renderer.data);
}

void	dynamic_background_toggle(void)
{
	t_dynamic_bg_system	*db;
	t_dynamic_bg_type	next;
	const char			*names[DYNAMIC_BG_COUNT];

	db = gdynbg(NULL);
	next = (db->current_bg + 1) % DYNAMIC_BG_COUNT;
	db->current_bg = next;
	db->time_accumulator = 0.0f;
	db->frame_counter = 0;
	names[0] = "Static";
	names[1] = "Vibrant";
	names[2] = "Clouds";
	names[3] = "Flash";
	names[4] = "Water";
	names[5] = "Fire";
	names[6] = "Matrix";
	names[7] = "Aurora";
	names[8] = "Nebula";
	names[9] = "Storm";
	names[10] = "Metal";
	names[11] = "Vortex";
	names[12] = "Black Hole";
	ft_printf("Dynamic Background: %s\n", names[next]);
	if (next == DYNAMIC_BG_EPILEPTIC_FLASH)
		ft_printf("Warning: Epileptic flash mode\n");
}

void	dynamic_background_cleanup(void)
{
	t_dynamic_bg_system	*db;

	db = gdynbg(NULL);
	black_hole_free();
	if (db->bg_buffer)
	{
		free(db->bg_buffer);
		db->bg_buffer = NULL;
	}
	db->initialized = false;
	db->current_bg = DYNAMIC_BG_STATIC;
	db->time_accumulator = 0.0f;
	db->frame_counter = 0;
}
