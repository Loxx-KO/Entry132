#include "pch.h"
#include "EditorState.h"

void EditorState::initializeVariables()
{

}

void EditorState::initializeBackground()
{

}

void EditorState::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/Neucha-Regular.ttf"))
	{
		throw("ERROR::EDITORSTATE - FONT NOT LOADED"); //exits program and gives the "Error"
	}
}

void EditorState::initializeKeybinds()
{
	std::ifstream file("Config/editorstate_keybinds.ini");

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

void EditorState::initializeButtons()
{
	
}
//

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<States*>* states)
	: States(window, supportedKeys, states)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeKeybinds();
	this->initializeButtons();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void EditorState::updateInput(const float& dtime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateButtons()
{
	for (auto i : this->buttons)
	{
		i.second->update(this->mousePositionView);
	}
}

void EditorState::update(const float& dtime)
{
	this->updateMousePositions();
	this->updateInput(dtime);

	this->updateButtons();
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderButtons(*target);
}

