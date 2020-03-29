#pragma once

class Renderer
{
public:
	void Init();
	void Resize(int width, int height);
	void Draw();

private:
	int extentWidth = 0;
	int extentHeight = 0;
};

