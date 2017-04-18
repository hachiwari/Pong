#pragma once
#include "SFML\Audio.hpp"

using namespace std;
using namespace sf;

class SoundManager
{
public:
	SoundManager(string sFileName);
	~SoundManager();

	void Play();

private:
	Sound _Sound;
};

