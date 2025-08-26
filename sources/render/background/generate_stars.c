/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_stars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 05:03:41 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/26 12:33:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "time.h"

// forward decls for our RNG API (kept local to avoid adding headers here)
void	ft_srand(unsigned int new_seed, int select);

static void	seed_rng_once(void)
{
	static int	seeded = 0;

	if (!seeded)
	{
		ft_srand((unsigned int)ft_time(), RNG_XORSHIFT);
		seeded = 1;
	}
}

static inline t_point2	star_pos(int i)
{
	t_point2	s;

	s.x = (i * 73 + 17) % WIN_WIDTH;
	s.y = (i * 137 + 23) % WIN_HEIGHT;
	return (s);
}

static inline void	draw_star_square(uint32_t *buf, int x, int y, uint32_t c)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		buf[y * WIN_WIDTH + x] = c;
}

static void	draw_star(uint32_t *buf, t_point2 s, uint32_t c)
{
	draw_star_square(buf, s.x, s.y, c);
	draw_star_square(buf, s.x + 1, s.y, c);
	draw_star_square(buf, s.x, s.y + 1, c);
	draw_star_square(buf, s.x + 1, s.y + 1, c);
}

void	generate_stars(t_app *fdf)
{
	uint32_t	*buf;
	int			i;
	t_point2	s;
	uint32_t	c;

	if (!fdf->stars_enabled)
		return ;
	seed_rng_once();
	buf = (uint32_t *)fdf->renderer.data;
	i = -1;
	while (++i < STAR_COUNT)
	{
		s = star_pos(i);
		c = star_color_for_theme(fdf->current_bg_theme, i);
		if (s.x + 1 < WIN_WIDTH && s.y + 1 < WIN_HEIGHT)
			draw_star(buf, s, c);
	}
}
