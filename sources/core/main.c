/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:45:31 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/09 21:23:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include "fdf.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	int		exit_code;
	t_app	fdf;

	if (argc != 2)
		return (ft_fprintf(STDERR_FILENO, "Usage: fdf FILE \n"),
			EXIT_FAILURE);
	ft_memset(&fdf, 0, sizeof(t_app));
	fdf.auto_rotate = false;
	fdf.current_bg_theme = 0;
	fdf.stars_enabled = 1;
	fdf.shadow_mode = 0;
	fdf.has_color = false;
	fdf.input_state = INPUT_STATE_IDLE;
	if (make_fdf(&fdf, argv[1]))
	{
		exit_code = EXIT_SUCCESS;
		mlx_loop(fdf.mlx);
	}
	else
		exit_code = EXIT_FAILURE;
	return (fdf_destroy_contents(&fdf), exit_code);
}
