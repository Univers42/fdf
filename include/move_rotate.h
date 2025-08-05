/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:28:58 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/05 18:28:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_ROTATE_H
#define MOVE_ROTATE_H

#include "fdf.h"

void move_forward(t_app *fdf, float amount);
void move_backward(t_app *fdf, float amount);
void move_left(t_app *fdf, float amount);
void move_right(t_app *fdf, float amount);
void rotate_up(t_app *fdf, float angle);
void rotate_down(t_app *fdf, float angle);
void rotate_left(t_app *fdf, float angle);
void rotate_right(t_app *fdf, float angle);

#endif
