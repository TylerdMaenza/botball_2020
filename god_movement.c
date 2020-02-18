#include <stdio.h>
#include <stdarg.h>

void Drive(){}
int servo_change(const char* pointer, ...)
{
    va_list mov_type;
    va_start(mov_type, pointer);
 
    while (*pointer != '\0') {
        if (*pointer == 'd' || *pointer == 'D') {
            int drive_type = va_arg( args, int);
            ++pointer;
            int var1 = va_arg(args, int );
            ++pointer;
            int var2 = va_arg( args, int );
            switch(drive_type)
            {
                case 1:
                {
                    //DRIVE(var1, var2);
                }
                case 2:
                {
                    //SQUARE_UP(var1, var2);
                }
                case 3:
                {
                    //TURN(var1, var2);
                }
            }
        
        //DRIVE
        //SQUARE_UP
        //TURN

    }
    va_end(args);
}