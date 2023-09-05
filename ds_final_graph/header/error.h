#ifndef __ERROR__H__
#define __ERROR__H__

#include<time.h>
#include<stdio.h>

//////////////////// .................... ERROR OPERATION :: WRITE ERROR INTO ERROR LOGFILE .................... ////////////////////




/**
 * Write the error message into the error.log
 * 
 * @param error_message enter the error message that you want to deliver " Error occured : Reason ~ " 
*/
void writeErrorLog(const char* error_message)
{
    FILE* file = fopen("error.log", "a");
    if(file == NULL)
    {
        printf("Failed to open error.log file.\n");
        return;
    }

    time_t happan_time;
    struct tm* time_info;
    time(&happan_time);
    time_info = localtime(&happan_time);
    char time_string[20];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);
    fprintf(file, "[%s] %s\n", time_string, error_message);

    fclose(file);

}



#endif /*__ERROR__H__*/