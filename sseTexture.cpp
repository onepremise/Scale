#include "sseMath.hpp"
#include "sseTexture.h"

int sseTexture::idCounter=0;

void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message){
    printf("\n*** ");
    if(fif != FIF_UNKNOWN) {
        if (FreeImage_GetFormatFromFIF(fif))
            printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
    }
    printf(message);
    printf(" ***\n");
}

sseTexture::sseTexture(void)
{
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif
}

sseTexture::~sseTexture(void)
{
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif

	Unload();
}

void sseTexture::SetRenderer(sseGrafxInterface *pRenderer)
{
	m_pRenderer=pRenderer;
}

FIBITMAP *sseTexture::OpenImage(const char* filename)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib(0);

	fif = FreeImage_GetFileType(filename, 0);

	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename);
	if(fif == FIF_UNKNOWN)
		return false;

	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);

	return dib;
}

void sseTexture::CloseImage(FIBITMAP *dib)
{
	FreeImage_Unload(dib);
}

int sseTexture::Load(String filename, int textureID, 
						  GLenum image_format, GLint internal_format, 
						  GLint level, GLint border)
{
	BYTE* bits(0);
	unsigned int width(0), height(0);
	GLuint glTexurePtr=0;
	FIBITMAP *dib=OpenImage(filename.c_str());

	if (textureID<0)
		textureID=idCounter++;

	if(!dib)
		return false;

	bits = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	CloseImage(dib);

	if((bits == 0) || (width == 0) || (height == 0))
		return false;

	map<int, GLuint>::iterator it = m_IDs.find(textureID);

	if(it!=m_IDs.end())
		glDeleteTextures(1, &(*it).second);

	glGenTextures(1, &glTexurePtr);

	m_IDs[textureID]=glTexurePtr;

	glBindTexture(GL_TEXTURE_2D, glTexurePtr);

	glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
		border, image_format, GL_UNSIGNED_BYTE, bits);

	return textureID;
}

//Confert BGR format from FreeImage to RGB for OpenGL
BYTE*  sseTexture::convertToRGBA(BYTE*  bits, int components, int width, int height)
{
	BYTE* textura = new BYTE[components*width*height];

	for(int j= 0; j<(width*height); j++){
		textura[j*components+0]= bits[j*components+2];
		textura[j*components+1]= bits[j*components+1];
		textura[j*components+2]= bits[j*components+0];

		if (components>3)
			textura[j*components+3]= bits[j*components+3];
	}

	return textura;
}

int sseTexture::LoadWrap(String filename, int textureID, GLenum image_format, int wraps,
						  int wrapt,int magf,int minf, bool mipmap)
{
	int depth=0;
	int components=0;
	BYTE* bgrBits = NULL;
	BYTE* rgbBits = NULL;
	unsigned int width(0), height(0);
	GLuint glTexurePtr=0;

	//SDL_CreateRGBSurface

	if (textureID<0)
		textureID=idCounter++;

	return textureID;

	sseErrorHandler::_ThrowIfSDLTextureLoadError();

	FreeImage_SetOutputMessage(FreeImageErrorHandler);

	FIBITMAP *dib=OpenImage(filename.c_str());

	if(!dib)
		sseErrorHandler::_ThrowIfSDLTextureLoadError();

	int bitsPerPixel =  FreeImage_GetBPP(dib);

	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32)
	{
	    cout << "Source image has " << bitsPerPixel << " bits per pixel. Skipping conversion." << endl;
	    bitmap32 = dib;
	}
	else
	{
	    cout << "Source image has " << bitsPerPixel << " bits per pixel. Converting to 32-bit colour." << endl;
	    bitmap32 = FreeImage_ConvertTo32Bits(dib);
	}

	if(image_format==GL_RGB)
		components = 3;
	else if(image_format==GL_RGBA)
		components = 4;
	else {
		sseErrorHandler::_ThrowIfSDLTextureLoadError();
	}

	depth = FreeImage_GetBPP(bitmap32);
	bgrBits = FreeImage_GetBits(bitmap32);
	width  = FreeImage_GetWidth(bitmap32);
	height = FreeImage_GetHeight(bitmap32);

	if((bgrBits == 0) || (width == 0) || (height == 0))
	{
		CloseImage(dib);
		CloseImage(bitmap32);
		sseErrorHandler::_ThrowIfSDLTextureLoadError();
	}

	rgbBits = convertToRGBA(bgrBits, components, width, height);

	CloseImage(dib);
	CloseImage(bitmap32);

	map<int, GLuint>::iterator it = m_IDs.find(textureID);

	if(it!=m_IDs.end())
		glDeleteTextures(1, &(*it).second);

	sseErrorHandler::_ThrowIfSDLTextureLoadError();

	glGenTextures(1, &glTexurePtr);

	sseErrorHandler::_ThrowIfSDLTextureLoadError();

	m_IDs[textureID]=glTexurePtr;

	glBindTexture(GL_TEXTURE_2D,glTexurePtr);

	sseErrorHandler::_ThrowIfSDLTextureLoadError();

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wraps);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapt);

	sseErrorHandler::_ThrowIfSDLTextureLoadError();

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minf);

	sseErrorHandler::_ThrowIfSDLTextureLoadError();

	if(!mipmap)
	{
		glTexImage2D(GL_TEXTURE_2D,0,components,width,height,0,image_format,
					 GL_UNSIGNED_BYTE,rgbBits);
	}
	else
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D,components,width,height,image_format,
						  GL_UNSIGNED_BYTE,rgbBits);
	}

	sseErrorHandler::_ThrowIfSDLTextureLoadError();

	delete [] rgbBits;

	return textureID;
}

bool sseTexture::Unload(int iTexID)
{
	bool result(true);

	map<int, GLuint>::iterator it = m_IDs.find(iTexID);

	if(it!=m_IDs.end()) {
		glDeleteTextures(1, &(*it).second);
		m_IDs.erase(it);
	} else {
		result = false;
	}

	return result;
}

void sseTexture::Bind(int iTexID)
{
	map<int, GLuint>::iterator it = m_IDs.find(iTexID);

	if(it!=m_IDs.end()) {
		GLuint glTexurePtr=(*it).second;
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, glTexurePtr);
	}

	sseErrorHandler::_ThrowIfSDLTextureLoadError();
}

void sseTexture::Unload()
{
	map<int, GLuint>::iterator it = m_IDs.begin();

	while(it != m_IDs.end())
	{
		Unload((*it).first);
		it = m_IDs.begin();
	}

	m_IDs.clear();
}
