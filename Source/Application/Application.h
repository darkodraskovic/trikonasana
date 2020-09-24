#ifndef APPLICATION_H
#define APPLICATION_H

extern float msPerUpdate;

void initApp();
void runApp();
void processInput(void);

// callbacks
void start(void);
void input(void);
void update(void);
void draw(void);
void stop(void);

#endif /* APPLICATION_H */
