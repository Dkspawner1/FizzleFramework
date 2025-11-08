

#include <stdlib.h>
#include <time.h>

#include "Core/Application.h"
#include "Core/Logger.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Logger_Initialize(LOG_DEBUG);

    Application application = Application_Create();
    Application_Initialize(&application);
    Application_LoadAssets(&application);
    Application_Run(&application);
    Application_Destroy(&application);
    Logger_Shutdown();

    return EXIT_SUCCESS;
}
