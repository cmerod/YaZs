/* This code was collected from https://rosettacode.org/wiki/A*_search_algorithm on 17-05-2018
The page was last modified on 25 April 2018, at 17:00 when code was collected.
Content is available under GNU Free Documentation License 1.2 unless otherwise noted.
Modifications to suit the game has been made*/
#include "Pathing.h"

Pathfinder pathing_init()
{
	Pathfinder pathfinder = {
		.p_len = 0,
		.path = NULL,
		.c_len = 0,
		.closed = NULL,
		.o_len = 1,
		.open = (int*)calloc(pathfinder.o_len, sizeof(int)),
		.player_node = -1,
		.enemy_node = -1,
	};
	return pathfinder;
}

void pathing_search(Pathfinder *pathfinder, Level *level, int player_node, int enemy_node)
{
	int i, j, k, l;

	// index of start stop 
	int s = enemy_node;
	// index of finish stop
	int e = player_node;
	pathfinder->player_node = player_node;
	pathfinder->enemy_node = enemy_node;

	for (i = 0; i < level->s_len; i++) {
		level->stops[i].h = sqrt(pow(level->stops[e].row - level->stops[i].row, 2) 
			+ pow(level->stops[e].col - level->stops[i].col, 2));
	}

	pathfinder->open[0] = s;
	level->stops[s].g = 0;
	level->stops[s].f = level->stops[s].g + level->stops[s].h;
	int found = 0; 
	double min, tempg; 
	int b, current;	

	while (pathfinder->o_len and not found) { 
		min = DBL_MAX;

		for (i = 0; i < pathfinder->o_len; i++) {
			if (level->stops[pathfinder->open[i]].f < min) {
				current = pathfinder->open[i];
				min = level->stops[pathfinder->open[i]].f;
			}
		}

		if (current == e) {
			found = 1;

			++pathfinder->p_len;
			pathfinder->path = (int*)realloc(pathfinder->path, pathfinder->p_len * sizeof(int));
			pathfinder->path[pathfinder->p_len - 1] = current;
			while (level->stops[current].from >= 0) {
				current = level->stops[current].from;
				++pathfinder->p_len;
				pathfinder->path = (int*)realloc(pathfinder->path, pathfinder->p_len * sizeof(int));
				pathfinder->path[pathfinder->p_len - 1] = current;
			}
		}

		for (i = 0; i < pathfinder->o_len; i++) {
			if (pathfinder->open[i] == current) {
				if (i not_eq (pathfinder->o_len - 1)) {
					for (j = i; j < (pathfinder->o_len - 1); j++) {
						pathfinder->open[j] = pathfinder->open[j + 1];
					}
				}
				--pathfinder->o_len;
				pathfinder->open = (int*)realloc(pathfinder->open, pathfinder->o_len * sizeof(int));
				break;
			}
		}

		++pathfinder->c_len;
		pathfinder->closed = (int*)realloc(pathfinder->closed, pathfinder->c_len * sizeof(int));
		pathfinder->closed[pathfinder->c_len - 1] = current;

		for (i = 0; i < level->stops[current].n_len; i++) {
			b = 0;

			for (j = 0; j < pathfinder->c_len; j++) {
				if (level->routes[level->stops[current].n[i]].y == pathfinder->closed[j]) { 
					b = 1;
				}
			}

			if (b) {
				continue;
			}

			tempg = level->stops[current].g + level->routes[level->stops[current].n[i]].d;

			b = 1;

			if (pathfinder->o_len > 0) {
				for (j = 0; j < pathfinder->o_len; j++) {
					if (level->routes[level->stops[current].n[i]].y == pathfinder->open[j]) {
						b = 0;
					}
				}
			}

			if (b or (tempg < level->stops[level->routes[level->stops[current].n[i]].y].g)) {
				level->stops[level->routes[level->stops[current].n[i]].y].from = current;
				level->stops[level->routes[level->stops[current].n[i]].y].g = tempg;
				level->stops[level->routes[level->stops[current].n[i]].y].f = 
					level->stops[level->routes[level->stops[current].n[i]].y].g 
					+ level->stops[level->routes[level->stops[current].n[i]].y].h;

				if (b) {
					++pathfinder->o_len;
					pathfinder->open = (int*)realloc(pathfinder->open, pathfinder->o_len * sizeof(int));
					pathfinder->open[pathfinder->o_len - 1] = level->routes[level->stops[current].n[i]].y;
				}
			}
		}

	}
	
}

void pathing_free_routes(Level *level)
{
	for (int i = 0; i < level->s_len; ++i) {
		free(level->stops[i].n);
	}
	free(level->stops);
	free(level->routes);
}

void pathing_free_path(Pathfinder *pathfinder)
{
	free(pathfinder->path);
	free(pathfinder->open);
	free(pathfinder->closed);
}
