/*
** mlx_int.h for mlx in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Mon Jul 31 16:45:48 2000 Charlie Root
** Last update Wed May 25 16:44:16 2011 Olivier Crouzet
*/



/*
** Internal settings for MiniLibX
*/

#ifndef MLX_INT_H

# define MLX_INT_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <X11/extensions/XShm.h>
# include <X11/XKBlib.h>
/* #include	<X11/xpm.h> */


# define MLX_TYPE_SHM_PIXMAP	3
# define MLX_TYPE_SHM			2
# define MLX_TYPE_XIMAGE		1
# define MLX_MAX_EVENT			LASTEvent
# define ENV_DISPLAY			"DISPLAY"
# define LOCALHOST				"localhost"
# define ERR_NO_TRUECOLOR		"MinilibX Error : No TrueColor Visual available.\n"
# define WARN_SHM_ATTACH		"MinilibX Warning : X server can't attach shared memory.\n"


typedef	struct	s_xpm_col
{
	int		name;	//color name as string
	int		col;	// color value
}				t_xpm_col;


struct	s_col_name
{
	char	*name;	//color name as a string (e.g., "red")
	int		color;	// Color value (e.g., 0xFF0000)
};

typedef struct	s_event_list
{
	int		mask;		// X11 event mask (e.g., Exposure mask, keypressmask)
	int		(*hook)();	//Pointer to the callback function for the event
	void	*param;		// Pointer to user data passed to the callback
}				t_event_list;

typedef struct	s_win_list
{
	Window				window;				//X11 window handle
	GC					gc;					// Graphics context for the window
	struct s_win_list	*next;				// Poijter to the next view in the list
	int					(*mouse_hook)();	// Mouse event callback
	int					(*key_hook)();		// key event callback
	int					(*expose_hook)();	// Expose event callback
	void				*mouse_param;		// User data for mouse callback
	void				*key_param;			// user data for key callback
	void				*expose_param;		// user data for exposse callback
	t_event_list		hooks[MLX_MAX_EVENT];	//array of event hooks for x11 events
}				t_win_list;


typedef struct	s_img
{
	XImage			*image;		//Pointer to the X11 image structure
	Pixmap			pix;		// X11 pixmap for the image
	GC				gc;			// Graphics context for the image
	int				size_line;	// Number of bytes in a row of the image
	int				bpp;		// bits per pixel
	int				width;		//Image width in pixels
	int				height;		// Image height in pixels
	int				type;		// Image type (e.g., SHM, XImage)
	int				format;		// Image format
	char			*data;		// Pointer to raw pixel data
	XShmSegmentInfo	shm;		// Shared mmeory segment info(if used)
}				t_img;

/**
hold all global state and configuration for the Minilibx display
and windows
used for event handling ; color management; ressource tracking
*/
typedef struct	s_xvar
{
	Display		*display;		//Pointer to the X11 display connection
	Window		root;			// Root window of the display
	int			screen;			// Screen number
	int			depth;			// Color depth (bits per pixel)
	Visual		*visual;		// Visual type for the display
	Colormap	cmap;			// Colormap used for the display
	int			private_cmap;	//Flag for private colormap usage
	t_win_list	*win_list;		//linked list of minilibx window
	int			(*loop_hook)();	//pointer to the main loop callback function
	void		*loop_param;	//User data for the loop callback
	int			use_xshm;		//flag for X11 shared memory usage
	int			pshm_format;	//Shared memory pixmap format
	int			do_flush;		//Flag to flush display after drawing
	int			decrgb[6];		//RGB bit shifts and lengths for color convenience
	Atom		wm_delete_window;	// Atom for window close protocol
	Atom		wm_protocols;		// Atom for window manager protocols
	int 		end_loop;			// Flag to end the main loop
}				t_xvar;


int				mlx_int_do_nothing();
int				mlx_get_color_value();
int				mlx_int_get_good_color();
int				mlx_int_find_in_pcm();
int				mlx_int_anti_resize_win();
int				mlx_int_wait_first_expose();
int				mlx_int_rgb_conversion();
int				mlx_int_deal_shm();
void			*mlx_int_new_xshm_image();
char			**mlx_int_str_to_wordtab();
void			*mlx_new_image();
int				shm_att_pb();
int				mlx_int_get_visual(t_xvar *xvar);
int				mlx_int_set_win_event_mask(t_xvar *xvar);
int				mlx_int_str_str_cote(char *str,char *find,int len);
int				mlx_int_str_str(char *str,char *find,int len);


#endif
