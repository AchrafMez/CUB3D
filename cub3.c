#include "cub3.h"
#include <string.h>

int check_extension(char *file_name){
    
    const char extension[5]= ".cub";
    int check_counter = 3;
    int file_counter = strlen(file_name) - 1;
    while(check_counter >= 0 && extension[check_counter])
    {
        if(file_name[file_counter--] != extension[check_counter--])
            return 0;
    }
    return 1;
}



int main(int ac, char **av){

    if(ac == 2)
    {
        if(check_extension(av[1]))
        {
            printf("correct");
        }
        else
            printf("uncorrect");
    }
}