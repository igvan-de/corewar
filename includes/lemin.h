/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lemin.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: igvan-de <igvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 15:16:29 by igvan-de       #+#    #+#                */
/*   Updated: 2020/02/28 12:46:35 by igvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define CURRENT_PATH_ROOM_LINKS get_last_room->room->links
# define PATH_ID (*path)->room->path_id
# define CONNECTED_ROOM_PATH_ID connected->room->path_id
# define CONNECTED_SHIFT connected->shift

typedef enum			e_object_type
{
	FREE = 0,
	START = 1,
	END = 2,
	ANT = 3,
	USELESS = 4
}						t_object_type;

typedef enum			e_node_value
{
	NAME = 0,
	X = 1,
	Y = 2,
	A = 0,
	B = 1,
	NOT_FOUND = 0,
	FOUND = 1,
	EXISTING = 2,
	OFF = 0,
	ON = 1
}						t_node_value;

typedef struct			s_save_map
{
	char				*line;
	struct s_save_map	*next;
}						t_save_map;

typedef struct			s_path_set
{
	long				path_size;
	struct s_path		*path;
	struct s_path_set	*next;
}						t_path_set;

typedef struct			s_path
{
	struct s_rooms		*room;
	struct s_path		*next;
	struct s_path		*previous;
}						t_path;

typedef struct			s_queue
{
	struct s_rooms		*room;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_data
{
	short				found_start;
	short				found_end;
	unsigned int		amount_ants_start;
	unsigned int		turns;
	size_t				size;
	struct s_rooms		*end_room;
	struct s_rooms		*start_room;
}						t_data;

typedef	struct			s_input
{
	char				*name;
	int					x;
	int					y;
	short				start;
	short				end;
	struct s_input		*next;
}						t_input;

typedef struct			s_links
{
	short				end;
	short				shift;
	struct s_rooms		*room;
	struct s_links		*next;
}						t_links;

typedef struct			s_rooms
{
	char				*name;
	int					distance;
	int					path_id;
	short				visited;
	unsigned int		ant_id;
	t_object_type		type;
	struct s_links		*links;
	struct s_rooms		*from;
	struct s_rooms		*towards;
	struct s_rooms		*branch;
	struct s_rooms		*next;
}						t_rooms;

/*
**===============================ANTS FUNCTIONS=================================
*/
unsigned int			calc_turn_amount(t_data *data, t_path_set *paths);
void					send_ants(t_data **data, t_path_set **paths);
void					get_ants(t_data **ants, t_save_map *map);

/*
**===============================FORMAT FUNCTIONS===============================
*/
bool					check_if_command(char *line, t_data **ants);
bool					check_format_room(char *line, t_data **ants);
bool					check_format_link(char *line, t_input **rooms);
bool					check_if_ants(char *line);
bool					space_counter(char *line, int i, int space_count);
bool					dash_counter(char *line, int i, int dash_count);
void					is_start_or_end(char *line, t_data **ants);
void					no_whitespaces(char *line);
void					error_check(int ret);

/*
**===============================LIST FUNCTIONS=================================
*/
void					add_to_list(char *line, t_input **head, t_data **data);

/*
**===============================HASHTABLE FUNCTIONS============================
*/
size_t					hash_function(unsigned char *str, size_t size);
void					hash_table(t_rooms **table, t_input *input,
						t_data **data);

/*
**===============================LINK FUNCTIONS=================================
*/
int						compare_with_rooms(char **a_b, t_input **input);
char					**lem_split(char *line, t_input **input);
char					**ft_split(char *line, int n, int c);
void					get_links(t_input **input, t_rooms **rooms,
						t_save_map *map, t_data *data);
void					set_links(t_rooms **rooms,
						size_t size, char *name_a, char *name_b);

/*
**===============================BFS FUNCTIONS==================================
*/
bool					bfs(t_rooms **rooms, t_data *data);
void					create_queue(t_queue **queue);
void					add_to_queue(t_queue **queue, t_queue *new);
void					pop_out_queue(t_queue **queue);
t_queue					*create_start(t_data *data);
t_queue					*create_end(t_data *data);
t_queue					*new_element(t_rooms *room);

/*
**===============================PATH FUNCTIONS=================================
*/
bool					calculate_path(t_path_set *old_path_set,
						t_path_set **best_path_set, t_data *data);
bool					set_link_shifts(t_links *connected,
						int current_distance, t_rooms **room);
bool					set_branch_shifts(t_links *connected, t_rooms **room);
void					create_paths_and_send_ants(t_rooms **rooms,
						t_data *data);
void					save_paths(t_path_set **path_set, t_path_set *path);
void					reset_path_ids(t_rooms **table, size_t size);
void					reset_link_value(t_path **start);
void					follow_shifts(t_path **path, t_path_set *set);
void					follow_bfs(t_rooms **room);
void					add_to_path(t_path **path,
						t_path *new_room, t_path_set *set);
void					set_link_shift(t_rooms **room,
						t_rooms **connected_room);
bool					check_paths(t_path_set **path_set);
t_path					*new_room_to_path(t_rooms *room);

/*
**===============================FREE FUNCTIONS=================================
*/
void					free_queue(t_queue **queue);
void					free_input(t_input **input);
void					free_set(t_path_set **path);
void					free_path(t_path **path);
void					free_path_set(t_path_set **set);
void					free_links(t_links **links);
void					free_rooms(t_rooms **rooms);
void					free_table(t_rooms **rooms, t_data *data);


/*
**==============================ERROR FUNCTIONS=================================
*/
void					no_path(t_data *data);
void					input_check(t_data *data);
void					ants_amount_check(int amount_ants);
void					bad_input(void);
void					max_int_error(void);

/*
**==============================PRINT FUNCTIONS=================================
*/
void					print_map(t_save_map *map);

/*
**==============================ADDITIONAL FUNCTIONS============================
*/
int						debug_main(int argc, char **argv);
void					print_input(t_input *rooms, t_data **ants);
void					print_hash(t_rooms **table, size_t size);
void					print_queue(t_queue *queue);
void					print_path_set(t_path_set *path_set);
void					print_path(t_path *path);

#endif
