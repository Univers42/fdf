/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 22:55:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/02 23:00:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
#  define FLAGS_H
typedef struct enum e_state_flags
{
	STATE_RUNNING = 1 << 0,
	STATE_PAUSED = 1 << 1,
	STATE_DEBUG = 1 << 2,
	STATE_WIREFRAME = 1 << 3,
	STATE_COLORS = 1 << 4,
	STATE_NORMALS = 1 << 5,
	STATE_BOUNDS = 1 << 6
} t_state_flags;

typedef struct enum e_input_flags
{
	INPUT_MOUSE_LEFT = 1 << 0,
	INPUT_MOUSE_RIGHT = 1 << 1,
	INPUT_MOUSE_MIDDLE = 1 << 2,
	INPUT_KEY_SHIFT = 1 << 3,
	INPUT_KEY_CTRL = 1 << 4,
	INPUT_KEY_ALT = 1 << 5
}   t_input_flags;


#endif