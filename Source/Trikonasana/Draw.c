#include "Draw.h"

#include <math.h>

#include "Trikonasana/Color.h"
#include "Trikonasana/Display.h"
#include "Trini/Vector.h"

void swapInt(int* n1, int* n2) {
  int tmp = *n1;
  *n1 = *n2;
  *n2 = tmp;
}

void swapFloat(float* n1, float* n2) {
  float tmp = *n1;
  *n1 = *n2;
  *n2 = tmp;
}

void swapVec2f(Vec2f* a, Vec2f* b) {
  Vec2f tmp = *a;
  *a = *b;
  *b = tmp;
}

void swapVec3f(Vec3f* a, Vec3f* b) {
  Vec3f tmp = *a;
  *a = *b;
  *b = tmp;
}

void swapVec4f(Vec4f* a, Vec4f* b) {
  Vec4f tmp = *a;
  *a = *b;
  *b = tmp;
}

/*      A
       / \
      /   \
     /     \
    /       \
   /    P    \
  /           \
 /             \
B______________ C   */

Vec3f getBarycentric(Vec2f a, Vec2f b, Vec2f c, Vec2f p) {
  Vec2f ab = vec2fSub(b, a);
  Vec2f ac = vec2fSub(c, a);
  Vec2f bc = vec2fSub(c, b);
  Vec2f ap = vec2fSub(p, a);
  Vec2f bp = vec2fSub(p, b);

  float abc = ab.x * ac.y - ab.y * ac.x;
  if (!abc) abc += 10e-3;  // prevent div by 0
  float alpha = (bc.x * bp.y - bc.y * bp.x) / abc;
  float beta = (ap.x * ac.y - ap.y * ac.x) / abc;

  return (Vec3f){alpha, beta, 1 - alpha - beta};
}

// PIXEL

void Tri_DrawPixel(int x, int y, color_t color) {
  if (x > -1 && x < windowWidth && y > -1 && y < windowHeight)
    renderBuffer[windowWidth * y + x] = color;
}

void Tri_DrawTexel(int x, int y, Vec4f a, Vec4f b, Vec4f c, Vec2f uv0,
                   Vec2f uv1, Vec2f uv2, Tri_Texture* texture) {
  Vec3f weights = getBarycentric((Vec2f){a.x, a.y}, (Vec2f){b.x, b.y},
                                 (Vec2f){c.x, c.y}, (Vec2f){x, y});

  float A = weights.x * b.w * c.w;
  float B = weights.y * a.w * c.w;
  float C = weights.z * a.w * b.w;
  float D = (A + B + C);
  if (!D) D += 10e-3;  // prevent div by 0
  float u = (uv0.x * A + uv1.x * B + uv2.x * C) / D;
  float v = (uv0.y * A + uv1.y * B + uv2.y * C) / D;

  int texX = u * texture->width;
  int texY = v * texture->height;

  Tri_DrawPixel(x, y, texture->data[texY * texture->width + texX]);
}

// LINE

void Tri_DrawLineHorizontal(int x0, int y0, int x1, color_t color) {
  // if off-screen do nothing
  if (y0 < 0 || y0 >= windowHeight) return;
  if (x0 > x1) swapInt(&x0, &x1);
  if (x0 > windowWidth || x1 < 0) return;

  // clamp horizontally
  if (x0 < 0) x0 = 0;
  if (x1 >= windowWidth) x1 = windowWidth - 1;

  int idx = windowWidth * y0 + x0;
  int end = windowWidth * y0 + x1;
  while (idx <= end) renderBuffer[idx++] = color;
}

void Tri_DrawLine(int x0, int y0, int x1, int y1, color_t color) {
  int deltaX = x1 - x0;
  int deltaY = y1 - y0;

  float sideLen = abs(deltaX) > abs(deltaY) ? abs(deltaX) : abs(deltaY);

  float incX = deltaX / sideLen;
  float curX = x0;
  float incY = deltaY / sideLen;
  float curY = y0;

  for (int i = 0; i < sideLen; ++i) {
    Tri_DrawPixel(curX, curY, color);
    curX += incX;
    curY += incY;
  }
}

// TRIANGLE

void Tri_DrawTri(int x0, int y0, int x1, int y1, int x2, int y2,
                 color_t color) {
  Tri_DrawLine(x0, y0, x1, y1, color);
  Tri_DrawLine(x1, y1, x2, y2, color);
  Tri_DrawLine(x2, y2, x0, y0, color);
}

/* positive y points downwards
        (x0,y0)
          /\
         /  \
   (x1,y1)--(Mx,My) */
void drawFlatBottom(int x0, int y0, int x1, int y1, int Mx, int My,
                    color_t color) {
  // reciprocal slope (inverse) because we derive delta x from delta y (== 1)
  float m1 = (float)(x1 - x0) / (y1 - y0);
  float m2 = (float)(Mx - x0) / (My - y0);
  float xStart = x0, xEnd = x0;
  for (int y = y0; y <= y1; y++) {  // loop scanlines from top to bottom
    Tri_DrawLineHorizontal(xStart, y, xEnd, color);
    xStart += m1;
    xEnd += m2;
  }
}

// (x1, y1)--(Mx, My)
//      \  /
//       \/
//    (x2,y2)
void drawFlatTop(int x1, int y1, int Mx, int My, int x2, int y2,
                 color_t color) {
  float m1 = (float)(x1 - x2) / (y1 - y2);  // reciprocal slope: dx / dy
  float m2 = (float)(Mx - x2) / (My - y2);
  float xStart = x2, xEnd = x2;
  for (int y = y2; y >= y1; y--) {  // loop scanlines from top to bottom
    Tri_DrawLineHorizontal(xStart, y, xEnd, color);
    xStart -= m1;
    xEnd -= m2;  // -= because we regress along y axis
  }
}

void Tri_DrawTriSolid(int x0, int y0, int x1, int y1, int x2, int y2,
                      color_t color) {
  // sort the vertices by y-coordinate ascending (y0 < y1 < y2)
  if (y0 > y1) {
    swapInt(&y0, &y1);
    swapInt(&x0, &x1);
  }
  if (y1 > y2) {
    swapInt(&y1, &y2);
    swapInt(&x1, &x2);
  }
  if (y0 > y1) {
    swapInt(&y0, &y1);
    swapInt(&x0, &x1);
  }

  // prevent division by 0 and redundant draw
  if (y1 == y2) {
    drawFlatBottom(x0, y0, x1, y1, x2, y2, color);
  } else if (y0 == y1) {
    drawFlatTop(x0, y0, x1, y1, x2, y2, color);
  } else {
    int Mx = ((float)((x2 - x0) * (y1 - y0))) / (float)(y2 - y0) + x0;
    // My = y1
    drawFlatBottom(x0, y0, x1, y1, Mx, y1, color);
    drawFlatTop(x1, y1, Mx, y1, x2, y2, color);
  }
}

void Tri_DrawTriTexture(Vec4f a, Vec4f b, Vec4f c, Vec2f uv0, Vec2f uv1,
                        Vec2f uv2, Tri_Texture* texture) {
  // sort the vertices by y-coordinate ascending (y0 < y1 < y2)
  if (a.y > b.y) {
    swapVec4f(&a, &b);
    swapVec2f(&uv0, &uv1);
  }
  if (b.y > c.y) {
    swapVec4f(&b, &c);
    swapVec2f(&uv1, &uv2);
  }
  if (a.y > b.y) {
    swapVec4f(&a, &b);
    swapFloat(&a.z, &b.z);
    swapVec2f(&uv0, &uv1);
  }

  // flat-bottom triangle
  float m1 = (b.y - a.y) ? (float)(b.x - a.x) / (b.y - a.y) : 0;
  float m2 = (c.y - a.y) ? (float)(c.x - a.x) / (c.y - a.y) : 0;
  if (m2 < m1) swapFloat(&m1, &m2);

  for (int y = a.y; y < b.y; y++) {
    int xStart = a.x + (y - a.y) * m1;
    int xEnd = a.x + (y - a.y) * m2;
    /* Tri_DrawLineHorizontal(xStart, y, xEnd, y % 2 ? RED : BLUE); */
    for (int x = xStart; x <= xEnd; x++) {
      /* Tri_DrawPixel(x, y, x % 2 == 0 && y % 2 == 0 ? RED : BLUE); */
      Tri_DrawTexel(x, y, a, b, c, uv0, uv1, uv2, texture);
    }
  }

  // flat-top triangle
  m1 = (b.y - c.y) ? (float)(b.x - c.x) / (b.y - c.y) : 0;
  m2 = (a.y - c.y) ? (float)(a.x - c.x) / (a.y - c.y) : 0;
  if (m1 < m2) swapFloat(&m1, &m2);

  for (int y = c.y; y >= b.y; y--) {
    int xStart = c.x + (y - c.y) * m1;
    int xEnd = c.x + (y - c.y) * m2;
    /* Tri_DrawLineHorizontal(xStart, y, xEnd, y % 2 ? CYAN : YELLOW); */
    for (int x = xStart; x <= xEnd; x++) {
      /* Tri_DrawPixel(x, y, x % 2 == 0 && y % 2 == 0 ? CYAN : YELLOW); */
      Tri_DrawTexel(x, y, a, b, c, uv0, uv1, uv2, texture);
    }
  }
}

// RECT

void Tri_DrawGrid(int x, int y, int width, int height, int distance,
                  color_t color) {
  for (int j = y; j < height; j += distance) {
    for (int i = x; i < width; i += distance) {
      Tri_DrawPixel(i, j, color);
    }
  }
};

void Tri_DrawRect(int x, int y, int width, int height, color_t color) {
  for (int j = y; j < y + height; j++) {
    for (int i = x; i < x + width; i++) {
      Tri_DrawPixel(i, j, color);
    }
  }
};
