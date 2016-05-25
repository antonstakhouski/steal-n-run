#include "painter.hpp"
#include "GL/gl.h"

void Painter::square(int x1, int y1, int x2, int y2, float r, float g, float b)
{

  glColor3f(r, g , b);
  glBegin(GL_QUADS);
  glVertex2f(x1, y1);
  glVertex2f(x2, y1);
  glVertex2f(x2, y2);
  glVertex2f(x1, y2);
  glEnd();
}
