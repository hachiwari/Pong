#include "SoundManager.h"
#include <iostream>

using namespace std;

SoundManager::SoundManager(string sFileName)
{
	SoundBuffer buffer;

	if (!buffer.loadFromFile(sFileName))
	{
		cout << "Error - no files (" << sFileName << ")" << endl;
		exit(0);
	}

	_Sound.setBuffer(buffer);
}

SoundManager::~SoundManager()
{
}

void SoundManager::Play()
{
	_Sound.play();
}
