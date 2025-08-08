#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

t_particle_transition g_particle_system = {
	0, // frame
	PARTICLE_TRANSITION_FRAMES, // max_frames
	false, // active
	PARTICLE_NONE, // current_type
	PARTICLE_NONE, // target_type
	// particles
	{
		{ .x = 0, .y = 0, .z = 0, .vx = 0, .vy = 0, .vz = 0, .size = 0, .color = 0, .lifetime = 0, .active = false }
	},
	false, // initialized
	0.0f // time_accumulator
};

// Initialize a single particle based on type
static void init_particle(t_particle *p, t_particle_type type, t_app *fdf)
{
	(void)fdf; // Unused parameter
	static bool seeded = false;
	if (!seeded) {
		srand((unsigned int)time(NULL));
		seeded = true;
	}
	
	p->active = true;
	p->lifetime = PARTICLE_LIFETIME + (rand() % 100);
	
	switch (type)
	{
		case PARTICLE_SNOW:
			particle_snow(p);
			break;
			
		case PARTICLE_RAIN:
			particle_rain(p);
			break;
			
		case PARTICLE_FIRE:
			particle_fire(p);
			break;
			
		case PARTICLE_SPARKS:
			particle_sparks(p);
			break;
			
		case PARTICLE_STARS:
			particle_stars(p);
			break;
			
		case PARTICLE_BUBBLES:
			particle_bubbles(p);
			break;
			
		case PARTICLE_DUST:
			particle_dust(p);
			break;
			
		case PARTICLE_SMOKE:
			particle_smoke(p);
			break;
			
		default:
			p->active = false;
			break;
	}
}

// Update particle physics
static void update_particle(t_particle *p, t_particle_type type)
{
	if (!p->active)
		return;
		
	// Update position
	p->x += p->vx;
	p->y += p->vy;
	p->z += p->vz;
	
	// Apply type-specific physics
	switch (type)
	{
		case PARTICLE_FIRE:
		case PARTICLE_SMOKE:
			// Gravity and fade
			p->vy -= 0.1f;
			p->size *= 0.998f;
			break;
			
		case PARTICLE_SPARKS:
			// Gravity
			p->vy += 0.2f;
			p->size *= 0.995f;
			break;
			
		case PARTICLE_BUBBLES:
			// Buoyancy
			p->vy -= 0.05f;
			break;
			
		case PARTICLE_DUST:
			// Slow drift
			p->vx *= 0.999f;
			p->vy *= 0.999f;
			break;
			
		default:
			break;
	}
	
	// Decrease lifetime
	p->lifetime--;
	if (p->lifetime <= 0)
		p->active = false;
	
	// Remove particles that go off screen
	if (p->x < -50 || p->x > WIN_WIDTH + 50 || 
		p->y < -50 || p->y > WIN_HEIGHT + 50)
		p->active = false;
}

// Render particles to screen
static void render_particles(t_app *fdf)
{
	uint32_t *screen = (uint32_t *)fdf->renderer.data;
	
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		t_particle *p = &g_particle_system.particles[i];
		if (!p->active)
			continue;
			
		// Simple particle rendering
		int px = (int)p->x;
		int py = (int)p->y;
		int size = (int)p->size + 2; // Make particles bigger for visibility
		
		for (int dy = 0; dy < size; dy++)
		{
			for (int dx = 0; dx < size; dx++)
			{
				int x = px + dx;
				int y = py + dy;
				
				if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
				{
					// Make particles much more visible - no alpha blending for now
					uint32_t color = p->color;
					
					// Force bright white for snow to make it super visible
					if (g_particle_system.current_type == PARTICLE_SNOW)
						color = 0xFFFFFF;
					
					// Directly set the color without blending
					screen[y * WIN_WIDTH + x] = color;
				}
			}
		}
	}
}

// Spawn new particles
static void spawn_particles(t_particle_type type, t_app *fdf)
{
	// Spawn rate depends on particle type
	int spawn_rate = 3;
	switch (type)
	{
		case PARTICLE_SPARKS: spawn_rate = 5; break;
		case PARTICLE_RAIN: spawn_rate = 8; break;
		case PARTICLE_SNOW: spawn_rate = 4; break;
		case PARTICLE_FIRE: spawn_rate = 6; break;
		case PARTICLE_STARS: spawn_rate = 1; break;
		default: break;
	}
	
	for (int i = 0; i < spawn_rate; i++)
	{
		// Find inactive particle slot
		for (int j = 0; j < MAX_PARTICLES; j++)
		{
			if (!g_particle_system.particles[j].active)
			{
				init_particle(&g_particle_system.particles[j], type, fdf);
				break;
			}
		}
	}
}

// Main particle system update
void particles_update(t_app *fdf)
{
	// Only update if system is active
	if (!g_particle_system.active && g_particle_system.current_type == PARTICLE_NONE)
		return;
	
	// Initialize if needed
	if (!g_particle_system.initialized)
	{
		for (int i = 0; i < MAX_PARTICLES; i++)
			g_particle_system.particles[i].active = false;
		g_particle_system.initialized = true;
	}
	
	// Handle transitions
	if (g_particle_system.active)
	{
		g_particle_system.frame++;
		if (g_particle_system.frame >= g_particle_system.max_frames)
		{
			g_particle_system.active = false;
			g_particle_system.frame = 0;
			g_particle_system.current_type = g_particle_system.target_type;
		}
	}
	
	// Update existing particles
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		update_particle(&g_particle_system.particles[i], g_particle_system.current_type);
	}
	
	// Spawn new particles if system is active
	if (g_particle_system.current_type != PARTICLE_NONE)
	{
		g_particle_system.time_accumulator += 1.0f;
		if (g_particle_system.time_accumulator >= 3.0f) // Spawn more frequently
		{
			spawn_particles(g_particle_system.current_type, fdf);
			g_particle_system.time_accumulator = 0.0f;
		}
	}
	
	// Render particles LAST to ensure they appear on top
	render_particles(fdf);
}

// Start particle transition (circular buffer)
void transition_start_particles(bool to_particles)
{
	(void)to_particles; // Unused parameter
	
	// Initialize if not done yet
	if (!g_particle_system.initialized)
	{
		for (int i = 0; i < MAX_PARTICLES; i++)
			g_particle_system.particles[i].active = false;
		g_particle_system.initialized = true;
	}
	
	// Cycle through particle types in circular buffer manner
	t_particle_type next_type = (g_particle_system.current_type + 1) % PARTICLE_COUNT;
	
	g_particle_system.active = true;
	g_particle_system.frame = 0;
	g_particle_system.target_type = next_type;
	
	const char *particle_names[] = {
		"None", "Snow", "Rain", "Fire", "Sparks", "Stars", "Bubbles", "Dust", "Smoke"
	};
	
	ft_printf("Particle system transitioning to: %s\n", particle_names[next_type]);
	
	// Immediately spawn some particles for instant feedback
	if (next_type != PARTICLE_NONE)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < MAX_PARTICLES; j++)
			{
				if (!g_particle_system.particles[j].active)
				{
					init_particle(&g_particle_system.particles[j], next_type, NULL);
					break;
				}
			}
		}
	}
}

// Check if particle system is active
bool particles_is_active(void)
{
	return g_particle_system.active || g_particle_system.current_type != PARTICLE_NONE;
}

