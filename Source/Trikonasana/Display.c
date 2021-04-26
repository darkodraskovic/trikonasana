#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#include "Display.h"
#include "Color.h"

void initBuffers();

Texture2D renderTexture;

color_t* renderBuffer = NULL;
color_t* clearBuffer = NULL;

int windowWidth = 640;
int windowHeight = 400;
int pixelSize = 2;

size_t bufferSize;
size_t pitch;

Mat4 TRI_projectionMatrix;
Mat3 TRI_screenMatrix;

void Tri_InitDisplay() {
    // init window
    InitWindow(windowWidth * pixelSize, windowHeight * pixelSize, "Trikonasana - CPU renderer");    
    SetTargetFPS(60);
    
    // init buffers
    bufferSize = windowWidth * windowHeight * sizeof(color_t);
    pitch = windowWidth * sizeof(color_t);

    renderBuffer = (color_t*)malloc(sizeof(color_t) * windowWidth * windowHeight);
    clearBuffer = (color_t*)malloc(sizeof(color_t) * windowWidth * windowHeight);
    Tri_SetClearColor(0xFF000000);

    Image image = GenImageColor(windowWidth, windowHeight, BLACK);
    renderTexture = LoadTextureFromImage(image);

    // init matrices
    TRI_projectionMatrix = mat4Perspective(PI / 3, (float)windowHeight / windowWidth, 0.1, 100);
    TRI_screenMatrix = mat3Screen(windowWidth, windowHeight);
};

void Tri_SetClearColor(color_t color) {
    int i = 0;
    while (i < windowWidth * windowHeight) clearBuffer[i++] = color;
}

void Tri_Render(void) {
    UpdateTexture(renderTexture, renderBuffer);
    
    BeginDrawing();
    DrawTextureEx(renderTexture, (Vector2){0,0}, 0, pixelSize, WHITE);
    EndDrawing();

    memcpy(renderBuffer, clearBuffer, bufferSize);
}

void Tri_DestroyDisplay() {
    free(renderBuffer);
    free(clearBuffer);

    CloseWindow();
}
