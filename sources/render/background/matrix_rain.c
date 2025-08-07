#include "fdf.h"
#include <math.h>

extern t_dynamic_bg_system g_dynamic_bg;

// Apply Matrix rain background - digital falling code
void apply_matrix_rain_bg(uint32_t *buffer)
{
	float time = g_dynamic_bg.time_accumulator;
	
	// Clear to black first
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
		buffer[i] = 0x000000;
	
	// Create falling "rain" columns
	int column_width = 20;
	int num_columns = WIN_WIDTH / column_width;
	
	for (int col = 0; col < num_columns; col++)
	{
		// Each column has different timing
		float column_offset = col * 0.7f;
		float fall_speed = 8.0f + (col % 3) * 2.0f;
		
		// Calculate drop position
		float drop_y = fmodf(time * fall_speed + column_offset, WIN_HEIGHT + 200.0f) - 100.0f;
		
		// Draw the falling "code"
		for (int trail = 0; trail < 15; trail++)
		{
			int y = (int)(drop_y - trail * 25);
			if (y >= 0 && y < WIN_HEIGHT)
			{
				for (int dx = 0; dx < column_width - 5; dx++)
				{
					int x = col * column_width + dx + 2;
					if (x >= 0 && x < WIN_WIDTH)
					{
						// Fade trail effect
						float fade = 1.0f - (trail / 15.0f);
						
						// Different shades of green
						if (trail == 0)
							buffer[y * WIN_WIDTH + x] = 0x00FF00; // Bright green head
						else if (trail < 3)
							buffer[y * WIN_WIDTH + x] = 0x00CC00; // Medium green
						else if (trail < 8)
							buffer[y * WIN_WIDTH + x] = (uint32_t)(0x008800 * fade); // Fading green
						else
							buffer[y * WIN_WIDTH + x] = (uint32_t)(0x004400 * fade); // Dark green
					}
				}
			}
		}
	}
}