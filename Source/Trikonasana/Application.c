#include "raylib.h"

#include "Display.h"
#include "Application.h"

void Tri_RunApp(){
    Tri_InitDisplay();
    start();

    while (!WindowShouldClose()) {
        input();

        update();

        draw();
        Tri_Render();
    }

    stop();
    Tri_DestroyDisplay();
}
