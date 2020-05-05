#include "pch.h"
#include "FightState.h"

void FightState::initializeVariables()
{
	this->dead = false;
	this->enemyCount = 1;
	this->gainEXP = 0;
}

void FightState::initializeTextures()
{
	if (!this->textures["FIGHT_IDLE"].loadFromFile("Resources/Images/Sprites/Player/FightState_Liam.png"))
	{
		throw "ERROR::FIGHT_STATE::PLAYER_FIGHT_FRONT_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}

	if (!this->textures["TESTENEMY_FIGHT"].loadFromFile("Resources/Images/Sprites/Enemy/FightState_Testenemy.png"))
	{
		throw "ERROR::FIGHT_STATE::TESTENEMY_FIGHT_FRONT_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}

	if (!this->textures["BLOB_FIGHT"].loadFromFile("Resources/Images/Sprites/Enemy/FightState_Blob.png"))
	{
		throw "ERROR::FIGHT_STATE::BLOB_FIGHT_FRONT_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}

	if (!this->textures["SNAKE_FIGHT"].loadFromFile("Resources/Images/Sprites/Enemy/FightState_Snake.png"))
	{
		throw "ERROR::FIGHT_STATE::SNAKE_FIGHT_FRONT_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}
}

void FightState::initializePlayer()
{
	this->player_fight = new Player(300.f, 270.f, this->textures["FIGHT_IDLE"], "infight");
	this->playerHp = this->player_fight->getStatsHP();
	this->playerDef = this->player_fight->getStatsDefence();
	this->playerMana = this->player_fight->getStatsMana();
	this->playerExp = this->player_fight->getStatsExp();
}

void FightState::initializeBackground()
{
	this->background.setSize
	(sf::Vector2f
	(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y))
	);

	if (!this->bgimage.loadFromFile("Resources/Images/Backgrounds/FightStatebg.png"))
	{
		throw "ERROR FIGHTSTATE::BACKGROUND_LOADING_FAILED";
	}
	this->background.setTexture(&this->bgimage);
}

void FightState::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/Neucha-Regular.ttf"))
	{
		throw("ERROR::MAINMENUSTATE - FONT NOT LOADED"); //exits program and gives the "Error"
	}
}

void FightState::initializeKeybinds()
{
	std::ifstream file("Config/fightstate_keybinds.ini");

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

void FightState::initializeButtons()
{
	this->buttons["FIGHT"] = new Button(40.f, 950.f, 355.f, 70.f,
		&this->font, "fight", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	this->buttons["DEFEND"] = new Button(525.f, 950.f, 355.f, 70.f,
		&this->font, "defend", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	this->buttons["USE_ITEM"] = new Button(1010.f, 950.f, 355.f, 70.f,
		&this->font, "use item", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	this->buttons["RUN"] = new Button(1495.f, 950.f, 355.f, 70.f,
		&this->font, "run", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));
}

FightState::FightState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<States*>* states, Enemy* enemy, std::string enemyName)
	:States(window, supportedKeys, states)
{
	this->initializeVariables();
	this->initializePlayer();
	this->initializeTextures();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeKeybinds();
	this->initializeButtons();

	this->enemyCount = rand() % 4 + 1;
	this->enemies = new Enemy * [this->enemyCount];
	float offsetx = 0.f;
	float offsety = 0.f;

	//enemies
	if (enemyName == "testenemy")
	{
		for (int i = 0; i < this->enemyCount; i++)
		{
			this->enemies[i] = new Enemy(1100.f + offsetx, 50.f + offsety, this->textures["TESTENEMY_FIGHT"], enemyName);
			offsetx += 20.f;
			offsety += 20.f;
			this->enemyHp = enemies[i]->getEnemyHP() * (this->enemyCount);
			this->enemyExp = enemies[i]->getEnemyExp() * (this->enemyCount);
		}
	}

	if (enemyName == "blob")
	{
		for (int i = 0; i < this->enemyCount; i++)
		{
			this->enemies[i] = new Enemy(1100.f + offsetx, 50.f + offsety, this->textures["BLOB_FIGHT"], enemyName);
			offsetx += 20.f;
			offsety += 20.f;
			this->enemyHp = enemies[i]->getEnemyHP() * (this->enemyCount);
			this->enemyExp = enemies[i]->getEnemyExp() * (this->enemyCount);
		}
	}

	if (enemyName == "snake")
	{
		for (int i = 0; i < this->enemyCount; i++)
		{
			this->enemies[i] = new Enemy(1100.f + offsetx, 50.f + offsety, this->textures["SNAKE_FIGHT"], enemyName);
			offsetx += 20.f;
			offsety += 20.f;
			this->enemyHp = enemies[i]->getEnemyHP() * (this->enemyCount);
			this->enemyExp = enemies[i]->getEnemyExp() * (this->enemyCount);
		}
	}

	std::cout << "\n hp" << enemyHp << enemyName << "\n exp" << enemyExp;			//for testing del later
	std::cout << "\n hp" << playerHp << "\n mana" << playerMana << "\n exp" << playerExp;
}

FightState::~FightState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	for (int i = 0; i < enemyCount; ++i)
	{
		delete[] enemies[i];
	}
	delete[] enemies;

	delete this->player_fight;
} 

void FightState::updateInput(const float& dtime)
{

}

void FightState::updateButtons()
{
	for (auto i : this->buttons)
	{
		i.second->update(this->mousePositionView);
	}

	//fighting
	if (this->buttons["FIGHT"]->isPressed())
	{
		std::cout << "fight\n";

		this->buttons.clear();
	}

	//fighting
	if (this->buttons["DEFEND"]->isPressed())
	{
		std::cout << "defend\n";
	}

	//fighting
	if (this->buttons["USE_ITEM"]->isPressed())
	{
		std::cout << "using item\n";
	}

	//Finish fight
	if (this->buttons["RUN"]->isPressed())
	{
		this->states->pop();
	}
}

void FightState::update(const float& dtime)
{
	this->updateMousePositions();
	this->updateInput(dtime);

	this->updateButtons();
}

void FightState::renderButtons(sf::RenderTarget& target)
{
	for (auto i : this->buttons)
	{
		i.second->render(target);
	}
	for (int i = 0; i < this->enemyCount; i++)
	{
		this->enemies[i]->render(target);
	}
}

void FightState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->player_fight->render(*target);

	this->renderButtons(*target);
}
