#pragma once
#include <GL/gl.h>

/* Image type - contains height, width, and data */
struct Image {
    int sizeX;
    int sizeY;
    unsigned char *data;
};
typedef struct Image Image;

class Painter
{
public:
	Painter();
	int imageLoad(char *filename, Image *image);
	void loadGLTextures();
	void square(int x1, int y1, int x2, int y2, int* startXY, int step);
private:
	/* storage for one texture  */
	GLuint texture[1];
	char texPath[80];
	int bitmapHeader;
	unsigned int bitmapVersion;
	int height;
	unsigned int compression;
	unsigned int pixelDataOffset;
	unsigned int sizeImage;
};
