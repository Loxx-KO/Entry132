#include "pch.h"
#include "States.h"

States::States(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<States*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->end = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimemax = 10.f;
}

States::~States()
{

}

//accessors
const bool& States::getEnd() const
{
	return this->end;
}

const bool States::getKeyTime()
{
	if (this->keytime >= this->keytimemax)
	{
		//resets the keytime
		this->keytime = 0.f;
		return true;
	}

	return false;
}

//functions
void States::endState()
{
	this->end = true;
}

void States::pauseState()
{
	this->paused = true;
}

void States::unPausedState()
{
	this->paused = false;
}


void States::updateKeyTime(const float& dtime)
{
	if (this->keytime < this->keytimemax)
	{
		this->keytime += 100.f * dtime;
	}
}

void States::updateMousePositions()
{
	this->mousePositionScreen = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
