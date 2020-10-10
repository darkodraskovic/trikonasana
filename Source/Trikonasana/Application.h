#ifndef APPLICATION_H
#define APPLICATION_H

extern float msPerUpdate;

void Tri_RunApp();

// callbacks
void start(void);
void input(void);
void update(void);
void draw(void);
void stop(void);

#endif /* APPLICATION_H */
