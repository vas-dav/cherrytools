#include <stdio.h>
#include "../cherrylog.h"

int main()
{
    CHERRY_INFO("Start of main in log examples");
    CHERRY_WARNING("Get a warn");
    CHERRY_ERROR("This is it!");
        
    return 0;
}
