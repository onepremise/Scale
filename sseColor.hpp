#pragma once

class sseColor
{
public:
	sseColor(void);
	sseColor(sseColor &c);
	sseColor(float r, float g, float b, float a);
	sseColor(float r, float g, float b);
	~sseColor(void);

	float operator[] (int index)
	{
		return color[index];
	}

	void setRed(float r);
	void setGreen(float r);
	void setBlue(float b);
	void setAlpha(float a);

	float getRed();
	float getGreen();
	float getBlue();
	float getAlpha();

	void setColor(sseColor &c);
	void setColor(float r, float g, float b, float a);
	void setColor(float r, float g, float b);
	float *getColor();

public:
	float  color[4];
};