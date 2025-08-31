/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:43:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 13:12:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

// FIXED: Separate seeds for each algorithm to prevent interference
t_rng_state	*get_rng_state(void)
{
	static t_rng_state	state = {
		1,
		1,
		1234,
		RNG_LCG
	};

	return (&state);
}

const char	*get_algorithm_name(int type)
{
	if (type == RNG_LCG)
		return ("LCG");
	if (type == RNG_XORSHIFT)
		return ("XORSHIFT");
	if (type == RNG_MIDDLE_SQUARE)
		return ("MIDDLE_SQUARE");
	return ("UNKNOWN");
}
