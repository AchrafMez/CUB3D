#include "cub3.h"

 int main(int ac, char **av)
 {
	t_data	data;
     if(ac == 2)
     {
         if(check_extension(av[1]))
         {
             t_map *map = malloc(sizeof(t_map));
             if(!map)
                 return 1;
             null_init(map);
             // printf("correct");
             read_map(av[1], &map);
             check_filled_map(map);
             check_map_chars(map->map);
             WHXY(&map);
             check_map_spaces(map);
			 data.map = map;
             // if(map->map) {
 //               check_map_walls(map->map);
             //    }
			 raycast(&data);
             print_map(map);
             free_map(map);
         }
         else
             printf("Uncorrect filename\n");

     //    atexit(leak);
     }
     return 0;
 }
