#include "pch.h"
#include "GameState.h"

//initializer functions
void GameState::initializeDeferredRender()
{
	this->stackSizeBefore = 0;
	this->stackSizeAfter = 1;

	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));

}

void GameState::initializeVariables()
{
	this->load_false();
}

void GameState::initializeView()
{
	this->view.setSize(sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width), static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->view.setCenter(sf::Vector2f(this->stateData->gfxSettings->resolution.width / 2.f, this->stateData->gfxSettings->resolution.height / 2.f));
}

void GameState::initializeKeybinds()
{
	std::ifstream file("Config/gamestate_keybinds.ini");

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

void GameState::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/Neucha-Regular.ttf"))
	{
		throw("ERROR::MAINMENUSTATE - FONT NOT LOADED"); //exits program and gives the "Error"
	}
}

void GameState::initializeTextures()
{
	//player textures

	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/LiamSheet.png"))
	{
		throw "ERROR::GAME_STATE::PLAYER_IDLE_FRONT_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}

	//enemy textures
	if (!this->textures["TEST_ENEMY_IDLE"].loadFromFile("Resources/Images/Sprites/Enemy/testenemy.png"))
	{
		throw "ERROR::GAME_STATE::TEST_ENEMY_IDLE_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}

	if (!this->textures["BLOB_ENEMY_IDLE"].loadFromFile("Resources/Images/Sprites/Enemy/blob_enemy.png"))
	{
		throw "ERROR::GAME_STATE::BLOB_ENEMY_IDLE_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}

	if (!this->textures["MECHA_SNAKE_IDLE"].loadFromFile("Resources/Images/Sprites/Enemy/mechasnake_enemy.png"))
	{
		throw "ERROR::GAME_STATE::MECHA_SNAKE_IDLE_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}
}

void GameState::initializePauseMenu()
{
	this->pausemenu = new PausedMenu(*this->window, this->font);

	this->pausemenu->addButton("SAVE", 760.f, 500.f, "Save");
	this->pausemenu->addButton("SETTINGS", 760.f, 600.f, "Settings");
	this->pausemenu->addButton("QUIT", 760.f, 700.f, "Quit");
}

void GameState::initializeGameOver()
{
	this->gameOver = new GameOver(*this->window, this->font);

	//this->gameOver->addButton("LOAD_SAVE", 760.f, 500.f, "Load last save");
	this->gameOver->addButton("RETURN", 760.f, 700.f, "Return to main menu");
}

void GameState::initializeTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 40, 30, "Resources/Images/Tile_textures/tileSelector_1.png");
	this->tileMap->loadFromFile("test_map.map");
}

void GameState::initializeEnemy()
{
	this->activeEnemies.push_back(new Enemy(1200.f, 500.f, this->textures["TEST_ENEMY_IDLE"], "testenemy", INGAME));
	this->activeEnemies.push_back(new Enemy(1300.f, 100.f, this->textures["TEST_ENEMY_IDLE"], "testenemy", INGAME));
	this->activeEnemies.push_back(new Enemy(600.f, 700.f, this->textures["BLOB_ENEMY_IDLE"], "blob", INGAME));
	this->activeEnemies.push_back(new Enemy(900.f, 300.f, this->textures["MECHA_SNAKE_IDLE"], "snake", INGAME));
}

void GameState::initializePlayers()
{
	this->player = new Player(900.f, 500.f, this->textures["PLAYER_SHEET"], "ingame");

	this->player->loadStatsFromFile("player_stats_start.txt", this->hp, this->defence, this->baseDmg, this->maxDmg, this->mana, this->exp, this->lvl, this->dead);
	this->player->saveStatsToFile("player_stats.txt", this->hp, this->defence, this->baseDmg, this->maxDmg, this->mana, this->exp, this->lvl, this->dead);
}

//Constructor/destructor
GameState::GameState(StateData* state_data)
	: States(state_data)
{
	this->initializeDeferredRender();
	this->initializeVariables();
	this->initializeView();
	this->initializeKeybinds();
	this->initializeFonts();
	this->initializeTextures();
	this->initializePauseMenu();
	this->initializeGameOver();
	this->initializePlayers();
	this->initializeEnemy();
	this->initializeTileMap();
}

GameState::~GameState()
{
	delete this->pausemenu;
	delete this->gameOver;

	delete this->player;
	this->activeEnemies.clear();
	delete this->tileMap;
}

//functions
void GameState::deleteEnemy(int i)
{
	this->activeEnemies.erase(activeEnemies.begin() + i);
}

void GameState::checkIfDead()
{
		this->player->loadStatsFromFile("player_stats.txt", this->hp, this->defence, this->baseDmg, this->maxDmg, this->mana, this->exp, this->lvl, this->dead);
		std::cout << "\nEXP: " << this->exp << "\n";

		if (this->dead == 0)
		{
			//std::cout << "\nwygrana\n";
			deleteEnemy(this->enemyNumber);
			this->dead = 0;
			this->alive();
			this->stackSizeAfter = 1;
		}
		else
		{
			//std::cout << "\nporazka\n";
			this->dead_check();
			this->stackSizeAfter = 1;
		}
}

void GameState::updateInput(const float& dtime)
{
	checkForCollision(dtime);

		//player input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
			this->player->move(-1.f, 0.f, dtime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
			this->player->move(1.f, 0.f, dtime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
			this->player->move(0.f, -1.f, dtime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
			this->player->move(0.f, 1.f, dtime);
}

void GameState::updatePausedInput(const float& dtime)
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

void GameState::checkForCollision(const float& dtime)
{
	this->playerbox = this->player->getGlobalBounds();

	for (unsigned i = 0; i < this->activeEnemies.size(); i++)
	{
		this->enemybox = this->activeEnemies[i]->getGlobalBounds();
		this->enemyName = this->activeEnemies[i]->getName();

		if (this->enemybox.intersects(this->playerbox))
		{
			std::cout << "collision\n";

			//bottom collision
			if (playerbox.top < enemybox.top
				&& playerbox.top + playerbox.height < enemybox.top + enemybox.height
				&& playerbox.left < enemybox.left + enemybox.width
				&& playerbox.left + playerbox.width > enemybox.left)
			{
				this->player->stopSpeedY();
				this->player->setPosition(playerbox.left, enemybox.top - playerbox.height);
			}

			//top collision
			else if (playerbox.top > enemybox.top
				&& playerbox.top + playerbox.height > enemybox.top + enemybox.height
				&& playerbox.left < enemybox.left + enemybox.width
				&& playerbox.left + playerbox.width > enemybox.left)
			{
				this->player->stopSpeedY();
				this->player->setPosition(playerbox.left, enemybox.top + enemybox.height);
			}

			//right collision
			if (playerbox.left < enemybox.left
				&& playerbox.left + playerbox.width < enemybox.left + enemybox.width
				&& playerbox.top < enemybox.top + enemybox.height
				&& playerbox.top + playerbox.height > enemybox.top)
			{
				this->player->stopSpeedX();
				this->player->setPosition(enemybox.left - playerbox.width, playerbox.top);
			}

			//left collision
			else if (playerbox.left > enemybox.left
				&& playerbox.left + playerbox.width > enemybox.left + enemybox.width
				&& playerbox.top < enemybox.top + enemybox.height
				&& playerbox.top + playerbox.height > enemybox.top)
			{
				this->player->stopSpeedX();
				this->player->setPosition(enemybox.left + enemybox.width, playerbox.top);
			}

			this->enemyNumber = i;
			this->states->push(new FightState(this->stateData, this->activeEnemies[i], this->enemyName));

			this->stackSizeAfter = 0;
		}
		else if(this->stackSizeBefore == this->stackSizeAfter)
		{
			checkIfDead();
		}
	}
}

//updates
void GameState::updateView(const float& dtime)
{
	this->view.setCenter(this->player->getPosition().x + this->player->getGlobalBounds().width, this->player->getPosition().y + this->player->getGlobalBounds().height);
}

void GameState::updatePausedMenuButtons()
{
	if (this->pausemenu->isButtonPressed("QUIT") && this->getKeyTime())
	{
		this->endState();
	}

	if (this->pausemenu->isButtonPressed("SETTINGS") && this->getKeyTime())
	{
		this->states->push(new SettingsState(this->stateData));
	}
}

void GameState::updateGameOverButtons()
{
	if (this->gameOver->isButtonPressed("RETURN") && this->getKeyTime())
	{
		this->endState();
	}

	/*if (this->gameOver->isButtonPressed("LOAD_SAVE") && this->getKeyTime())
	{
		this->load_true();
		this->endState();
	}*/
}

void GameState::update(const float& dtime)
{
	this->updateMousePositions(&this->view);
	this->updateKeyTime(dtime);
	this->updatePausedInput(dtime);

	//unpaused update
	if (!this->paused && !this->player_dead)
	{
		this->updateView(dtime);
		this->updateInput(dtime);

		this->player->update(dtime);

		for (unsigned i = 0; i < this->activeEnemies.size(); i++)
		{
			this->activeEnemies[i]->update(dtime);
		}
	}
	//pause update
	else if(this->paused)
	{
		this->pausemenu->update(this->mousePositionWindow);
		this->updatePausedMenuButtons();
	}
	else if(this->player_dead)
	{
		this->gameOver->update(this->mousePositionWindow);
		this->updateGameOverButtons();
	}
}

//render
void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture);

	this->player->render(this->renderTexture);

	for (unsigned i = 0; i < this->activeEnemies.size(); i++)
	{
		this->activeEnemies[i]->render(this->renderTexture);
	}

	if (this->paused) //render for paused
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pausemenu->render(this->renderTexture);
	}

	if (this->player_dead) //render for dead
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->gameOver->render(this->renderTexture);
	}

	//final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
