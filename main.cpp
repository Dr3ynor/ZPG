#include <vector>
#include "Application.h"

// RUZ0096

// argv = array of arguments, accepting only one for now (sceneParam)
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Expecting one argument (integer sceneParam)!\n");
        return 0;
    }

    if (argc > 2)
    {
        printf("Accepting only one argument (integer sceneParam)!\n");
        return 0;
    }

    int sceneParam = atoi(argv[1]);
    printf("Argument sceneParam=%d\n", sceneParam);

    Application *app = new Application(sceneParam);

    app->run();

    delete app;
    return 0;
}
