/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:45:31 by dmontesd          #+#    #+#             */
/*   Updated: 2025/08/07 23:56:45 by dlesieur         ###   ########.fr       */
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
	fdf = (t_app){0};
	fdf.auto_rotate = false;
	if (make_fdf(&fdf, argv[1]))
	{
		exit_code = EXIT_SUCCESS;
		mlx_loop(fdf.mlx);
	}
	else
		exit_code = EXIT_FAILURE;
	return (fdf_destroy_contents(&fdf), exit_code);
}
