/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:32:19 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 13:11:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H
# include <stdlib.h>
# include "ft_memory.h"
# include "arena.h"
# include <stdbool.h>

# ifndef RAND_MAX
#  define RAND_MAX 32767
# endif

typedef enum e_rng_type
{
	RNG_LCG = 0,
	RNG_XORSHIFT,
	RNG_MIDDLE_SQUARE,
	RNG_MAX_TYPES
}	t_rng_type;

typedef struct s_rng_state
{
	unsigned long	seed_lcg;
	unsigned long	seed_xorshift;
	unsigned long	seed_middle;
	t_rng_type		current_type;
}	t_rng_state;

char		*ft_itoa(int n);
char		*ft_utoa(unsigned int n);
char		*ft_xtoa(unsigned long int num, int is_upper);
int			ft_atoi(const char *nptr);
void		ft_putnbr_base(int nbr, char *radix);
int			ft_atoi_base(const char *str, int base);
void		*ft_calloc(t_size nmemb, t_size size);
// Remove or comment out this line if you want to use your custom ft_realloc
// void    *ft_realloc(void *ptr, t_size old, t_size new);
void		skip_spaces(int *i, int size, char *str);
void		dbl_free(char **ptr);
bool		grow_buf(void **ptr, size_t *cap, size_t start);
//RAND section
void		ft_srand(unsigned int new_seed, int select);
int			ft_rand(void);
t_rng_state	*get_rng_state(void);
const char	*get_algorithm_name(int type);

#endif