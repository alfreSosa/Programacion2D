//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include "include/examples.h"
#include <iostream>

void TestGLFW3_V2()
{
    SCREEN.Open(800, 600, false);
  
    while (SCREEN.IsOpened())
    {
        SCREEN.ProcessScreenInput();
        RENDER.Clear(0.2f, 0.3f, 0.3f);

        SCREEN.Refresh();

    }
    glfwTerminate();
}

int main(int argc, char* argv[]) 
{
    TestGLFW3_V2();
    return 0;
}