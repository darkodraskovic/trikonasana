#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>

extern float msPerUpdate;
extern SDL_Event TRI_event;

void Tri_RunApp();

// callbacks
void start(void);
void input(void);
void update(void);
void draw(void);
void stop(void);

#endif /* APPLICATION_H */
