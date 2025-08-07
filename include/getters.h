/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:27:06 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/07 23:03:43 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETTERS_H
# define GETTERS_H
#include "fdf.h"

#include "ds.h"
/**
    * Singletons
*/

inline t_projection_ctl    ctrl_projection(t_trans_stack *self)
{
    return (self->projection);
}

inline t_point3    r(t_trans_stack *self)
{
    return (self->r);
}

inline t_point3    o(t_trans_stack *self)
{
    return (self->o);
}

inline t_point3    t(t_trans_stack *self)
{
    return (self->t);
}

inline t_point3    p(t_trans_stack *self)
{
    return (self->p);
}

// FDF singletons
inline  t_renderer  render(t_fdf *fdf)
{
    return (fdf->renderer);
}

inline  t_bresenham_state   (t_fdf *fdf)
{
    return (fdf->bresenham_state);
}

inline t_trans_stack trans_stack(t_fdf *fdf)
{
    return (fdf->transformation->stack);
}

inline  t_input_state   input_state(t_fdf *fdf)
{
    return (fdf->input_state);
}

inline  t_bresenham_state   breshenham(t_bresenham_ctx *self)
{
    return (self->bresenham->state);
}
#endif