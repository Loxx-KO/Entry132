#include "pch.h"
#include "EditorState.h"

void EditorState::initializeVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TILE_TYPES::DEAFULT;
	this->camera_speed = 100.f;
}

void EditorState::initializeView()
{
	this->mainView.setSize(sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width), static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->mainView.setCenter(this->stateData->gfxSettings->resolution.width / 2.f , this->stateData->gfxSettings->resolution.height / 2.f);

}

void EditorState::initializeBackground()
{

}

void EditorState::initializePauseMenu()
{
	this->pausemenu = new PausedMenu(*this->window, this->font);

	this->pausemenu->addButton("LOAD", 760.f, 400.f, "Load");
	this->pausemenu->addButton("SAVE", 760.f, 500.f, "Save");
	this->pausemenu->addButton("SETTINGS", 760.f, 600.f, "Settings");
	this->pausemenu->addButton("QUIT", 760.f, 700.f, "Quit");
}

void EditorState::initializeGui()
{
	this->sideBar.setSize(sf::Vector2f(60.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sideBar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sideBar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sideBar.setOutlineThickness(2.f);

	this->tileSelector.setSize(sf::Vector2f(50.f, 50.f));			//change later - grid size will be defined in state data
	this->tileSelector.setOutlineThickness(1.f);
	this->tileSelector.setFillColor(sf::Color(255,255,255,170));
	this->tileSelector.setOutlineColor(sf::Color::Magenta);

	this->tileSelector.setTexture(this->tileMap->getTileTextureSheet());
	this->tileSelector.setTextureRect(this->textureRect);

	this->texture_selector = new TextureSelector(61.f, 20.f, 500.f, 500.f, 
		this->stateData->gridSize, this->tileMap->getTileTextureSheet(), this->font, "Hide");
}

void EditorState::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/Neucha-Regular.ttf"))
	{
		throw("ERROR::EDITORSTATE - FONT NOT LOADED"); //exits program and gives the "Error"
	}
}

void EditorState::initializeCursorText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setPosition(this->mousePositionView.x, this->mousePositionView.y);
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

void EditorState::initializeTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 40, 30, "Resources/Images/Tile_textures/tileSelector_1.png");
}
//

EditorState::EditorState(StateData* state_data)
	: States(state_data)
{
	this->initializeVariables();
	this->initializeView();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeCursorText();
	this->initializeKeybinds();
	this->initializePauseMenu();
	this->initializeButtons();
	this->initializeTileMap();
	this->initializeGui();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->pausemenu;

	delete this->tileMap;
	delete this->texture_selector;
}

void EditorState::updateInput(const float& dtime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unPausedState();
		}
	}
}

void EditorState::updateEditorInput(const float& dtime)
{
	//move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_RIGHT"))))
	{
		this->mainView.move(this->camera_speed * dtime, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_LEFT"))))
	{
		this->mainView.move(-this->camera_speed * dtime, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_UP"))))
	{
		this->mainView.move(0.f, -this->camera_speed * dtime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CAMERA_DOWN"))))
	{
		this->mainView.move(0.f, this->camera_speed * dtime);
	}

	//add tile to tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		if (!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mousePositionWindow)))
		{
			if (!this->texture_selector->getActive())
			{
				this->tileMap->addTile(this->mousePositionGrid.x, this->mousePositionGrid.y, 0, this->textureRect, this->collision, this->type);
			}
			else
			{
				this->textureRect = this->texture_selector->getTextureRect();
			}
		}
	}
	//remove tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
	{
		if(!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mousePositionWindow)))
		{
			if (!this->texture_selector->getActive())
			{
				this->tileMap->removeTile(this->mousePositionGrid.x, this->mousePositionGrid.y, 0);
			}
		}
	}

	//TOGGLE_COLLISION
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_COLLISION"))) && this->getKeyTime())
	{
		if (this->collision)
		{
			this->collision = false;
		}
		else this->collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INCRESE_TYPE"))) && this->getKeyTime())
	{
		//limit the max type!
		this->type++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DECRESE_TYPE"))) && this->getKeyTime())
	{
		if (this->type > 0)
		{
			this->type--;
		}
		else this->type = 0;
	}
}

void EditorState::updateButtons()
{
	for (auto i : this->buttons)
	{
		i.second->update(this->mousePositionWindow);
	}
}

void EditorState::updatePausedButtons()
{
	if (this->pausemenu->isButtonPressed("QUIT") && this->getKeyTime())
	{
		this->endState();
	}

	if (this->pausemenu->isButtonPressed("SETTINGS") && this->getKeyTime())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	if (this->pausemenu->isButtonPressed("SAVE") && this->getKeyTime())
	{
		this->tileMap->saveToFile("test_map.map");
	}

	if (this->pausemenu->isButtonPressed("LOAD") && this->getKeyTime())
	{
		this->tileMap->loadFromFile("test_map.map");
	}
}

void EditorState::updateGUI(const float& dtime)
{
	this->texture_selector->update(this->mousePositionWindow, dtime);

	if (!this->texture_selector->getActive())
	{
		this->tileSelector.setTextureRect(this->textureRect);
		//setting position for tile selector - mouse position * tile grid to make snaping rect between the tiles
		this->tileSelector.setPosition(this->mousePositionGrid.x * 50.f, this->mousePositionGrid.y * 50.f);			//change gridSize
	}

	this->cursorText.setPosition(this->mousePositionView.x + 50.f, this->mousePositionView.y - 50.f);
	std::stringstream ss;
	ss << this->mousePositionGrid.x << this->mousePositionGrid.y << "\n" 
		<< this->mousePositionView.x << " " << this->mousePositionView.y << "\n" 
		<< this->textureRect.left << " " << this->textureRect.top << "\n"
		<< "Collsion: " << this->collision << "\n"
		<< "Type: " << this->type << "\n";
	this->cursorText.setString(ss.str());
}

void EditorState::update(const float& dtime)
{
	this->updateMousePositions(&this->mainView);
	this->updateKeyTime(dtime);
	this->updateInput(dtime);

	if (!this->paused)
	{
		this->updateButtons();
		this->updateGUI(dtime);
		this->updateEditorInput(dtime);
	}
	//pause update
	else
	{
		this->pausemenu->update(this->mousePositionWindow);
		this->updatePausedButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}
}

void EditorState::renderGUI(sf::RenderTarget& target)
{
	//setting different views for different objects
	if (!this->texture_selector->getActive())
	{
		target.setView(this->mainView);
		target.draw(this->tileSelector);
	}

	target.setView(this->window->getDefaultView());
	this->texture_selector->render(target);
	target.draw(this->sideBar);

	target.setView(this->mainView);
	target.draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->mainView);
	this->tileMap->render(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);

	this->renderGUI(*target);

	if (this->paused) //render for paused
	{
		target->setView(this->window->getDefaultView());
		this->pausemenu->render(*target);
	}
}