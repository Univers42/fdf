#include "window.h"
#include "atom_demo.c"
#include "object.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "ft_math.h" // <-- Explicitly include ft_math.h here for M_PI

// Simple animation state
typedef struct s_animation
{
    float time;
    int frame_count;
    t_window *window;
} t_animation;

void test_color_patterns(t_window *window)
{
    printf("Testing color patterns...\n");

    // Draw color gradient
    for (int x = 0; x < 256 && x < window->width; x++)
    {
        for (int y = 0; y < 256 && y < window->height; y++)
        {
            int color = (x << 16) | (y << 8) | ((x + y) / 2);
            window_put_pixel(window, x + 10, y + 10, color);
        }
    }
}

void test_animation_frame(t_animation *anim)
{
    t_window *window = anim->window;

    // Ensure M_PI is available
    double pi = M_PI;
    (void)pi; // Prevent unused variable warning if not used

    // Clear with animated background color
    int bg_r = (int)(127 + 127 * sin(anim->time * 0.5));
    int bg_g = (int)(127 + 127 * sin(anim->time * 0.3));
    int bg_b = (int)(127 + 127 * sin(anim->time * 0.7));
    int bg_color = (bg_r << 16) | (bg_g << 8) | bg_b;

    window_set_background(window, bg_color);
    window_clear(window);

    // Draw animated shapes
    int center_x = window->width / 2;
    int center_y = window->height / 2;

    // Rotating lines
    for (int i = 0; i < 8; i++)
    {
        float angle = anim->time + (i * M_PI / 4);
        int x1 = center_x + (int)(50 * cos(angle));
        int y1 = center_y + (int)(50 * sin(angle));
        int x2 = center_x + (int)(100 * cos(angle));
        int y2 = center_y + (int)(100 * sin(angle));

        int color = 0xFFFFFF - (i * 0x202020);
        window_draw_line_simple(window, x1, y1, x2, y2, color);
    }

    // Bouncing circle
    int bounce_x = center_x + (int)(150 * sin(anim->time * 2));
    int bounce_y = center_y + (int)(100 * cos(anim->time * 1.5));
    window_draw_circle_simple(window, bounce_x, bounce_y, 20, 0xFF00FF);

    // Frame counter
    window_draw_rectangle_simple(window, 10, 10, anim->frame_count % 200, 5, 0xFFFF00);

    anim->time += 0.05f;
    anim->frame_count++;
}

// MLX event callbacks
int close_hook(void *param)
{
    t_window *window = (t_window *)param;
    window->should_close = true;
    return 0;
}

int key_hook(int keycode, void *param)
{
    t_window *window = (t_window *)param;

    printf("Key pressed: %d\n", keycode);

    // ESC key or 'q' to quit
    if (keycode == 65307 || keycode == 113)
    {
        window->should_close = true;
        return 0;
    }

    // Space to clear and redraw
    if (keycode == 32)
    {
        window_clear(window);
        test_basic_drawing(window);
        window_render(window);
    }

    // 'c' to test colors
    if (keycode == 99)
    {
        window_clear(window);
        test_color_patterns(window);
        window_render(window);
    }

    // 'r' to change background color randomly
    if (keycode == 114)
    {
        int random_color = rand() & 0xFFFFFF;
        window_set_background(window, random_color);
        window_clear(window);
        window_render(window);
    }

    return 0;
}

int test_key_hook(int keycode, void *param)
{
    t_window *win = (t_window *)param;
    printf("Key pressed in test: %d\n", keycode);
    if (keycode == 'q' || keycode == 'Q' || keycode == 65307)
    {
        win->should_close = true;
        printf("Closing window...\n");
    }
    return 0;
}

int animation_loop(void *param)
{
    t_animation *anim = (t_animation *)param;

    if (!anim->window->should_close)
    {
        test_animation_frame(anim);
        window_render(anim->window);
        usleep(16666); // ~60 FPS
    }

    return 0;
}

// Z-index test: draw overlapping objects with different z-index
void test_zindex(t_window *window)
{
    printf("=== Z-Index Test ===\n");
    printf("Window: %p, MLX: %p, Image: %p\n", window, window->mlx_ptr, window->img_ptr);
    printf("Window size: %dx%d\n", window->width, window->height);

    // Clear window first
    window_clear(window);

    // Force render after clear to see if we get black screen
    window_render(window);
    printf("Cleared window and rendered - you should see black background\n");
    sleep(1);

    printf("Drawing overlapping shapes to test z-index ordering...\n");

    // Test with simple pixel first
    printf("Testing basic pixel drawing...\n");
    window_put_pixel(window, 100, 100, 0xFFFFFF); // White pixel
    window_put_pixel(window, 101, 100, 0xFF0000); // Red pixel
    window_put_pixel(window, 102, 100, 0x00FF00); // Green pixel
    window_put_pixel(window, 103, 100, 0x0000FF); // Blue pixel
    window_render(window);
    printf("Drew test pixels at (100,100) - you should see 4 colored pixels\n");
    sleep(2);

    // Rectangle 1 (should be at the back - z=1)
    printf("Adding red rectangle (z=1) at (150, 150)\n");
    for (int y = 150; y < 250; y++)
    {
        for (int x = 150; x < 350; x++)
        {
            window_put_pixel(window, x, y, 0xFF0000); // Red
        }
    }
    window_render(window);
    printf("Drew red rectangle - you should see red rectangle\n");
    sleep(1);

    // Rectangle 2 (should be in middle - z=2)
    printf("Adding green rectangle (z=2) at (200, 200)\n");
    for (int y = 200; y < 300; y++)
    {
        for (int x = 200; x < 400; x++)
        {
            window_put_pixel(window, x, y, 0x00FF00); // Green
        }
    }
    window_render(window);
    printf("Drew green rectangle - you should see green overlapping red\n");
    sleep(1);

    // Circle (should be on top - z=3)
    printf("Adding blue circle (z=3) at (250, 180)\n");
    window_draw_circle_simple(window, 250, 180, 50, 0x0000FF); // Blue circle
    window_render(window);
    printf("Drew blue circle - you should see blue circle on top\n");
    sleep(1);

    // Draw legend with more visibility
    printf("Drawing legend...\n");
    window_draw_rectangle_simple(window, 10, 10, 200, 100, 0x333333); // Background

    // Draw bigger legend squares
    for (int y = 20; y < 35; y++)
    {
        for (int x = 20; x < 35; x++)
        {
            window_put_pixel(window, x, y, 0xFF0000); // Red square
        }
    }
    for (int y = 40; y < 55; y++)
    {
        for (int x = 20; x < 35; x++)
        {
            window_put_pixel(window, x, y, 0x00FF00); // Green square
        }
    }
    for (int y = 60; y < 75; y++)
    {
        for (int x = 20; x < 35; x++)
        {
            window_put_pixel(window, x, y, 0x0000FF); // Blue square
        }
    }

    // Draw text labels as simple patterns
    // "Z=1" for red
    window_draw_line_simple(window, 45, 20, 45, 35, 0xFFFFFF);
    window_draw_line_simple(window, 50, 20, 60, 20, 0xFFFFFF);
    window_draw_line_simple(window, 50, 35, 60, 35, 0xFFFFFF);

    // "Z=2" for green
    window_draw_line_simple(window, 45, 40, 45, 55, 0xFFFFFF);
    window_draw_line_simple(window, 50, 40, 60, 40, 0xFFFFFF);
    window_draw_line_simple(window, 50, 47, 60, 47, 0xFFFFFF);
    window_draw_line_simple(window, 50, 55, 60, 55, 0xFFFFFF);

    // "Z=3" for blue
    window_draw_line_simple(window, 45, 60, 45, 75, 0xFFFFFF);
    window_draw_line_simple(window, 50, 60, 60, 60, 0xFFFFFF);
    window_draw_line_simple(window, 50, 67, 60, 67, 0xFFFFFF);
    window_draw_line_simple(window, 50, 75, 60, 75, 0xFFFFFF);

    // Final render
    window_render(window);

    printf("✅ Z-Index test completed!\n");
    printf("You should see:\n");
    printf("  🔴 Red rectangle at the back (z=1)\n");
    printf("  🟢 Green rectangle in the middle (z=2)\n");
    printf("  🔵 Blue circle on top (z=3)\n");
    printf("  📋 Legend in top-left corner\n");
    printf("The blue circle should be visible on top of both rectangles.\n");
    printf("If you see only black, there might be an issue with window_put_pixel or window_render.\n");
    printf("Press any key to continue or wait 5 seconds...\n");

    // Wait for user interaction or timeout
    sleep(5);
}

// Test the window's layer system (if implemented)
void test_layer_system(t_window *window)
{
    printf("=== Layer System Test ===\n");

    // Test if the layer system is working
    if (!window->layers)
    {
        printf("⚠️  Layer system not initialized, creating manual test...\n");
        test_zindex(window);
        return;
    }

    printf("✅ Layer system detected, testing layer management...\n");

    // Create layers with different z-indices
    t_layer *layer1 = layer_new(1);
    t_layer *layer2 = layer_new(2);
    t_layer *layer3 = layer_new(3);

    if (!layer1 || !layer2 || !layer3)
    {
        printf("❌ Failed to create layers\n");
        return;
    }

    printf("✅ Created 3 layers with z-indices 1, 2, 3\n");

    // Add layers to window
    layer1->next = window->layers;
    window->layers = layer1;

    layer2->next = window->layers;
    window->layers = layer2;

    layer3->next = window->layers;
    window->layers = layer3;

    printf("✅ Added layers to window\n");
    printf("🎨 Rendering layered content...\n");

    // Since we don't have full object system, simulate with direct drawing
    window_clear(window);

    // Draw content that would be on each layer
    // Layer 1 content (background)
    for (int y = 100; y < 200; y++)
    {
        for (int x = 100; x < 300; x++)
        {
            window_put_pixel(window, x, y, 0x800000); // Dark red
        }
    }

    // Layer 2 content (middle)
    for (int y = 150; y < 250; y++)
    {
        for (int x = 200; x < 400; x++)
        {
            window_put_pixel(window, x, y, 0x008000); // Dark green
        }
    }

    // Layer 3 content (foreground)
    window_draw_circle_simple(window, 300, 200, 60, 0x000080); // Dark blue

    window_render(window);

    printf("✅ Layer system test completed!\n");

    // Cleanup
    layer_destroy(layer1);
    layer_destroy(layer2);
    layer_destroy(layer3);
}

// Forward declaration
int visual_test_run(void){
    return 0;
}

//int main(int argc, char **argv)
//{
//    // If "-atom" is passed, run the atom animation demo
//    for (int i = 1; i < argc; ++i)
//        if (strcmp(argv[i], "-atom") == 0)
//            return atom_demo_main(argc, argv);
//
//    printf("=== Window Object Test Program ===\n");
//
//    // Parse command line arguments
//    int width = 800;
//    int height = 600;
//    int bg_color = 0x000000;
//    bool enable_animation = false;
//    bool enable_zindex_test = false;
//    bool enable_visual_test = false;
//
//    for (int i = 1; i < argc; i++)
//    {
//        if (strcmp(argv[i], "-w") == 0 && i + 1 < argc)
//            width = atoi(argv[++i]);
//        else if (strcmp(argv[i], "-h") == 0 && i + 1 < argc)
//            height = atoi(argv[++i]);
//        else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
//            bg_color = strtol(argv[++i], NULL, 16);
//        else if (strcmp(argv[i], "-a") == 0)
//            enable_animation = true;
//        else if (strcmp(argv[i], "-z") == 0)
//            enable_zindex_test = true;
//        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--visual") == 0)
//            enable_visual_test = true;
//        else if (strcmp(argv[i], "--help") == 0)
//        {
//            printf("Usage: %s [-w width] [-h height] [-c hex_color] [-a] [-z] [-v] [--help]\n", argv[0]);
//            printf("  -w width     : Window width (default: 800)\n");
//            printf("  -h height    : Window height (default: 600)\n");
//            printf("  -c hex_color : Background color in hex (default: 000000)\n");
//            printf("  -a           : Enable animation mode\n");
//            printf("  -z           : Run Z-Index test\n");
//            printf("  -v, --visual : Run comprehensive visual test suite\n");
//            printf("  --help       : Show this help\n");
//            printf("\nControls:\n");
//            printf("  ESC/q : Quit\n");
//            printf("  SPACE : Redraw basic shapes\n");
//            printf("  c     : Test color patterns\n");
//            printf("  r     : Random background color\n");
//            return 0;
//        }
//    }
//
//    srand(time(NULL));
//
//    // Create window
//    printf("Creating window: %dx%d, bg_color: 0x%06X\n", width, height, bg_color);
//    t_window *window = window_new(width, height, "Window Object Test", bg_color);
//    if (!window)
//    {
//        printf("❌ Failed to create window\n");
//        return 1;
//    }
//
//    printf("✅ Window created successfully\n");
//    printf("MLX pointer: %p\n", window->mlx_ptr);
//    printf("Window pointer: %p\n", window->win_ptr);
//    printf("Image pointer: %p\n", window->img_ptr);
//
//    // Test basic functionality
//    printf("\n=== Testing Basic Window Operations ===\n");
//
//    // Test background color change
//    printf("Testing background color changes...\n");
//    window_set_background(window, 0xFF0000);
//    window_clear(window);
//    window_render(window);
//    usleep(500000); // 0.5 second
//
//    window_set_background(window, 0x00FF00);
//    window_clear(window);
//    window_render(window);
//    usleep(500000);
//
//    window_set_background(window, bg_color);
//    window_clear(window);
//
//    // Test drawing functions
//    test_basic_drawing(window);
//    window_render(window);
//
//    printf("✅ Basic drawing test completed\n");
//
//    // Setup event handlers
//    mlx_hook(window->win_ptr, 17, 0, close_hook, window);    // Close button
//    mlx_hook(window->win_ptr, 2, 1L << 0, key_hook, window); // Key press
//
//    printf("\n=== Controls ===\n");
//    printf("ESC/q : Quit\n");
//    printf("SPACE : Redraw basic shapes\n");
//    printf("c     : Test color patterns\n");
//    printf("r     : Random background color\n");
//
//    if (enable_animation)
//    {
//        printf("\n🎬 Animation mode enabled\n");
//        t_animation anim = {0};
//        anim.window = window;
//        anim.time = 0.0f;
//        anim.frame_count = 0;
//
//        mlx_loop_hook(window->mlx_ptr, animation_loop, &anim);
//    }
//
//    if (enable_zindex_test)
//    {
//        printf("\n🔍 Running Z-Index and Layer Tests...\n");
//
//        // First test basic window functionality
//        printf("Testing basic window functionality...\n");
//        window_set_background(window, 0x220000); // Dark red background
//        window_clear(window);
//        window_render(window);
//        printf("Set dark red background - do you see it? (waiting 2 seconds)\n");
//        sleep(2);
//
//        window_set_background(window, 0x000000); // Back to black
//        window_clear(window);
//        window_render(window);
//        printf("Back to black background\n");
//        sleep(1);
//
//        test_layer_system(window);
//
//        printf("\nPress 'q' to quit or any other key to continue...\n");
//
//        // Setup minimal event handling for the test
//        mlx_hook(window->win_ptr, 2, 1L << 0, test_key_hook, window);
//        mlx_hook(window->win_ptr, 17, 0, close_hook, window);
//
//        // Simple event loop for the test
//        printf("Entering test event loop...\n");
//        while (!window->should_close)
//        {
//            usleep(16666); // ~60 FPS
//            // MLX will handle events automatically
//        }
//
//        window_destroy(window);
//        return 0;
//    }
//
//    if (enable_visual_test)
//    {
//        printf("\n🎯 Running Visual Test Suite...\n");
//        return visual_test_run();
//    }
//
//    printf("\n🚀 Entering main loop...\n");
//
//    // Main event loop
//    mlx_loop(window->mlx_ptr);
//
//    printf("\n👋 Cleaning up...\n");
//    window_destroy(window);
//    printf("✅ Window destroyed successfully\n");
//
//    // Instead of the old test/animation, run the atom demo main loop:
//    return atom_demo_main(argc, argv);
//}
