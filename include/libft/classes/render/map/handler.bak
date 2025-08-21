/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:44:51 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/31 22:55:00 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

// Forward declarations for FSM handlers
void fsm_handle_space(t_parser *parser);
void fsm_handle_color(t_parser *parser);
void fsm_handle_val(t_parser *parser);
void fsm_handle_word(t_parser *parser);

// Provide the jump table for FSM handlers
typedef void (*fsm_handler_fn)(t_parser *);

fsm_handler_fn *get_fsm_jump_table(void)
{
    static fsm_handler_fn jump_table[4] = {
        fsm_handle_space,
        fsm_handle_color,
        fsm_handle_val,
        fsm_handle_word
    };
    return jump_table;
}