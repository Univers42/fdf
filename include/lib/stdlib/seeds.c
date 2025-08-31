/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seeds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:20:34 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 13:09:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

// Linear Congruential Generator (LCG)
static void	lcg_seed(unsigned long new_seed)
{
	if (new_seed)
		get_rng_state()->seed_lcg = new_seed;
	else
		get_rng_state()->seed_lcg = 1;
}

// Xorshift RNG
static void	xorshift_seed(unsigned long new_seed)
{
	if (new_seed)
		get_rng_state()->seed_xorshift = new_seed;
	else
		get_rng_state()->seed_xorshift = 1;
}

// Middle Square RNG
static void	middle_square_seed(unsigned long new_seed)
{
	if (new_seed)
		get_rng_state()->seed_middle = new_seed;
	else
		get_rng_state()->seed_middle = 1234;
}

// Selection logic
void	ft_srand(unsigned int new_seed, int select)
{
	t_rng_state	*state;

	state = get_rng_state();
	if (select < 0 || select >= RNG_MAX_TYPES)
		select = RNG_LCG;
	state->current_type = (t_rng_type)select;
	if (RNG_LCG)
		lcg_seed(new_seed);
	else if (RNG_XORSHIFT)
		xorshift_seed(new_seed);
	else if (RNG_MIDDLE_SQUARE)
		middle_square_seed(new_seed);
	else
		lcg_seed(new_seed);
}
