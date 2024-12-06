#include "cub3.h"
#include <string.h>

int check_extension(char *file_name){
    
    char extension[4]= ".cub";
    int check_counter = 3;
    int file_counter = 0;
    while(file_name[file_counter])
        file_counter++;
    file_counter--;
    while(file_name[file_counter && extension[check_counter]] && extension[check_counter] > 0 && file_name[file_counter] > 0)
    {
        if(file_name[file_counter] != extension[check_counter])
        {
            printf("uncorrect extension\n");
            return 0;
        }
        file_counter--;
        check_counter--;
    }
    printf("f: %c e: %c\n", file_name[file_counter], extension[check_counter]);
    printf("correct extension\n");
    return 1;
}

int main(int ac, char **av){

    if(ac == 2)
    {
        char *file = av[1];
        // printf("%s\n", file);
        check_extension(file);
    }
}