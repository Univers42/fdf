// #include "window.h"
// #include <stdio.h>
// #include <unistd.h>
// #include <time.h>
// #include <math.h>
// #include <stdlib.h>
// #include <stdint.h> // Add this for uint32_t, uint8_t
// #include <string.h> // Add this for memset
// #include "mlx.h"

// #define MAX_ELECTRONS 8
// #define MAX_PROTONS 6
// #define MAX_NEUTRONS 6
// #define MAX_ORBITS 3
// #define MAX_PARTICLES 100

// typedef struct s_particle
// {
//     double x, y, z;
//     double vx, vy, vz;
//     double size;
//     uint32_t color;
//     double life;
//     double max_life;
//     int type; // 0=electron, 1=proton, 2=neutron, 3=energy_particle
// } t_particle;

// typedef struct s_electron
// {
//     double angle;
//     double speed;
//     double orbit_radius;
//     double orbit_tilt;
//     double phase_offset;
//     int orbit_level;
//     uint32_t color;
//     double energy_level;
//     t_particle trail[20];
//     int trail_index;
// } t_electron;

// typedef struct s_nucleus
// {
//     double x, y, z;
//     double rotation;
//     double pulse;
//     t_particle protons[MAX_PROTONS];
//     t_particle neutrons[MAX_NEUTRONS];
//     int proton_count;
//     int neutron_count;
//     double energy_field;
// } t_nucleus;

// typedef struct s_atom
// {
//     t_nucleus nucleus;
//     t_electron electrons[MAX_ELECTRONS];
//     int electron_count;
//     t_particle energy_particles[MAX_PARTICLES];
//     int particle_count;
//     double time;
//     double center_x, center_y;
//     double zoom;
//     int atom_type; // 1=Hydrogen, 2=Helium, 6=Carbon, etc.
//     double electromagnetic_field;
//     double quantum_fluctuation;
// } t_atom;

// // Color definitions for different particles
// #define COLOR_ELECTRON 0x00BFFF // Deep sky blue
// #define COLOR_PROTON 0xFF4500   // Orange red
// #define COLOR_NEUTRON 0x696969  // Dim gray
// #define COLOR_NUCLEUS 0xFFD700  // Gold
// #define COLOR_ENERGY 0xFF69B4   // Hot pink
// #define COLOR_FIELD 0x00FFFF    // Cyan
// #define COLOR_QUANTUM 0x9370DB  // Medium purple

// // Forward declarations
// static void add_energy_particle(t_atom *atom, double x, double y, uint32_t color);
// static void draw_glowing_circle(t_window *win, int x, int y, int radius, uint32_t color, double intensity);

// // Initialize different atom types
// static void init_hydrogen_atom(t_atom *atom)
// {
//     atom->atom_type = 1;
//     atom->nucleus.proton_count = 1;
//     atom->nucleus.neutron_count = 0;
//     atom->electron_count = 1;

//     // Single electron in ground state
//     atom->electrons[0].orbit_radius = 80;
//     atom->electrons[0].speed = 0.02;
//     atom->electrons[0].orbit_tilt = 0;
//     atom->electrons[0].energy_level = 1.0;
//     atom->electrons[0].color = COLOR_ELECTRON;
// }

// static void init_helium_atom(t_atom *atom)
// {
//     atom->atom_type = 2;
//     atom->nucleus.proton_count = 2;
//     atom->nucleus.neutron_count = 2;
//     atom->electron_count = 2;

//     // Two electrons in same shell but different phases
//     for (int i = 0; i < 2; i++)
//     {
//         atom->electrons[i].orbit_radius = 70;
//         atom->electrons[i].speed = 0.025;
//         atom->electrons[i].orbit_tilt = i * M_PI / 6;
//         atom->electrons[i].phase_offset = i * M_PI;
//         atom->electrons[i].energy_level = 1.0;
//         atom->electrons[i].color = COLOR_ELECTRON;
//     }
// }

// static void init_carbon_atom(t_atom *atom)
// {
//     atom->atom_type = 6;
//     atom->nucleus.proton_count = 6;
//     atom->nucleus.neutron_count = 6;
//     atom->electron_count = 6;

//     // 2 electrons in inner shell
//     for (int i = 0; i < 2; i++)
//     {
//         atom->electrons[i].orbit_radius = 60;
//         atom->electrons[i].speed = 0.03;
//         atom->electrons[i].orbit_tilt = i * M_PI / 4;
//         atom->electrons[i].phase_offset = i * M_PI;
//         atom->electrons[i].energy_level = 1.0;
//         atom->electrons[i].color = 0x87CEEB; // Light blue
//     }

//     // 4 electrons in outer shell
//     for (int i = 2; i < 6; i++)
//     {
//         atom->electrons[i].orbit_radius = 120;
//         atom->electrons[i].speed = 0.02;
//         atom->electrons[i].orbit_tilt = (i - 2) * M_PI / 2;
//         atom->electrons[i].phase_offset = (i - 2) * M_PI / 2;
//         atom->electrons[i].energy_level = 2.0;
//         atom->electrons[i].color = COLOR_ELECTRON;
//     }
// }

// static void init_atom(t_atom *atom, int type, double center_x, double center_y)
// {
//     memset(atom, 0, sizeof(t_atom));
//     atom->center_x = center_x;
//     atom->center_y = center_y;
//     atom->zoom = 1.0;
//     atom->nucleus.x = center_x;
//     atom->nucleus.y = center_y;
//     atom->nucleus.z = 0;

//     switch (type)
//     {
//     case 1:
//         init_hydrogen_atom(atom);
//         break;
//     case 2:
//         init_helium_atom(atom);
//         break;
//     case 6:
//         init_carbon_atom(atom);
//         break;
//     default:
//         init_hydrogen_atom(atom);
//         break;
//     }

//     // Initialize nucleus particles
//     double nucleus_radius = 15;
//     for (int i = 0; i < atom->nucleus.proton_count; i++)
//     {
//         double angle = (2.0 * M_PI * i) / atom->nucleus.proton_count;
//         atom->nucleus.protons[i].x = nucleus_radius * cos(angle);
//         atom->nucleus.protons[i].y = nucleus_radius * sin(angle);
//         atom->nucleus.protons[i].z = (rand() % 10 - 5);
//         atom->nucleus.protons[i].size = 8;
//         atom->nucleus.protons[i].color = COLOR_PROTON;
//     }

//     for (int i = 0; i < atom->nucleus.neutron_count; i++)
//     {
//         double angle = (2.0 * M_PI * i) / atom->nucleus.neutron_count + M_PI / atom->nucleus.neutron_count;
//         atom->nucleus.neutrons[i].x = nucleus_radius * 0.8 * cos(angle);
//         atom->nucleus.neutrons[i].y = nucleus_radius * 0.8 * sin(angle);
//         atom->nucleus.neutrons[i].z = (rand() % 10 - 5);
//         atom->nucleus.neutrons[i].size = 8;
//         atom->nucleus.neutrons[i].color = COLOR_NEUTRON;
//     }

//     // Initialize electron angles randomly
//     for (int i = 0; i < atom->electron_count; i++)
//     {
//         atom->electrons[i].angle = (rand() % 628) / 100.0; // Random angle
//         atom->electrons[i].trail_index = 0;
//     }
// }

// static void add_energy_particle(t_atom *atom, double x, double y, uint32_t color)
// {
//     if (atom->particle_count >= MAX_PARTICLES)
//         return;

//     t_particle *p = &atom->energy_particles[atom->particle_count++];
//     p->x = x + (rand() % 20 - 10);
//     p->y = y + (rand() % 20 - 10);
//     p->z = rand() % 10 - 5;
//     p->vx = (rand() % 100 - 50) / 50.0;
//     p->vy = (rand() % 100 - 50) / 50.0;
//     p->vz = (rand() % 100 - 50) / 50.0;
//     p->size = rand() % 3 + 1;
//     p->color = color;
//     p->life = p->max_life = 60 + rand() % 120;
//     p->type = 3;
// }

// static void update_atom(t_atom *atom)
// {
//     atom->time += 0.016; // ~60 FPS
//     atom->nucleus.rotation += 0.01;
//     atom->nucleus.pulse = sin(atom->time * 2) * 0.3 + 1.0;
//     atom->electromagnetic_field = sin(atom->time * 3) * 0.5 + 0.5;
//     atom->quantum_fluctuation = sin(atom->time * 7) * 0.2;

//     // Update electrons with quantum mechanics inspired movement
//     for (int i = 0; i < atom->electron_count; i++)
//     {
//         t_electron *e = &atom->electrons[i];

//         // Add quantum uncertainty to movement
//         double uncertainty = (rand() % 100 - 50) / 10000.0;
//         e->speed += uncertainty;
//         if (e->speed < 0.01)
//             e->speed = 0.01;
//         if (e->speed > 0.05)
//             e->speed = 0.05;

//         e->angle += e->speed;
//         if (e->angle > 2 * M_PI)
//             e->angle -= 2 * M_PI;

//         // Add energy level transitions (random quantum jumps)
//         if (rand() % 2000 == 0)
//         {
//             double old_radius = e->orbit_radius;
//             if (rand() % 2)
//             {
//                 e->orbit_radius *= 1.5; // Excitation
//                 e->energy_level += 0.5;
//             }
//             else
//             {
//                 e->orbit_radius *= 0.8; // De-excitation
//                 e->energy_level -= 0.3;
//                 if (e->energy_level < 0.5)
//                     e->energy_level = 0.5;
//             }

//             // Emit energy particle when transitioning
//             double x = atom->center_x + old_radius * cos(e->angle);
//             double y = atom->center_y + old_radius * sin(e->angle);
//             add_energy_particle(atom, x, y, COLOR_ENERGY);
//         }

//         // Store trail for electron path
//         double trail_x = atom->center_x + e->orbit_radius * cos(e->angle + e->phase_offset);
//         double trail_y = atom->center_y + e->orbit_radius * sin(e->angle + e->phase_offset) * cos(e->orbit_tilt);

//         e->trail[e->trail_index].x = trail_x;
//         e->trail[e->trail_index].y = trail_y;
//         e->trail[e->trail_index].life = 20;
//         e->trail_index = (e->trail_index + 1) % 20;
//     }

//     // Update energy particles
//     for (int i = 0; i < atom->particle_count; i++)
//     {
//         t_particle *p = &atom->energy_particles[i];
//         p->x += p->vx;
//         p->y += p->vy;
//         p->z += p->vz;
//         p->life--;

//         // Add gravity towards nucleus
//         double dx = atom->nucleus.x - p->x;
//         double dy = atom->nucleus.y - p->y;
//         double dist = sqrt(dx * dx + dy * dy);
//         if (dist > 0)
//         {
//             p->vx += dx / (dist * 100);
//             p->vy += dy / (dist * 100);
//         }

//         if (p->life <= 0)
//         {
//             // Remove dead particle
//             *p = atom->energy_particles[--atom->particle_count];
//             i--;
//         }
//     }

//     // Randomly emit energy from nucleus
//     if (rand() % 100 == 0)
//     {
//         add_energy_particle(atom, atom->nucleus.x, atom->nucleus.y, COLOR_QUANTUM);
//     }
// }

// static void draw_glowing_circle(t_window *win, int x, int y, int radius, uint32_t color, double intensity)
// {
//     // Draw multiple layers for glow effect
//     for (int r = radius; r > 0; r--)
//     {
//         double alpha = intensity * (double)r / radius;
//         uint32_t glow_color = color;

//         // Fade the color based on distance from center
//         uint8_t red = ((color >> 16) & 0xFF) * alpha;
//         uint8_t green = ((color >> 8) & 0xFF) * alpha;
//         uint8_t blue = (color & 0xFF) * alpha;
//         glow_color = (red << 16) | (green << 8) | blue;

//         window_draw_circle_simple(win, x, y, r, glow_color);
//     }
// }

// static void draw_electromagnetic_field(t_window *win, t_atom *atom)
// {
//     // Draw field lines around the atom
//     int num_lines = 12;
//     double field_intensity = atom->electromagnetic_field;

//     for (int i = 0; i < num_lines; i++)
//     {
//         double angle = (2.0 * M_PI * i) / num_lines;
//         double field_radius = 200 + 50 * sin(atom->time * 2 + angle);

//         int x1 = atom->center_x + 150 * cos(angle);
//         int y1 = atom->center_y + 150 * sin(angle);
//         int x2 = atom->center_x + field_radius * cos(angle);
//         int y2 = atom->center_y + field_radius * sin(angle);

//         uint32_t field_color = COLOR_FIELD;
//         uint8_t alpha = (uint8_t)(field_intensity * 100);
//         field_color = (field_color & 0x00FFFFFF) | (alpha << 24);

//         window_draw_line_simple(win, x1, y1, x2, y2, field_color);
//     }
// }

// static void draw_atom(t_window *win, t_atom *atom)
// {
//     // Draw electromagnetic field first (background)
//     draw_electromagnetic_field(win, atom);

//     // Draw electron orbital paths (faint)
//     for (int i = 0; i < atom->electron_count; i++)
//     {
//         t_electron *e = &atom->electrons[i];
//         uint32_t orbit_color = 0x404040;
//         window_draw_circle_simple(win, atom->center_x, atom->center_y, e->orbit_radius, orbit_color);
//     }

//     // Draw electron trails
//     for (int i = 0; i < atom->electron_count; i++)
//     {
//         t_electron *e = &atom->electrons[i];
//         for (int j = 0; j < 20; j++)
//         {
//             if (e->trail[j].life > 0)
//             {
//                 double alpha = (double)e->trail[j].life / 20.0;
//                 uint32_t trail_color = e->color;
//                 uint8_t intensity = (uint8_t)(alpha * 150);
//                 trail_color = (trail_color & 0x00FFFFFF) | (intensity << 24);

//                 window_put_pixel(win, e->trail[j].x, e->trail[j].y, trail_color);
//                 e->trail[j].life--;
//             }
//         }
//     }

//     // Draw nucleus with pulsing effect
//     double pulse = atom->nucleus.pulse;
//     draw_glowing_circle(win, atom->nucleus.x, atom->nucleus.y, 25 * pulse, COLOR_NUCLEUS, 0.8);

//     // Draw protons
//     for (int i = 0; i < atom->nucleus.proton_count; i++)
//     {
//         t_particle *p = &atom->nucleus.protons[i];
//         double rotation = atom->nucleus.rotation;
//         int x = atom->nucleus.x + p->x * cos(rotation) - p->y * sin(rotation);
//         int y = atom->nucleus.y + p->x * sin(rotation) + p->y * cos(rotation);

//         draw_glowing_circle(win, x, y, p->size * pulse, p->color, 0.9);
//     }

//     // Draw neutrons
//     for (int i = 0; i < atom->nucleus.neutron_count; i++)
//     {
//         t_particle *p = &atom->nucleus.neutrons[i];
//         double rotation = atom->nucleus.rotation * 0.7; // Slightly different rotation
//         int x = atom->nucleus.x + p->x * cos(rotation) - p->y * sin(rotation);
//         int y = atom->nucleus.y + p->x * sin(rotation) + p->y * cos(rotation);

//         draw_glowing_circle(win, x, y, p->size * pulse, p->color, 0.7);
//     }

//     // Draw electrons with quantum uncertainty
//     for (int i = 0; i < atom->electron_count; i++)
//     {
//         t_electron *e = &atom->electrons[i];

//         // Add quantum fluctuation
//         double uncertainty_x = atom->quantum_fluctuation * (rand() % 10 - 5);
//         double uncertainty_y = atom->quantum_fluctuation * (rand() % 10 - 5);

//         double electron_x = atom->center_x + e->orbit_radius * cos(e->angle + e->phase_offset) + uncertainty_x;
//         double electron_y = atom->center_y + e->orbit_radius * sin(e->angle + e->phase_offset) * cos(e->orbit_tilt) + uncertainty_y;

//         // Size based on energy level
//         int electron_size = 6 + (int)(e->energy_level * 2);
//         draw_glowing_circle(win, electron_x, electron_y, electron_size, e->color, 1.0);

//         // Draw energy level indicator
//         uint32_t energy_color = COLOR_ENERGY;
//         double energy_intensity = e->energy_level / 3.0;
//         if (energy_intensity > 0.3)
//         {
//             window_draw_circle_simple(win, electron_x, electron_y, electron_size + 5, energy_color);
//         }
//     }

//     // Draw energy particles
//     for (int i = 0; i < atom->particle_count; i++)
//     {
//         t_particle *p = &atom->energy_particles[i];
//         double alpha = (double)p->life / p->max_life;
//         uint32_t particle_color = p->color;

//         uint8_t red = ((particle_color >> 16) & 0xFF) * alpha;
//         uint8_t green = ((particle_color >> 8) & 0xFF) * alpha;
//         uint8_t blue = (particle_color & 0xFF) * alpha;
//         particle_color = (red << 16) | (green << 8) | blue;

//         draw_glowing_circle(win, p->x, p->y, p->size * alpha, particle_color, alpha);
//     }
// }

// // In draw_atom_info, print the atom name and show it in the window info box
// static void draw_atom_info(t_window *win, t_atom *atom)
// {
//     // Draw simple text representation of atom info using colored rectangles
//     const char *atom_names[] = {"", "Hydrogen", "Helium", "", "", "", "Carbon"};
//     const char *name = (atom->atom_type <= 6) ? atom_names[atom->atom_type] : "Unknown";

//     // Draw info background
//     int info_x = 10;
//     int info_y = 10;
//     window_draw_rectangle_simple(win, info_x, info_y, 200, 80, 0x333333);

//     // Draw atom name as rectangles (visual label)
//     int name_y = info_y + 5;
//     int name_x = info_x + 40;
//     int name_len = strlen(name);
//     for (int i = 0; i < name_len; ++i)
//         window_draw_rectangle_simple(win, name_x + i * 12, name_y, 10, 14, 0xAAAAFF);

//     // Draw the element symbol pattern
//     if (atom->atom_type == 1)
//     { // H
//         window_draw_line_simple(win, info_x + 10, info_y + 10, info_x + 10, info_y + 30, 0xFFFFFF);
//         window_draw_line_simple(win, info_x + 20, info_y + 10, info_x + 20, info_y + 30, 0xFFFFFF);
//         window_draw_line_simple(win, info_x + 10, info_y + 20, info_x + 20, info_y + 20, 0xFFFFFF);
//     }
//     else if (atom->atom_type == 2)
//     { // He
//         window_draw_rectangle_simple(win, info_x + 10, info_y + 10, 15, 20, 0xFFFFFF);
//     }
//     else if (atom->atom_type == 6)
//     { // C
//         window_draw_line_simple(win, info_x + 20, info_y + 10, info_x + 10, info_y + 10, 0xFFFFFF);
//         window_draw_line_simple(win, info_x + 10, info_y + 10, info_x + 10, info_y + 30, 0xFFFFFF);
//         window_draw_line_simple(win, info_x + 10, info_y + 30, info_x + 20, info_y + 30, 0xFFFFFF);
//     }

//     // Draw proton/neutron/electron count indicators
//     for (int i = 0; i < atom->nucleus.proton_count && i < 10; i++)
//     {
//         window_put_pixel(win, info_x + 50 + i * 3, info_y + 15, COLOR_PROTON);
//     }
//     for (int i = 0; i < atom->nucleus.neutron_count && i < 10; i++)
//     {
//         window_put_pixel(win, info_x + 50 + i * 3, info_y + 25, COLOR_NEUTRON);
//     }
//     for (int i = 0; i < atom->electron_count && i < 10; i++)
//     {
//         window_put_pixel(win, info_x + 50 + i * 3, info_y + 35, COLOR_ELECTRON);
//     }

//     // Print the atom name in the terminal for debug
//     printf("Atom info: %s\n", name);
// }

// // Add this function to cycle atom type at runtime
// static void cycle_atom_type(t_atom *atom, int width, int height)
// {
//     // Supported atom types: 1 (Hydrogen), 2 (Helium), 6 (Carbon)
//     int next_type;
//     if (atom->atom_type == 1)
//         next_type = 2;
//     else if (atom->atom_type == 2)
//         next_type = 6;
//     else
//         next_type = 1;
//     init_atom(atom, next_type, width / 2, height / 2);
// }

// Rename your main to avoid conflict:
// In atom_demo_main, use MLX event loop and fix ESC handling and animation speed:
// int atom_demo_main(int argc, char **argv)
// {
//     printf("=== Atomic Structure Simulator ===\n");

//     int width = 1200;
//     int height = 800;
//     int atom_type = 6; // Default to Carbon

//     for (int i = 1; i < argc; i++)
//     {
//         if (strcmp(argv[i], "-w") == 0 && i + 1 < argc)
//             width = atoi(argv[++i]);
//         else if (strcmp(argv[i], "-h") == 0 && i + 1 < argc)
//             height = atoi(argv[++i]);
//         else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc)
//             atom_type = atoi(argv[++i]);
//         else if (strcmp(argv[i], "--help") == 0)
//         {
//             printf("Usage: %s [-w width] [-h height] [-a atom_type]\n", argv[0]);
//             printf("  -a 1  : Hydrogen atom\n");
//             printf("  -a 2  : Helium atom\n");
//             printf("  -a 6  : Carbon atom\n");
//             printf("  (You can add more atoms by extending init_atom)\n");
//             return 0;
//         }
//     }

//     srand(time(NULL));

//     t_window *window = window_new(width, height, "Atomic Structure Simulator", 0x000011);
//     if (!window)
//     {
//         printf("❌ Failed to create window\n");
//         return 1;
//     }

//     t_atom atom;
//     init_atom(&atom, atom_type, width / 2, height / 2);

//     // Key event handler for atom switching and quit
//     int atom_key_hook(int keycode, void *param)
//     {
//         t_atom *atom = (t_atom *)param;
//         if (keycode == 'n' || keycode == 'N')
//         {
//             printf("Switching atom type...\n");
//             cycle_atom_type(atom, width, height);
//         }
//         // ESC or 'q' to quit
//         if (keycode == 65307 || keycode == 'q' || keycode == 'Q')
//         {
//             window->should_close = true;
//             // Also call mlx_loop_end if available (for newer MLX)
// #ifdef HAS_MLX_LOOP_END
//             mlx_loop_end(window->mlx_ptr);
// #endif
//         }
//         return 0;
//     }

//     // Animation loop callback for MLX (slower speed)
//     int atom_anim_loop(void *param)
//     {
//         t_atom *atom = (t_atom *)param;
//         static struct timespec last = {0, 0};
//         struct timespec now;
//         double elapsed;

//         // Limit to ~60 FPS
//         clock_gettime(CLOCK_MONOTONIC, &now);
//         elapsed = (now.tv_sec - last.tv_sec) + (now.tv_nsec - last.tv_nsec) / 1e9;
//         if (elapsed < 0.016)
//             return 0;
//         last = now;

//         if (!window->should_close)
//         {
//             update_atom(atom);
//             window_clear(window);
//             draw_atom(window, atom);
//             draw_atom_info(window, atom);
//             window_render(window);
//         }
//         return 0;
//     }

//     mlx_hook(window->win_ptr, 2, 1L << 0, atom_key_hook, &atom);
//     mlx_loop_hook(window->mlx_ptr, atom_anim_loop, &atom);

//     printf("✅ Atomic simulator initialized\n");
//     printf("🔬 Simulating %s atom\n",
//            atom_type == 1 ? "Hydrogen" : atom_type == 2 ? "Helium"
//                                      : atom_type == 6   ? "Carbon"
//                                                         : "Unknown");
//     printf("⚛️  Protons: %d, Neutrons: %d, Electrons: %d\n",
//            atom.nucleus.proton_count, atom.nucleus.neutron_count, atom.electron_count);

//     // Use MLX event loop for input and animation
//     mlx_loop(window->mlx_ptr);

//     printf("👋 Simulation ended\n");
//     window_destroy(window);
//     return 0;
// }
