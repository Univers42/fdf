/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:19:48 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/28 17:14:04 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_HANDLER_H
# define ERR_HANDLER_H

# include <stddef.h>

typedef struct s_handler		t_handler;
typedef struct s_interface		t_interface;
typedef struct s_err_ctx		t_err_ctx;

struct	s_err_ctx
{
	const char	*file;
	const char	*func;
	int			line;
};

// Registry struct with methods
struct	s_interface
{
	int			(*add_message)(t_interface *self, int code,
			const char *message);
	const char	*(*get_message)(t_interface *self, int code);
	void		(*destroy)(t_interface *self);
	void		*impl;
};

// Handler struct with methods
struct s_handler
{
	void		(*set_error)(t_handler *self, int code, t_err_ctx *ctx);
	const char	*(*get_message)(t_handler *self, int code);
	int			last_error;
	const char	*file;
	const char	*func;
	int			line;
	void		*ctx;
	void		*custom_data;
};

struct s_err_entry
{
	int					code;
	const char			*message;
	struct s_err_entry	*next;
};

struct	s_registry_impl
{
	struct s_err_entry	*head;
};

// Registry API (object-oriented style)
t_interface	*err_registry_create(void);
t_interface	*err_default_registry(void);

// Handler API (object-oriented style)
t_handler	*err_handler_create(void);
void		err_handler_destroy(t_handler *handler);
void		print_error(t_handler *err, const char *file,
				const char *func, int line);
#endif