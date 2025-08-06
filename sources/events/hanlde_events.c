/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hanlde_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:11:25 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/06 05:01:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

#define MAX_KEYCODE 70000  // Increased to handle X11 keycodes
#define MODIFIER_COMBO_COUNT 8 // 3 bits: Shift, Ctrl, Alt

// Special keycode mapping for common X11 keys that are out of normal range
typedef struct s_keycode_map {
	int x11_keycode;
	int mapped_keycode;
} t_keycode_map;

static const t_keycode_map g_keycode_mappings[] = {
	{65307, 1000},  // Escape
	{65362, 1001},  // Arrow Up
	{65364, 1002},  // Arrow Down  
	{65361, 1003},  // Arrow Left
	{65363, 1004},  // Arrow Right
	{65451, 1005},  // KP_Add
	{65453, 1006},  // KP_Subtract
	{4097,  1007},  // Mouse Right
	{4098,  1008},  // Mouse Left
	{4099,  1009},  // Mouse Scroll
	{0, 0}          // End marker
};

// Map problematic keycodes to a safe range
static int map_keycode(int keycode)
{
	// Normal keycodes pass through
	if (keycode >= 0 && keycode < 1000)
		return keycode;
	
	// Check mapping table for special keys
	for (int i = 0; g_keycode_mappings[i].x11_keycode != 0; i++)
	{
		if (g_keycode_mappings[i].x11_keycode == keycode)
			return g_keycode_mappings[i].mapped_keycode;
	}
	
	// Unmapped large keycodes get a default safe value
	return 999; // Safe fallback
}

// Event handler table singleton
typedef struct s_event_handler_table {
	t_event_fn handler_table[MAX_KEYCODE][MODIFIER_COMBO_COUNT];
	bool initialized;
} t_event_handler_table;

// Singleton accessor for event handler table
static t_event_handler_table *get_event_handler_table(void)
{
	static t_event_handler_table instance = {0};
	
	if (!instance.initialized)
	{
		// Initialize all handlers to NULL
		for (int i = 0; i < MAX_KEYCODE; i++)
		{
			for (int j = 0; j < MODIFIER_COMBO_COUNT; j++)
			{
				instance.handler_table[i][j] = NULL;
			}
		}
		instance.initialized = true;
	}
	return &instance;
}

// Map X11 modifier mask to a small index (0-7)
static inline int modifier_index(unsigned int mods)
{
	// Only care about Shift, Ctrl, Alt (Mod1)
	return ((mods & ShiftMask) ? 1 : 0)
	     | ((mods & ControlMask) ? 2 : 0)
	     | ((mods & Mod1Mask) ? 4 : 0);
}

// Register a handler for a key+modifier combination
void register_event_binding(int keycode, unsigned int modifiers, t_event_fn handler)
{
	t_event_handler_table *table = get_event_handler_table();
	int mapped_keycode = map_keycode(keycode);
	int mod_idx = modifier_index(modifiers);
	
	if (mapped_keycode >= 0 && mapped_keycode < MAX_KEYCODE)
	{
		table->handler_table[mapped_keycode][mod_idx] = handler;
	}
}

// Enhanced lookup that passes keycode to handler
t_event_fn find_event_handler(int keycode, unsigned int modifiers)
{
	t_event_handler_table *table = get_event_handler_table();
	int mapped_keycode = map_keycode(keycode);
	
	if (mapped_keycode >= 0 && mapped_keycode < MAX_KEYCODE)
	{
		int mod_idx = modifier_index(modifiers);
		t_event_fn handler = table->handler_table[mapped_keycode][mod_idx];
		return handler;
	}
	return NULL;
}

// Setup all event bindings (call this at startup)
void setup_event_bindings(void)
{
	// Movement keys - WASD
	register_event_binding(W, 0, move_up);      // W = forward
	register_event_binding(A, 0, move_left);    // A = left
	register_event_binding(S, 0, move_down);    // S = backward
	register_event_binding(D, 0, move_right);   // D = right
	
	// Rotation keys - Arrow keys (without Ctrl)
	register_event_binding(ARROW_UP, 0, rotate_up_handler);
	register_event_binding(ARROW_DOWN, 0, rotate_down_handler);
	register_event_binding(ARROW_LEFT, 0, rotate_left_handler);
	register_event_binding(ARROW_RIGHT, 0, rotate_right_handler);
	
	// Z-perspective controls (Ctrl + Arrow) - register with both enum and direct keycode
	register_event_binding(ARROW_UP, ControlMask, z_perspective_ctrl);
	register_event_binding(ARROW_DOWN, ControlMask, z_perspective_ctrl);
	register_event_binding(65362, ControlMask, z_perspective_ctrl);    // Direct keycode for Up
	register_event_binding(65364, ControlMask, z_perspective_ctrl);    // Direct keycode for Down
	
	// Projection controls
	register_event_binding(P, 0, projection_fly);
	register_event_binding(I, 0, project_iso);
	
	// Shape transformation
	register_event_binding(T, 0, ch_shape);
	
	// System controls
	register_event_binding(R, 0, reset_state);
	register_event_binding(65307, 0, exit_prog);   // Escape
	
	// Zoom controls
	register_event_binding(XK_plus, 0, zoom_in);
	register_event_binding(XK_minus, 0, zoom_out);
	register_event_binding(XK_KP_Add, 0, zoom_in);
	register_event_binding(XK_KP_Subtract, 0, zoom_out);
	
	// Other controls
	register_event_binding(SPACE_BAR, 0, auto_rotate);
	
	// Color palette controls (keys 1-9)
	register_event_binding(ONE, 0, palette_1_handler);
	register_event_binding(TWO, 0, palette_2_handler);
	register_event_binding(THREE, 0, palette_3_handler);
	register_event_binding(FOUR, 0, palette_4_handler);
	register_event_binding(FIVE, 0, palette_5_handler);
	register_event_binding(SIX, 0, palette_6_handler);
	register_event_binding(SEVEN, 0, palette_7_handler);
	register_event_binding(EIGHT, 0, palette_8_handler);
	register_event_binding(NINE, 0, palette_9_handler);
	
	// Particle system (lowercase g)
	register_event_binding(G, 0, ch_particules);
	
	printf("FDF Event System: WASD movement, Arrow rotation, Ctrl+Arrow Z-perspective, T shapes, I/P projection, Space auto-rotate, 1-9 color palettes, G particles, ESC exit\n");
}

// Event system initialization function
void event_system_init(t_app *fdf)
{
	(void)fdf; // Mark as unused
	// Event system is already initialized through singleton pattern
}

// Enhanced event dispatcher with better fallback handling
void handle_key_event(int keycode, unsigned int modifiers, t_app *fdf)
{
	// Debug output to see what's happening
	static int debug_counter = 0;
	if (++debug_counter % 20 == 0) // Only print occasionally to avoid spam
	{
		printf("Key event: keycode=%d\n", keycode);
	}
	
	t_event_fn fn = find_event_handler(keycode, modifiers);
	if (fn != NULL)
	{
		fn(fdf, keycode, NULL);
		return;
	}
	
	// Special handling for common key combinations that might not be caught
	// Check for common Ctrl combinations by keycode patterns
	if (keycode == ARROW_UP || keycode == 65362)
	{
		// For now, assume it's regular rotation unless we detect otherwise
		rotate_up_handler(fdf, keycode, NULL);
	}
	else if (keycode == ARROW_DOWN || keycode == 65364)
	{
		rotate_down_handler(fdf, keycode, NULL);
	}
	else if (keycode == ARROW_LEFT || keycode == 65361)
	{
		rotate_left_handler(fdf, keycode, NULL);
	}
	else if (keycode == ARROW_RIGHT || keycode == 65363)
	{
		rotate_right_handler(fdf, keycode, NULL);
	}
	// Add a simple way to trigger z-perspective with different keys
	else if (keycode == XK_equal || keycode == XK_plus) // + key for z-perspective up
	{
		increase_z_perspective(fdf);
		printf("Z-perspective increased (+)\n");
	}
	else if (keycode == XK_underscore || keycode == XK_minus) // - key for z-perspective down
	{
		reduce_z_perspective(fdf);
		printf("Z-perspective reduced (-)\n");
	}
}