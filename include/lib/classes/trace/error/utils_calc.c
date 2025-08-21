/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:21:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:33:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err_handler.h"
#include <stdio.h>
#include "ft_stdio.h"

void	print_error(t_handler *err, const char *file,
			const char *func, int line);

double	util_divide_positive(double a, double b, t_handler *err)
{
	double	res;
	int		code;

	code = 0;
	if (b == 0.0)
		code = 200;
	else if (a < 0 || b < 0)
		code = 201;
	else
		res = a / b;
	if (code)
	{
		err->last_error = code;
		print_error(err, __FILE__, __func__, __LINE__);
		return (0.0);
	}
	return (res);
}

double	util_divide_force_zero(double a, t_handler *err)
{
	(void)a;
	err->last_error = 200;
	print_error(err, __FILE__, __func__, __LINE__);
	return (0.0);
}

// Make print_error visible to other files
void	print_error(t_handler *err, const char *file,
			const char *func, int line)
{
	t_err_ctx	ctx;

	ctx.file = file;
	ctx.func = func;
	ctx.line = line;
	err->set_error(err, err->last_error, &ctx);
	ft_printf("Type error: %s (at %s:%d in %s)\n",
		err->get_message(err, err->last_error),
		err->file, err->line, err->func);
}
