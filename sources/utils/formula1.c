/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 08:33:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/09/01 08:44:58 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * @brief Converts NDC X coordinate to screen X pixel.
 *
 * @param ndc_x The NDC X value.
 * @return The screen X pixel coordinate.
 */
int	ndc_to_screen_x(float ndc_x)
{
	return ((int)((ndc_x + NDC_SHIFT) / NDC_SCALE * gviewport()->w));
}

/**
 * @brief Converts NDC Y coordinate to screen Y pixel.
 *
 * @param ndc_y The NDC Y value.
 * @return The screen Y pixel coordinate.
 */
int	ndc_to_screen_y(float ndc_y)
{
	return ((int)((1 - ndc_y) / NDC_SCALE * gviewport()->h));
}

/**
 * @brief Converts NDC Z coordinate to depth value.
 *
 * @param ndc_z The NDC Z value.
 * @return The depth value clamped to [DEPTH_MIN, DEPTH_MAX].
 */
int	ndc_to_depth(float ndc_z)
{
	return ((int)fminf(fmaxf(((ndc_z + NDC_SHIFT) / NDC_SCALE * DEPTH_SCALE)
				+ DEPTH_OFFSET, DEPTH_MIN), DEPTH_MAX));
}
