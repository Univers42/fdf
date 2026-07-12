/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:07:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/09 19:38:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_H
# define PIXEL_H
# include <stdbool.h>
# include <stdint.h>

// Polar coordinates indices
# define LAT 0    // Latitude
# define LONG 1   // Longitude

# define ROJO 		0xc1272d
# define VERDE		0x33cc55
# define FUCSIA 	0xff255c
# define AZUL		0x1B8EFA
# define SUPERAZUL	0x0000FF
# define CARBON		0x151515
# define WHITE		0xBBBBBB
# define DISCO		0x9A1F6A
# define BRICK_RED	0xC2294E
# define FLAMINGO	0xEC4B27
# define JAFFA		0xEF8633
# define SAFFRON	0xAAAAAA

# define DEFAULT_COLOR		JAFFA
# define BOTTOM_COLOR		AZUL
# define TOP_COLOR			BRICK_RED
# define GROUND_COLOR		SAFFRON
# define BACK_COLOR			0x151515
# define MENU_COLOR			0x202020
# define TEXT_COLOR			0xEAEAEA	
# define NUMBER_COLOR		0xF3AF3D

typedef enum e_axis
{
	X,
	Y,
	Z,
}	t_axis;

typedef struct m_colors
{
	int	topcolor;
	int	groundcolor;
	int	bottomcolor;
	int	backcolor;
	int	menucolor;	
}		t_colors;

typedef struct s_color
{
	int			z_val;
	float		zf_val;
	uint32_t	hex_color;
	union
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	}			u_raw_color;
}				t_color;

typedef struct s_rgba
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}			t_rgba;

typedef struct s_fvectorfN
{
	double	x;
	double	y;
	union
	{
		struct
		{
			double	z;
		}	s_v3;
		struct
		{
			double	z;
			double	w;
		}	s_v4;
	}	u_ctx;
}	t_fvectorfN;

typedef struct s_fvectorN
{
	float	x;
	float	y;
	union
	{
		struct
		{
			float	z;
		}	s_v3;
		struct
		{
			float	z;
			float	w;
		}	s_v4;
	}	u_ctx;
}	t_fvectorN;

typedef struct s_vectorN
{
	int	x;
	int	y;
	union
	{
		struct
		{
			int	z;
		}	s_v3;
		struct
		{
			int	z;
			int	w;
		}	s_v4;
	}	u_ctx;
}	t_vectorN;

typedef struct s_point
{
	float	axis[3];
	float	polar[2];
	float	original[3];
	t_color	color;
	t_axis	axes;
	bool	paint;
}			t_point;

// 2D, 3D, 4D Vectors
typedef struct s_point2
{
	int	x;
	int	y;
}		t_point2;

typedef struct s_fpoint2
{
	float	x;
	float	y;
}			t_fpoint2;

typedef struct s_fpoint3
{
	float	x;
	float	y;
	float	z;
}			t_fpoint3;

typedef struct s_fpoint4
{
	float	x;
	float	y;
	float	z;
	float	w;
}			t_fpoint4;

typedef struct s_point3
{
	int	x;
	int	y;
	int	z;
}		t_point3;

typedef struct s_point4
{
	int	x;
	int	y;
	int	z;
	int	w;
}		t_point4;
void	load_color(int max, int min, t_point *point, t_colors colors);
int		gradient(int startcolor, int endcolor, int len, int pix);
#endif