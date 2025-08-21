#include "input_handler.h"
#include <stdio.h>
#include <mlx.h>

// Example callback functions
void	exit_callback(void *param)
{
	(void)param;
	printf("Exit key pressed!\n");
	exit(0);
}

//void	print_callback(void *param)
//{
//	char *message = (char *)param;
//	printf("Key pressed: %s\n", message);
//}
//
//int	main(void)
//{
//	t_input_event	*e;
//	void			*mlx_ptr;
//	void			*win_ptr;
//	char			*message;
//
//	// Initialize MLX
//	mlx_ptr = mlx_init();
//	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Event Test");
//	
//	// Create event system
//	e = create_event();
//	if (!e)
//		return (1);
//	
//	// Add events with callbacks
//	message = "Hello World!";
//	e->add_event(e, 99, print_callback, message);  // 'c' key
//	e->add_event(e, 105, print_callback, message);
//	e->add_event(e, 65307, exit_callback, NULL);   // ESC key
//	
//	// Hook events to program
//	e->prog_hook_events(e, win_ptr);
//	
//	// Start event loop
//	mlx_loop(mlx_ptr);
//	
//	// Cleanup
//	e->destroy(e);
//	return (0);
//}