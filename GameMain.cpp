#include "Application.h"
#include <iostream>

using namespace Roguelike;

int main()
{
    try
    {
        Application& app = Application::Instance();
        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}