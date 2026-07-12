/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:53:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/29 22:53:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include "fdf.h"
#include "libft.h"

/* FDF_BG=<0..12> pre-selects a dynamic background (12 = black hole). */
static void	env_bg(void)
{
	int	m;

	if (!getenv("FDF_BG"))
		return ;
	m = atoi(getenv("FDF_BG")) % DYNAMIC_BG_COUNT;
	if (m < 0)
		m += DYNAMIC_BG_COUNT;
	gdynbg(NULL)->active = true;
	gdynbg(NULL)->current_bg = (t_dynamic_bg_type)m;
}

/* FDF_SHAPE / FDF_VIEW / FDF_CAM pre-select demo state at launch. */
static void	env_misc(void)
{
	int	m;

	if (getenv("FDF_VIEW"))
		*gviewmode() = atoi(getenv("FDF_VIEW")) % 3;
	if (getenv("FDF_CAM"))
		gcam()->active = true;
	if (getenv("FDF_PART"))
		gparticles(NULL)->current_type = (t_particle_type)(
			atoi(getenv("FDF_PART")) % PARTICLE_COUNT);
	if (!getenv("FDF_SHAPE"))
		return ;
	m = atoi(getenv("FDF_SHAPE")) % SHAPE_COUNT;
	if (m < 0)
		m += SHAPE_COUNT;
	gtransition(NULL)->active = true;
	gtransition(NULL)->target_shape = (t_shape_type)m;
}

/* FDF_FX=<1..9> pre-selects an H-key object effect at launch. */
static void	env_fx(void)
{
	int	m;

	if (!getenv("FDF_FX"))
		return ;
	m = atoi(getenv("FDF_FX")) % OBJECT_EFFECT_COUNT;
	if (m < 0)
		m += OBJECT_EFFECT_COUNT;
	gobjfx(NULL)->current_effect = (t_object_effect_type)m;
}

int	main(int argc, char **argv)
{
	int		exit_code;
	t_app	fdf;

	if (argc != 2)
		return (ft_fdprintf(STDERR_FILENO, "Usage: fdf FILE \n"),
			EXIT_FAILURE);
	env_bg();
	env_misc();
	env_fx();
	ft_memset(&fdf, 0, sizeof(t_app));
	fdf.auto_rotate = false;
	fdf.current_bg_theme = 0;
	fdf.stars_enabled = 1;
	fdf.shadow_mode = 0;
	fdf.has_color = false;
	fdf.input_state = INPUT_STATE_IDLE;
	if (make_fdf(&fdf, argv[1]))
	{
		exit_code = EXIT_SUCCESS;
		mlx_loop(fdf.mlx);
	}
	else
		exit_code = EXIT_FAILURE;
	return (fdf_destroy_contents(&fdf), exit_code);
}
