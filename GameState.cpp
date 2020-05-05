#include "pch.h"
#include "GameState.h"

void GameState::initializeVariables()
{
	this->playerbox = this->player->getGlobalBounds();
}

//initializer functions
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

void GameState::initializeFight()
{

}

void GameState::CreateEnemy()
{
	this->testenemy = new Enemy(400.f, 400.f, this->textures["TEST_ENEMY_IDLE"], "testenemy");
	this->blob = new Enemy(600.f, 700.f, this->textures["BLOB_ENEMY_IDLE"], "blob");
	this->snake = new Enemy(200.f, 300.f, this->textures["MECHA_SNAKE_IDLE"], "snake");
}

void GameState::initializeEnemy()
{
	this->activeEnemies.push_back(this->testenemy);
	this->activeEnemies.push_back(this->blob);
	this->activeEnemies.push_back(this->snake);
}

void GameState::initializePlayers()
{
	this->player = new Player(20.f, 20.f, this->textures["PLAYER_SHEET"], "ingame");
}

//Constructors/destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<States*>* states)
	: States(window, supportedKeys, states)
{
	this->initializeKeybinds();
	this->initializeFonts();
	this->initializeTextures();

	this->initializePauseMenu();

	this->initializePlayers();
	this->CreateEnemy();
	this->initializeEnemy();
}

GameState::~GameState()
{
	delete this->pausemenu;
	delete this->fight;

	delete this->player;
	delete this->testenemy;
	delete this->blob;
	delete this->snake;
	this->activeEnemies.clear();
}

//functions
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
		this->activeEnemy = this->activeEnemies[i];
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
			this->states->push(new FightState(this->window, this->supportedKeys, this->states, this->activeEnemies[i], this->enemyName));
		}
	}
}

void GameState::updatePausedMenuButtons()
{
	if (this->pausemenu->isButtonPressed("QUIT") && this->getKeyTime())
	{
		this->endState();
	}

	if (this->pausemenu->isButtonPressed("SETTINGS") && this->getKeyTime())
	{
		this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));
	}
}

void GameState::update(const float& dtime)
{
	this->updateKeyTime(dtime);
	this->updatePausedInput(dtime);
	this->updateMousePositions();

	//unpaused update
	if (!this->paused)				
	{
		this->updateInput(dtime);

		this->player->update(dtime);

		this->testenemy->update(dtime);
		this->blob->update(dtime);
		this->snake->update(dtime);
	}
	//pause update
	else
	{
		this->pausemenu->update(this->mousePositionView);
		this->updatePausedMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->player->render(*target);

	this->testenemy->render(*target);
	this->blob->render(*target);
	this->snake->render(*target);

	if (this->paused) //render for paused
	{
		this->pausemenu->render(*target);
	}
}
