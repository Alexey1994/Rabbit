#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED


#include "../../interfaces/ports/ports.h"


Byte get_time_seconds();
Byte get_time_minutes();
Byte get_time_hours();

void print_date();


#include "time.c"

#endif //TIME_H_INCLUDED