//#include <windows.h>  //Solo para Windows
//#include <gl/gl.h>     // The GL Header File
//#include <stdio.h>
//#include <string.h>
//#include "Main.h"


#include <windows.h>		// Archivo de cabecera para Windows
#include <math.h>			// Archivo de cabecera para Funciones Matemáticas
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>			// Header File For Standard Library
//#include "GL\gl.h"				// Archivo de cabecera para la libreria OpenGL32
//#include "glu.h"			// Archivo de cabecera para la libreria GLu32
//#include "glaux.h"			// Archivo de cabecera para la libreria Glaux
#include "GL\glut.h"			// Archivo de cabecera para la libreria Glut


class CTexture
{
public:
	char* name;
	unsigned char*  imageData;
	int		bpp;			// Image Color Depth In Bits Per Pixel
	int		width;			// Image Width
	int		height;		    // Image Height
	unsigned int    GLindex;

	bool LoadTGA(char* filename);		// Loads A TGA File Into Memory
	bool LoadBMP(char* filename);
	void BuildGLTexture();
	void ReleaseImage();
};
