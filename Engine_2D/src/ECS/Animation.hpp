#pragma once

struct Animation
{
	int frames;
	int animIndex;
	int frameMills;

	Animation() {};
	Animation(int _animIndex, int _frames, int _frameMills)
	{
		animIndex = _animIndex;
		frames = _frames;
		frameMills = _frameMills;
	}

};