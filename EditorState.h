#pragma once
#include "States.h"
#include "Button.h"
#include "PausedMenu.h"
#include "SettingsState.h"
#include "TileMap.h"
#include "TextureSelector.h"

class EditorState :
	public States
{
private:
	//variables
	sf::View mainView;
	float camera_speed;

	PausedMenu* pausemenu;
	sf::Font font;
	sf::Text cursorText;

	std::map<std::string, Button*> buttons;

	TileMap* tileMap;

	sf::RectangleShape sideBar;

	sf::IntRect textureRect;
	sf::RectangleShape tileSelector;

	TextureSelector* texture_selector;

	bool collision;
	short type;

	//functions
	void initializeVariables();
	void initializeView();
	void initializeBackground();
	void initializeFonts();
	void initializeCursorText();
	void initializeKeybinds();
	void initializeButtons();
	void initializePauseMenu();
	void initializeGui();
	void initializeTileMap();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//functions
	void updateInput(const float& dtime);
	void updateEditorInput(const float& dtime);

	void updateButtons();
	void updatePausedButtons();
	void updateGUI(const float& dtime);

	void update(const float& dtime);

	void renderButtons(sf::RenderTarget& target);
	void renderGUI(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};



