/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ease-in-out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:59:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 01:38:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Ease-in-out interpolation for smoother transitions
float	ease_in_out(float t)
{
	if (t < 0.5f)
		return (2.0f * t * t);
	else
		return (-1.0f + (4.0f - 2.0f * t) * t);
}
