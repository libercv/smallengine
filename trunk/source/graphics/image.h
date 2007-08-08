//////////////////////////////////////////////////////////////////////////////////////////
//	Image.h
//	functions for images to be turned to textures
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <GL/gl.h>

namespace Small
{

class Image
{
public:
	Image() : data(NULL), bpp(0), width(0), height(0)
	{}

	~Image()
	{
		if(data)
			delete [] data;
		data=NULL;
	}
	
	bool Load(char * filename);					//load a texture from a file

	bool LoadBMP(char * filename);				//Load BMP
	bool Load24BitBMP(char * filename);
	bool Load8BitBMP(char * filename);

	bool LoadPCX(char * filename);				//Load PCX
	
	bool LoadJPG(char * filename);				//Load JPG

	bool LoadTGA(char * filename);				//Load TGA
	bool LoadUncompressed8BitTGA(char * filename);
	bool LoadUncompressedTrueColorTGA(char * filename);
	bool LoadCompressedTrueColorTGA(char * filename);
	
	//load an uncompressed greyscale TGA for alpha channel
	bool LoadAlphaTGA(char * filename);

	bool CreateTexture(unsigned int &texture, char * strFileName);

	//Alter the image
	void FlipVertically();

	unsigned char * data;				//Image data
	unsigned int	bpp;				//Image color depth in bits per pixel
	unsigned int	width;				//Image width
	unsigned int	height;			//Image height
	
	GLuint	 format;				//Data format, eg GL_RGBA
};

//Universal bitmap identifier
//const DWORD BITMAP_ID=0x4D42;
#ifndef BITMAP_ID
	#define BITMAP_ID 0x4D42
#endif
//const unsigned int DWORD_BITMAP_ID=0x4D42;
}
#endif	//TEXTURE_Image_H
