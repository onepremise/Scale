#include "sseColor.hpp"

sseColor::sseColor(void)
{
	color[0]=0;
	color[1]=0;
	color[2]=0;
	color[3]=1;
}

sseColor::sseColor(sseColor &c)
{
	setColor(c);
}

sseColor::sseColor(float r, float g, float b, float a)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
	color[3]=a;
}

sseColor::sseColor(float r, float g, float b)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
	color[3]=1;
}


sseColor::~sseColor(void)
{

}

void sseColor::setRed(float r)
{
	color[0]=r;
}

void sseColor::setGreen(float g)
{
	color[1]=g;
}

void sseColor::setBlue(float b)
{
	color[2]=b;
}

void sseColor::setAlpha(float a)
{
	color[3]=a;
}

float sseColor::getRed()
{
	return color[0];
}

float sseColor::getGreen()
{
	return color[1];
}

float sseColor::getBlue()
{
	return color[2];
}

float sseColor::getAlpha()
{
	return color[3];
}

void sseColor::setColor(sseColor &c)
{
	color[0]=c[0];
	color[1]=c[1];
	color[2]=c[2];
	color[3]=c[3];
}

void sseColor::setColor(float r, float g, float b, float a)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
	color[3]=a;
}

void sseColor::setColor(float r, float g, float b)
{
	color[0]=r;
	color[1]=g;
	color[2]=b;
	color[3]=1;
}

float *sseColor::getColor()
{
	return color;
}