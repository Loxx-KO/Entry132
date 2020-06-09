#include "pch.h"
#include "SettingsState.h"

//initializer functions
void SettingsState::initializeVariables()
{
	this->fullscreen = false;
}

void SettingsState::initializeBackground()
{
	this->background.setSize
	(sf::Vector2f
	(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y))
	);

	if (!this->bgimage.loadFromFile("Resources/Images/Backgrounds/settingsmenubg.png"))
	{
		throw "ERROR MAINMENUSTATE::BACKGROUND_LOADING_FAILED";
	}
	this->background.setTexture(&this->bgimage);
}

void SettingsState::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/Neucha-Regular.ttf"))
	{
		throw("ERROR::MAINMENUSTATE - FONT NOT LOADED"); //exits program and gives the "Error"
	}
}

void SettingsState::initializeKeybinds()
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

void SettingsState::initializeButtons()
{
	this->buttons["FULLSCREEN"] = new Button(760.f, 400.f, 400.f, 60.f,
		&this->font, "Fullscreen", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	this->buttons["QUIT"] = new Button(760.f, 500.f, 400.f, 60.f,
		&this->font, "Quit settings", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));
}

SettingsState::SettingsState(StateData* state_data)
	:States(state_data)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeKeybinds();
	this->initializeButtons();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void SettingsState::updateInput(const float& dtime)
{

}

void SettingsState::updateButtons()
{
	for (auto i : this->buttons)
	{
		i.second->update(this->mousePositionWindow);
	}

	//Fullscreen off/on
	if (this->buttons["FULLSCREEN"]->isPressed())
	{
		std::cout << "not done yet";
	}

	//Quit settings
	if (this->buttons["QUIT"]->isPressed())
	{
		this->states->pop();
	}
}

void SettingsState::update(const float& dtime)
{
	this->updateMousePositions();
	this->updateInput(dtime);

	this->updateButtons();
}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);
}
