/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_cross.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:34:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/26 12:35:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

// Add a handler for the window close (top-right cross) button.
int	window_close_handler(t_app *fdf)
{
	exit_prog(fdf, 0, NULL);
	return (0);
}
