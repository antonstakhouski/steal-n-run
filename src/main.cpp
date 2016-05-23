#include "painter.hpp"
#include "game.hpp"
#include "GL/glut.h"
#include "field.hpp"

Game game;

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  Painter p;
  game.draw(p);
  glutSwapBuffers();
}

void timer(int = 0)
{
  game.tick();
  display();
  glutTimerFunc(100, timer, 0);
}

void keyEvent(int key, int, int)
{
  switch (key)
  {
  case GLUT_KEY_LEFT:
    game.keyEvent(Player::LEFT);
    break;
  case GLUT_KEY_UP:
    game.keyEvent(Player::UP);
    break;
  case GLUT_KEY_RIGHT:
    game.keyEvent(Player::RIGHT);
    break;
  case GLUT_KEY_DOWN:
    game.keyEvent(Player::DOWN);
    break;
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(Field::WIDTH * Field::BLOCK_WIDTH, 
		    Field::HEIGHT * Field::BLOCK_HEIGHT);
  glutInitWindowPosition(100, 780);
  glutCreateWindow("Steal and Run");
  glClearColor(0, 0, 0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, Field::WIDTH * Field::BLOCK_WIDTH, 
	  Field::HEIGHT * Field::BLOCK_HEIGHT, 0, 
	  -1.0, 1.0);
  glutDisplayFunc(display);
  glutSpecialFunc(keyEvent);
  timer();

  glutMainLoop();
}
