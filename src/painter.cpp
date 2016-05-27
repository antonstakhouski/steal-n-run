#include <cstdio>
#include <cstdlib>
#include "painter.hpp"
#include <cstring>

Painter::Painter()
{
	strcpy(texPath, "../res/textures.bmp");
	bitmapHeader = 14;
}

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int Painter::imageLoad(char *filename, Image *image) {
	FILE *file;
    unsigned int i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
    	printf("File Not Found : %s\n",filename);
    	return 1;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, bitmapHeader - sizeof(pixelDataOffset), SEEK_CUR);

    if ((i = fread(&pixelDataOffset, 4, 1, file)) != 1) {
    	printf("Error reading pixelDataOffset from %s.\n", filename);
    	return 1;
    }
    printf("pixelDataOffset is %u\n", pixelDataOffset);

    if ((i = fread(&bitmapVersion, 4, 1, file)) != 1) {
    	printf("Error reading width from %s.\n", filename);
    	return 1;
    }
    printf("BitMap version. Size %d\n", bitmapVersion);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
    	printf("Error reading width from %s.\n", filename);
    	return 1;
    }
    printf("Width of %s: %d\n", filename, image->sizeX);
    
    // read the height 
    if ((i = fread(&height, 4, 1, file)) != 1) {
    	printf("Error reading height from %s.\n", filename);
    	return 1;
    }
    image->sizeY = abs(height);
    printf("Height of %s: %d\n", filename, height);

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
    	printf("Error reading planes from %s.\n", filename);
    	return 1;
    }
    if (planes != 1) {
    	printf("Planes from %s is not 1: %u\n", filename, planes);
    	return 1;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
    	printf("Error reading bpp from %s.\n", filename);
    	return 1;
    }
    printf("Bpp from %s is : %u\n", filename, bpp);
    if (bpp != 24) {
    	printf("Bpp from %s is not 24: %u\n", filename, bpp);
    	return 1;
    }

    // read the compression
    if ((i = fread(&compression, 4, 1, file)) != 1) {
    	printf("Error reading compression from %s.\n", filename);
    	return 1;
    }
    printf("compression of %s: %u\n", filename, compression);

    if ((i = fread(&sizeImage, 4, 1, file)) != 1) {
    	printf("Error reading sizeImage from %s.\n", filename);
    	return 1;
    }
    printf("sizeImage of %s: %u\n", filename, sizeImage);
    
    // seek past the rest of the bitmap header.
    fseek(file, pixelDataOffset, SEEK_SET);



    // read the data. 
    image->data = (unsigned char *) malloc(sizeof(unsigned char)*sizeImage);
    if (image->data == NULL) {
    	printf("Error allocating memory for color-corrected image data\n");
    	return 1;   
    }

    
    if ((i = fread(image->data, sizeImage, 1, file)) != 1) {
    	printf("Error reading image data from %s.\n", filename);
    	return 1;
    }

    unsigned char temp;
    for (i = 0; i < sizeImage; i += 3) { 
    	// reverse all of the colors. (bgr -> rgb)
    	temp = image->data[i];
    	image->data[i] = image->data[i + 2];
    	image->data[i + 2] = temp;
    }

    //reverse string order
    for (int i = 0; i < image->sizeY / 2; i++) {
    	for (int j = 0; j < image->sizeX; j++){
    		temp = image->data[i * image->sizeX * 3 + j];
    		image->data[i * image->sizeX * 3 + j] = image->data[(image->sizeY - 2 - i) * image->sizeX * 3 + j];
    		image->data[(image->sizeY - 2 - i) * image->sizeX * 3 + j] = temp;
    	}
    }

    //conversion test
/*    for(int i = (image->sizeY - 2) * image->sizeX * 3; i < (image->sizeY - 2) * image->sizeX * 3 + 30; i++){
    	if (i % 3 == 0 && i != 0){
    		printf("\t");
    	}

    	if (i % (image->sizeX * 3) == 0 &&  i != 0){
    		printf("\n");
    	}

    	printf("%d ", image->data[i]);
    }
    printf("\n");
    exit(1);*/

    // we're done
    return 0;
}

// Load Bitmaps And Convert To Textures
void Painter::loadGLTextures() { 
    // Load Texture
	Image *image1;

    // allocate space for texture
	image1 = (Image *) malloc(sizeof(Image));
	if (image1 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (imageLoad(texPath, image1) != 0) {
		exit(1);
	}        

	glEnable( GL_TEXTURE_RECTANGLE_NV );
    // Create Texture   
	glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_RECTANGLE_NV, texture[0]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
    glDisable( GL_TEXTURE_RECTANGLE_NV );
}

/* The main drawing function. */
void Painter::square(int x1, int y1, int x2, int y2, 
	int* startXY, int step)
{
    //white background
	glColor3f( 1.0f, 1.0f, 1.0f );
    glBindTexture(GL_TEXTURE_RECTANGLE_NV, texture[0]);   // choose the texture to use.

    glEnable(GL_TEXTURE_RECTANGLE_NV);
    glBegin(GL_QUADS);                      // begin drawing a cube
    
    //top left
    glTexCoord2i(startXY[0], startXY[1]);
    glVertex2f(x1, y1);  // Bottom Left Of The Texture and Quad
    //top right
    glTexCoord2i(startXY[0] + step, startXY[1]); 
    glVertex2f(x2, y1);  // Bottom Right Of The Texture and Quad
    //bottom right
    glTexCoord2i(startXY[0] + step, startXY[1] + step); 
    glVertex2f(x2, y2);  // Top Right Of The Texture and Quad
    //bottom left
    glTexCoord2i(startXY[0] , startXY[1] + step); 
    glVertex2f(x1, y2);  // Top Left Of The Texture and Quad


    glEnd();                                    // done with the polygon.
    glDisable(GL_TEXTURE_RECTANGLE_NV);
}
