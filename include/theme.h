#ifndef THEME_H
# define THEME_H

# include "fdf.h"
# include <stdint.h>

typedef struct s_theme_palette {
	const char	*name;
	uint32_t	colors[8];   // packed RGBA
	int			color_count;
	uint32_t	background;
}	t_theme_palette;

/* Palette core */
void		init_palette_system(t_app *fdf);
void		set_palette_index(int idx, t_app *fdf);
void		apply_current_palette(t_app *fdf);
bool		palette_needs_update(t_app *fdf); // added: check if colors need refresh
void		update_palette_if_needed(t_app *fdf); // added: check and apply if needed

/* Color access */
uint32_t	get_color_for_height(t_app *fdf, float norm);
uint32_t	get_color_for_z(t_app *fdf, int z);

/* Utility */
uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	create_color(uint8_t r, uint8_t g, uint8_t b); // replacement for C macro

/* Per-color shadow helpers */
uint32_t	color_apply_depth_shadow(uint32_t color, float depth_norm);
uint32_t	color_apply_ambient_shadow(uint32_t color, float intensity);

/* Background integration */
void		update_background_from_palette(t_app *fdf);
void		clear_screen_with_palette_bg(t_app *fdf); // added: for render loop

/* Palette singleton access */
const t_theme_palette	*get_theme_palette(int idx);
int						get_theme_palette_count(void);

#endif
