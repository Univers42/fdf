/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randoms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:20:30 by dlesieur          #+#    #+#             */
/*   Updated: 2025/09/01 13:17:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_stdlib.h"

static int	lcg_rand(void)
{
	t_rng_state	*state;

	state = get_rng_state();
	state->seed_lcg = (state->seed_lcg * 1103515245 + 12345) & 0x7fffffff;
	return ((int)(state->seed_lcg % RAND_MAX));
}

static int	middle_square_rand(void)
{
	t_rng_state		*state;
	unsigned long	x;

	state = get_rng_state();
	x = state->seed_middle;
	x = x * x;
	x = (x / 100) % 10000;
	if (x == 0)
		x = 1234;
	state->seed_middle = x;
	return ((int)(x % RAND_MAX));
}

static int	xorshift_rand(void)
{
	t_rng_state		*state;
	unsigned long	x;

	state = get_rng_state();
	x = state->seed_xorshift;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	state->seed_xorshift = x;
	return ((int)(x % RAND_MAX));
}

int	ft_rand(void)
{
	t_rng_state	*state;

	state = get_rng_state();
	if (state->current_type == RNG_LCG)
		return (lcg_rand());
	else if (state->current_type == RNG_MIDDLE_SQUARE)
		return (middle_square_rand());
	else if (state->current_type == RNG_XORSHIFT)
		return (xorshift_rand());
	else
		return (lcg_rand());
}

//int main() {
//    printf("CUSTOM RANDOM NUMBER GENERATOR TEST SUITE\n");
//    printf("RAND_MAX = %d\n", RAND_MAX);
//    printf("Available algorithms: LCG, XORSHIFT, MIDDLE_SQUARE\n");
//    
//    test_basic_functionality();
//    test_different_seeds();
//    test_distribution();
//    test_range_limits();
//    test_periodicity();
//    test_seed_sensitivity();
//    
//    print_separator("FINAL EXPECTATIONS SUMMARY");
//    printf("✅ SHOULD WORK PERFECTLY:\n");
//    printf("   - Same algorithm + same seed = identical sequences\n");
//    printf("   - Different algorithms + same seed = different sequences\n");
//    printf("   - LCG: Excellent distribution (8-10/10 buckets good)\n");
//    printf("   - XORSHIFT: Excellent distribution (8-10/10 buckets good)\n");
//    printf("   - All values in range [0, %d]\n", RAND_MAX);
//    printf("   - No short periods detected\n");
//    printf("   - Close seeds produce very different outputs\n\n");
//    
//    printf("⚠️  EXPECTED LIMITATIONS:\n");
//    printf("   - MIDDLE_SQUARE: Fair distribution (4-7/10 buckets good)\n");
//    printf("   - MIDDLE_SQUARE: May show some patterns\n\n");
//    
//    printf("🚨 RED FLAGS (contact if you see these):\n");
//    printf("   - Same seed giving different sequences\n");
//    printf("   - Values outside [0, %d] range\n", RAND_MAX);
//    printf("   - Period of length 1-10 detected\n");
//    printf("   - LCG or XORSHIFT with < 6/10 good buckets\n");
//    
//    return 0;
//}

//int main(void)
//{
//    ft_srand(1, RNG_LCG);
//    printf("%d\n", ft_rand());
//}