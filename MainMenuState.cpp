#include "pch.h"
#include "MainMenuState.h"

//initializer functions
void MainMenuState::initializeVariables()
{

}

void MainMenuState::initializeBackground()
{
	this->background.setSize
	(sf::Vector2f
	(	static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y))
	);

	if (!this->bgimage.loadFromFile("Resources/Images/Backgrounds/mainmenubg.png"))
	{
		throw "ERROR MAINMENUSTATE::BACKGROUND_LOADING_FAILED";
	}
	this->background.setTexture(&this->bgimage);
}

void MainMenuState::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/Neucha-Regular.ttf"))
	{
		throw("ERROR::MAINMENUSTATE - FONT NOT LOADED"); //exits program and gives the "Error"
	}
}

void MainMenuState::initializeKeybinds()
{
	std::ifstream file("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initializeButtons()
{
	this->buttons["NEW_GAME"] = new Button(760.f, 600.f, 400.f, 60.f,
		&this->font, "New Game", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),		//text color
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));				//button color	

	this->buttons["LOAD_GAME"] = new Button(760.f, 700.f, 400.f, 60.f,
		&this->font, "Load Game", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	this->buttons["SETTINGS"] = new Button(760.f, 800.f, 400.f, 60.f,
		&this->font, "Settings", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	this->buttons["QUIT"] = new Button(760.f, 900.f, 400.f, 60.f,
		&this->font, "Quit", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	this->buttons["EDITOR_STATE"] = new Button(1300.f, 900.f, 400.f, 60.f,
		&this->font, "Editor", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));
}
//

MainMenuState::MainMenuState(StateData* state_data)
	: States(state_data)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeKeybinds();
	this->initializeButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dtime)
{

}

void MainMenuState::updateButtons()
{
	for(auto i : this->buttons)
	{
		i.second->update(this->mousePositionWindow);
	}

	//New game
	if (this->buttons["NEW_GAME"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	//Load game
	if (this->buttons["LOAD_GAME"]->isPressed())
	{
		std::cout << "This button doesn't work yet\n";
	}

	//Settings
	if (this->buttons["SETTINGS"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	//Quit the game
	if (this->buttons["QUIT"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}
}

void MainMenuState::update(const float& dtime)
{
	this->updateMousePositions();
	this->updateInput(dtime);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);
}
