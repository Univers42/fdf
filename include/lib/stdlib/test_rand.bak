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
