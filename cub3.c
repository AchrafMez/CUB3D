#include "cub3.h"

void leak()
{
	system("leaks cub3D");
}
 int main(int ac, char **av)
 {
	t_data	data;
     if(ac == 2)
     {
         if(check_extension(av[1]))
         {
             t_map *map = malloc(sizeof(t_map));
             if(!map)
                 return (free_map(map), EXIT_FAILURE);
             null_init(map);
             read_map(av[1], &map);
             check_filled_map(map);
             check_map_chars(map);
             WHXY(&map);
             check_map_spaces(map);
			 data.map = map;
			 if (raycast(&data))
			 	return (free_map(map), EXIT_FAILURE);
             free_map(map);
         }
         else
             printf("Uncorrect filename\n");
        atexit(leak);
     }
     return 0;
 }
