#include "pch.h"
#include "GameOver.h"

//initializer functions
void GameOver::initializeVariables()
{

}

void GameOver::initializeBackground()
{
	this->background.setSize
	(sf::Vector2f
	(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y))
	);

	if (!this->bgimage.loadFromFile("Resources/Images/Backgrounds/settingsmenubg.png"))
	{
		throw "ERROR GAMEOVER::BACKGROUND_LOADING_FAILED";
	}
	this->background.setTexture(&this->bgimage);
}

void GameOver::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/Neucha-Regular.ttf"))
	{
		throw("ERROR::GAMEOVER - FONT NOT LOADED"); //exits program and gives the "Error"
	}
}

void GameOver::initializeKeybinds()
{
	std::ifstream file("Config/settingsstate_keybinds.ini");

	if (file.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (file >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	file.close();
}

void GameOver::initializeButtons()
{
	this->buttons["NEW_GAME"] = new Button(760.f, 600.f, 400.f, 60.f,
		&this->font, "New Game", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),		//text color
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));				//button color	

	this->buttons["RETURN"] = new Button(760.f, 900.f, 400.f, 60.f,
		&this->font, "Return to main menu", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));
}
//

GameOver::GameOver(StateData* state_data)
	: States(state_data)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeKeybinds();
	this->initializeButtons();
}

GameOver::~GameOver()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void GameOver::updateInput(const float& dtime)
{

}

void GameOver::updateButtons()
{
	for (auto i : this->buttons)
	{
		i.second->update(this->mousePositionWindow);
	}

	//New game // later load last save
	if (this->buttons["NEW_GAME"]->isPressed())
	{
		std::cout << "doesn't work";
		this->states->pop();
	}

	//Return to main menu
	if (this->buttons["RETURN"]->isPressed())
	{
		std::cout << "doesn't work";
		this->states->pop();
	}
}

void GameOver::update(const float& dtime)
{
	this->updateMousePositions();
	this->updateInput(dtime);

	this->updateButtons();
}

void GameOver::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}
}

void GameOver::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);
}