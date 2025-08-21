/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:28:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 15:34:35 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLER_H
# define INPUT_HANDLER_H

# include <stdlib.h>
# include <mlx.h>

# define MAX_EVENTS 256

typedef struct s_event_entry
{
	int		keycode;
	void	(*callback)(void *param);
	void	*param;
}			t_event_entry;

typedef struct s_input_event
{
	t_event_entry	events[MAX_EVENTS];
	int				event_count;
	void			*mlx_ptr;
	void			*win_ptr;
	void			(*add_event)(struct s_input_event *self,
			int keycode, void (*callback)(void *), void *param);
	void			(*prog_hook_events)(struct s_input_event *self, void *win);
	void			(*destroy)(struct s_input_event *self);
}					t_input_event;

t_input_event	*create_event(void);
int				handle_keypress(int keycode, void *param);
int				handle_close(void *param);
t_input_event	*create_event(void);
int				handle_keypress(int keycode, void *param);
int				handle_close(void *param);
void			destroy_method(t_input_event *self);
void			input_destroy(struct s_input_event *self);
void			input_add_event(struct s_input_event *self,
					int keycode, void (*callback)(void *), void *param);
void			add_event_method(t_input_event *self, int keycode,
					void (*callback)(void *), void *param);
void			input_prog_hook_events(struct s_input_event *self, void *win);
void			prog_hook_events_method(t_input_event *self, void *win);
void			prog_hook_events_method(t_input_event *self, void *win);

#endif
