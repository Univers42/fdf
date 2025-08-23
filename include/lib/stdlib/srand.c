/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:20:30 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/23 17:31:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#ifndef RAND_MAX
#define RAND_MAX 32767
#endif

typedef enum e_rng_type {
    RNG_LCG = 0,
    RNG_XORSHIFT,
    RNG_MIDDLE_SQUARE,
    RNG_MAX_TYPES
} t_rng_type;

typedef struct s_rng_state {
    unsigned long seed_lcg;
    unsigned long seed_xorshift;
    unsigned long seed_middle;
    t_rng_type current_type;
} t_rng_state;

// FIXED: Separate seeds for each algorithm to prevent interference
static t_rng_state *get_rng_state(void)
{
    static t_rng_state state = {1, 1, 1234, RNG_LCG};
    return &state;
}

const char *get_algorithm_name(int type) {
    switch (type) {
        case RNG_LCG: return "LCG";
        case RNG_XORSHIFT: return "XORSHIFT";  
        case RNG_MIDDLE_SQUARE: return "MIDDLE_SQUARE";
        default: return "UNKNOWN";
    }
}

// Linear Congruential Generator (LCG)
static void lcg_seed(unsigned long new_seed)
{
    get_rng_state()->seed_lcg = new_seed ? new_seed : 1;
}

static int lcg_rand(void)
{
    t_rng_state *state = get_rng_state();
    state->seed_lcg = (state->seed_lcg * 1103515245 + 12345) & 0x7fffffff;
    return (int)(state->seed_lcg % RAND_MAX);
}

// Xorshift RNG
static void xorshift_seed(unsigned long new_seed)
{
    get_rng_state()->seed_xorshift = new_seed ? new_seed : 1;
}

static int xorshift_rand(void)
{
    t_rng_state *state = get_rng_state();
    unsigned long x = state->seed_xorshift;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state->seed_xorshift = x;
    return (int)(x % RAND_MAX);
}

// Middle Square RNG
static void middle_square_seed(unsigned long new_seed)
{
    get_rng_state()->seed_middle = new_seed ? new_seed : 1234;
}

static int middle_square_rand(void)
{
    t_rng_state *state = get_rng_state();
    unsigned long x = state->seed_middle;
    x = x * x;
    x = (x / 100) % 10000;
    if (x == 0) x = 1234; // Prevent zero lock
    state->seed_middle = x;
    return (int)(x % RAND_MAX);
}

// Selection logic
void ft_srand(unsigned int new_seed, int select)
{
    t_rng_state *state = get_rng_state();
    if (select < 0 || select >= RNG_MAX_TYPES)
        select = RNG_LCG;
    
    state->current_type = (t_rng_type)select;
    
    switch (state->current_type) {
        case RNG_LCG: lcg_seed(new_seed); break;
        case RNG_XORSHIFT: xorshift_seed(new_seed); break;
        case RNG_MIDDLE_SQUARE: middle_square_seed(new_seed); break;
        default: lcg_seed(new_seed); break;
    }
}

int ft_rand(void)
{
    t_rng_state *state = get_rng_state();
    switch (state->current_type) {
        case RNG_LCG: return lcg_rand();
        case RNG_XORSHIFT: return xorshift_rand();
        case RNG_MIDDLE_SQUARE: return middle_square_rand();
        default: return lcg_rand();
    }
}

// ==============================
// TEST SUITE
// ==============================

void print_separator(const char *title) {
    printf("\n=== %s ===\n", title);
}

// FIXED: Added return type and better formatting
int loop_basic_functionality(unsigned int seed, int flag)
{
    int i = -1;
    
    printf("%s with seed %u: ", get_algorithm_name(flag), seed);
    ft_srand(seed, flag);
    
    while (++i < 10) {
        printf("%d ", ft_rand());
    }
    printf("\n");
    return 0; // Added return value
}

void test_basic_functionality(void)
{
    print_separator("BASIC FUNCTIONALITY TEST - REPRODUCIBILITY");
    
    printf("Testing that same seed produces same sequence:\n\n");
    
    // Test LCG reproducibility
    printf("=== LCG REPRODUCIBILITY TEST ===\n");
    loop_basic_functionality(42, RNG_LCG);
    loop_basic_functionality(42, RNG_LCG);
    printf("^ EXPECTED: These two lines should be IDENTICAL\n\n");
    
    // Test XORSHIFT reproducibility  
    printf("=== XORSHIFT REPRODUCIBILITY TEST ===\n");
    loop_basic_functionality(42, RNG_XORSHIFT);
    loop_basic_functionality(42, RNG_XORSHIFT);
    printf("^ EXPECTED: These two lines should be IDENTICAL\n\n");
    
    // Test MIDDLE_SQUARE reproducibility
    printf("=== MIDDLE_SQUARE REPRODUCIBILITY TEST ===\n");
    loop_basic_functionality(42, RNG_MIDDLE_SQUARE);
    loop_basic_functionality(42, RNG_MIDDLE_SQUARE);
    printf("^ EXPECTED: These two lines should be IDENTICAL\n\n");
    
    // FIXED: Proper comparison between algorithms
    printf("=== ALGORITHM DIFFERENCE TEST (Same seed, different algorithms) ===\n");
    loop_basic_functionality(42, RNG_LCG);
    loop_basic_functionality(42, RNG_XORSHIFT);
    loop_basic_functionality(42, RNG_MIDDLE_SQUARE);
    printf("^ EXPECTED: All three lines should be COMPLETELY DIFFERENT\n");
}

void test_different_seeds(void) {
    print_separator("DIFFERENT SEEDS TEST");
    
    int seeds[] = {1, 100, 12345, 999999};
    int num_seeds = sizeof(seeds) / sizeof(seeds[0]);
    
    printf("Testing LCG with different seeds:\n");
    for (int s = 0; s < num_seeds; s++) {
        loop_basic_functionality(seeds[s], RNG_LCG);
    }
    printf("^ EXPECTED: All 4 sequences should be different\n\n");
    
    printf("Testing XORSHIFT with different seeds:\n");
    for (int s = 0; s < num_seeds; s++) {
        loop_basic_functionality(seeds[s], RNG_XORSHIFT);
    }
    printf("^ EXPECTED: All 4 sequences should be different\n");
}

void test_distribution_detailed(int algorithm, const char *name) {
    int buckets[10] = {0};
    int total_samples = 10000;
    
    printf("\n--- %s Distribution Analysis ---\n", name);
    ft_srand(12345, algorithm);
    
    for (int i = 0; i < total_samples; i++) {
        int val = ft_rand() % 10;
        buckets[val]++;
    }
    
    printf("Digit distribution (%d samples):\n", total_samples);
    int good_buckets = 0;
    for (int i = 0; i < 10; i++) {
        double percentage = (buckets[i] * 100.0) / total_samples;
        printf("  %d: %d times (%.1f%%) ", i, buckets[i], percentage);
        if (percentage >= 8.0 && percentage <= 12.0) {
            printf("✓");
            good_buckets++;
        } else {
            printf("✗");
        }
        printf("\n");
    }
    
    printf("Quality Score: %d/10 buckets in acceptable range (8-12%%) - ", good_buckets);
    if (good_buckets >= 8) printf("EXCELLENT\n");
    else if (good_buckets >= 6) printf("GOOD\n");
    else if (good_buckets >= 4) printf("FAIR\n");
    else printf("POOR\n");
    
    printf("EXPECTED for %s: ", name);
    if (algorithm == RNG_LCG) printf("8-10/10 buckets good (EXCELLENT)\n");
    else if (algorithm == RNG_XORSHIFT) printf("8-10/10 buckets good (EXCELLENT)\n");
    else printf("4-7/10 buckets good (FAIR to GOOD)\n");
}

void test_distribution(void) {
    print_separator("DISTRIBUTION TEST (0-9 range)");
    
    test_distribution_detailed(RNG_LCG, "LCG");
    test_distribution_detailed(RNG_XORSHIFT, "XORSHIFT");
    test_distribution_detailed(RNG_MIDDLE_SQUARE, "MIDDLE_SQUARE");
}

void test_range_limits(void) {
    print_separator("RANGE AND LIMITS TEST");
    
    int algorithms[] = {RNG_LCG, RNG_XORSHIFT, RNG_MIDDLE_SQUARE};
    const char *names[] = {"LCG", "XORSHIFT", "MIDDLE_SQUARE"};
    
    for (int alg = 0; alg < 3; alg++) {
        ft_srand(777, algorithms[alg]);
        int min_val = RAND_MAX;
        int max_val = 0;
        int samples = 1000;
        int errors = 0;
        
        printf("\n%s Range Test (%d samples):\n", names[alg], samples);
        
        for (int i = 0; i < samples; i++) {
            int val = ft_rand();
            if (val < min_val) min_val = val;
            if (val > max_val) max_val = val;
            if (val < 0 || val > RAND_MAX) {
                printf("ERROR: Value %d out of range [0, %d]\n", val, RAND_MAX);
                errors++;
            }
        }
        
        printf("  Range found: [%d, %d]\n", min_val, max_val);
        printf("  Expected: [0, %d]\n", RAND_MAX);
        printf("  Coverage: %.1f%% of total range\n", ((max_val - min_val) * 100.0) / RAND_MAX);
        printf("  Errors: %d\n", errors);
        printf("  EXPECTED: 0 errors, coverage > 50%%\n");
    }
}

void test_periodicity(void) {
    print_separator("PERIODICITY TEST");
    
    printf("Testing LCG for short periods (bad sign if found):\n");
    ft_srand(1, RNG_LCG);
    
    int period_test[100];
    for (int i = 0; i < 100; i++) {
        period_test[i] = ft_rand();
    }
    
    // Check for very short periods
    int period_found = 0;
    for (int period_len = 1; period_len <= 10 && !period_found; period_len++) {
        int is_periodic = 1;
        for (int i = period_len; i < 50; i++) {
            if (period_test[i] != period_test[i - period_len]) {
                is_periodic = 0;
                break;
            }
        }
        if (is_periodic) {
            printf("WARNING: Detected period of length %d (VERY BAD!)\n", period_len);
            period_found = 1;
        }
    }
    
    if (!period_found) {
        printf("✓ No short periods detected (good sign)\n");
    }
    
    printf("EXPECTED: No short periods should be detected\n");
}

void test_seed_sensitivity(void) {
    print_separator("SEED SENSITIVITY TEST");
    
    printf("Testing how different close seeds produce different outputs:\n");
    
    const char *names[] = {"LCG", "XORSHIFT", "MIDDLE_SQUARE"};
    int algorithms[] = {RNG_LCG, RNG_XORSHIFT, RNG_MIDDLE_SQUARE};
    
    for (int alg = 0; alg < 3; alg++) {
        printf("\n%s sensitivity:\n", names[alg]);
        
        int base_seed = 1000;
        ft_srand(base_seed, algorithms[alg]);
        int base_first = ft_rand();
        
        printf("  Seed %d -> %d\n", base_seed, base_first);
        
        for (int offset = 1; offset <= 3; offset++) {
            ft_srand(base_seed + offset, algorithms[alg]);
            int test_first = ft_rand();
            int diff = test_first > base_first ? test_first - base_first : base_first - test_first;
            printf("  Seed %d -> %d (diff: %d)\n", base_seed + offset, test_first, diff);
        }
        
        printf("  EXPECTED: All outputs should be significantly different\n");
    }
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