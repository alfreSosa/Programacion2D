# 2DProgramming
In this project you can find a 2D engine. This was developed in C++ and OpenGL.

To execute it you can open the Visual Studio(2013) Solution and launch the project. Then a command promt window 
will open with a message. You have to enter the number of with example you want to test.

In the main function there are eleven examples to test the right funcionality of the engine. Some solutions have 
several examples what running in differents windows.

-----------------
03/01/2022
-----------------

- Update reference to abs from #include <cmath> to avoid warning about abs implementation with double
- Added legacy_stdio_definitions.lib to the properties/linker/input to remove "unresolved external symbol __imp__fprintf"
- Updating glfw2 to glfw3
