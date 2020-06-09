#include "pch.h"
#include "States.h"

States::States(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;

	this->end = false;
	this->paused = false;
	this->fight = false;

	this->keytime = 0.f;
	this->keytimemax = 20.f;
	this->gridSize = state_data->gridSize;
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

void States::fightStateNotActive()
{
	this->fight = false;
}

void States::fightStateEnding()
{
	this->fight = true;
}


void States::updateKeyTime(const float& dtime)
{
	if (this->keytime < this->keytimemax)
	{
		this->keytime += 100.f * dtime;
	}
}

void States::updateMousePositions(sf::View* view)
{
	this->mousePositionScreen = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);

	if(view)
		this->window->setView(*view);

	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePositionGrid = 
		sf::Vector2u(
			static_cast<unsigned> (this->mousePositionView.x) / 50,			//static_cast<unsigned> (this->gridSize)
			static_cast<unsigned> (this->mousePositionView.y) / 50
		);

	this->window->setView(this->window->getDefaultView());
}
