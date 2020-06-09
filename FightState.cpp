#include "pch.h"
#include "FightState.h"

void FightState::initializeVariables()
{
	this->enemydead = false;
	this->playerdead = false;
	this->turn = true;

	this->enemyCount = 1;
	this->gainEXP = 0;
}

void FightState::initializeTextures()
{
	if (!this->textures["FIGHT_IDLE"].loadFromFile("Resources/Images/Sprites/Player/FightState_Liam.png"))
	{
		throw "ERROR::FIGHT_STATE::PLAYER_FIGHT_FRONT_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}

	if (!this->textures["BAR"].loadFromFile("Resources/Images/Bars/barbg.png"))
	{
		throw "ERROR::FIGHT_STATE::PLAYER_FIGHT_FRONT_TEXTURE_DIDN'T_LOAD_PROPERLY";
	}

	if (!this->textures["HP"].loadFromFile("Resources/Images/Bars/hpbar.png"))
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
	//fighting
	this->buttons["FIGHT"] = new Button(40.f, 950.f, 355.f, 70.f,
		&this->font, "fight", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	//defending
	this->buttons["DEFEND"] = new Button(525.f, 950.f, 355.f, 70.f,
		&this->font, "defend", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	//items
	this->buttons["USE_ITEM"] = new Button(1010.f, 950.f, 355.f, 70.f,
		&this->font, "use item", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));

	//runnin
	this->buttons["RUN"] = new Button(1495.f, 950.f, 355.f, 70.f,
		&this->font, "run", 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));
}

void FightState::initializeBars()
{
	//player
	this->playerBarWidth = playerHp * 1.f;
	this->PlayerBarHp.setPosition(45.f, 655.f);
	this->PlayerBarHp.setTexture(&this->textures["HP"]);
	this->PlayerBarHp.setSize(sf::Vector2f(playerBarWidth, 30.f));

	this->playerBar = new Bar(40.f, 650.f, playerBarWidth + 10.f, 40.f, &this->textures["BAR"]);

	//enemy
	this->enemyBarWidth = enemyHp * 1.f;
	this->enemyBarHp.setPosition(1015.f, 655.f);
	this->enemyBarHp.setTexture(&this->textures["HP"]);
	this->enemyBarHp.setSize(sf::Vector2f(enemyBarWidth, 30.f));

	this->enemyBar = new Bar(1010.f, 650.f, enemyBarWidth + 10.f, 40.f, &this->textures["BAR"]);
}

FightState::FightState(StateData* state_data, Enemy* enemy, std::string enemyName)
	: States(state_data), keytimeMax(1.f), keytime(0.f)
{
	this->initializeVariables();
	this->initializePlayer();
	this->initializeTextures();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeKeybinds();
	this->initializeButtons();

	//player
	this->player_fight->loadStatsFromFile("player_stats.txt", this->playerHp, this->playerDef, this->playerBaseDMG, this->playerMaxDMG, this->playerMana, this->playerCurrentExp, this->playerLvl, this->playerdead);
	this->playerExp = this->playerCurrentExp;

	std::cout << "\nHP" << playerHp << "\nDEF" << playerDef << "\nEXP" << playerExp << "\n";

	//enemy
	this->enemyCount = rand() % 3 + 1;
	this->enemies = new Enemy * [this->enemyCount];
	this->enemyHp = 0;
	float offsetx = 0.f;
	float offsety = 0.f;

	//enemies
	if (enemyName == "testenemy")
	{
		for (int i = 0; i < this->enemyCount; i++)
		{
			this->enemies[i] = new Enemy(1100.f + offsetx, 50.f + offsety, this->textures["TESTENEMY_FIGHT"], enemyName, INFIGHT);
			currentEnemies.push_back(enemies[i]);

			offsetx += 20.f;
			offsety += 20.f;
			runChance = 9;

			this->enemyHp = enemies[i]->getEnemyHP() + this->enemyHp;
			this->enemyExp = enemies[i]->getEnemyExp() * (this->enemyCount);
			this->enemyDMG = (rand() % enemies[i]->getEnemyMaxDMG() + enemies[i]->getEnemyBaseDMG()) * (this->enemyCount);
		}
	}

	else if (enemyName == "blob")
	{
		for (int i = 0; i < this->enemyCount; i++)
		{
			this->enemies[i] = new Enemy(1100.f + offsetx, 50.f + offsety, this->textures["BLOB_FIGHT"], enemyName, INFIGHT);
			currentEnemies.push_back(enemies[i]);

			offsetx += 20.f;
			offsety += 20.f;
			runChance = 9;

			this->enemyHp = enemies[i]->getEnemyHP() + this->enemyHp;
			this->enemyExp = enemies[i]->getEnemyExp() * (this->enemyCount);
			this->enemyDMG = (rand() % enemies[i]->getEnemyMaxDMG() + enemies[i]->getEnemyBaseDMG()) * (this->enemyCount);
		}
	}

	else if (enemyName == "snake")
	{
		for (int i = 0; i < this->enemyCount; i++)
		{
			this->enemies[i] = new Enemy(1100.f + offsetx, 50.f + offsety, this->textures["SNAKE_FIGHT"], enemyName, INFIGHT);
			currentEnemies.push_back(enemies[i]);

			offsetx += 20.f;
			offsety += 20.f;
			runChance = 8;

			this->enemyHp = enemies[i]->getEnemyHP() + this->enemyHp;
			this->enemyExp = enemies[i]->getEnemyExp() * (this->enemyCount);
			this->enemyDMG = (rand() % enemies[i]->getEnemyMaxDMG() + enemies[i]->getEnemyBaseDMG()) * (this->enemyCount);
		}
	}

	std::cout << "\nENEMY  hp" << enemyHp << enemyName << "\n exp" << enemyExp << "\nDMG" << enemyDMG;			//for testing del later

	this->initializeBars();
}

FightState::~FightState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	for (int i = 0; i < enemyCount; i++)
	{
		delete[] enemies[i];
	}
	delete[] enemies;

	this->currentEnemies.clear();
	delete this->player_fight;

	delete this->enemyBar;
	delete this->playerBar;
}

//functions
void FightState::enemyAttack()
{
	playerHp = playerHp - enemyDMG;

	playerBarWidth = playerHp * 1.f;

	std::cout << "\nenemy attack PlayerHP:" << playerHp << "\n";

	if (playerHp <= 0)
	{
		playerdead = true;
	}
}

void FightState::attack()
{
	playerDMG = (rand() % this->playerMaxDMG + this->playerBaseDMG);

	enemyHp = enemyHp - playerDMG;

	enemyBarWidth = enemyHp * 1.f;

	std::cout << "\nplayer attack, EnemyHP:" << enemyHp << "\n";

	if (enemyHp <= 0)
	{
		enemydead = true;
	}
}

void FightState::defend()
{
	playerBarWidth = playerHp * 1.f;

	if(playerDef < enemyDMG)
		playerHp = playerHp + playerDef - enemyDMG;

	std::cout << "\nplayer defence PlayerHP:" << playerHp << "\n";

	if (playerHp <= 0)
	{
		playerdead = 1;
	}
}

void FightState::useItem()
{
	std::cout << "\nusing item\n";
}

void FightState::tryRun()
{
	int escaped = rand() % 10 + 1;
	if (this->runChance >= escaped)
	{
		this->endState();
		turn = true;
	}
	else
	{
		playerHp = playerHp - enemyDMG;

		playerBarWidth = playerHp * 1.f;

		std::cout << "\nCouldn't escape the battle!\n";
		turn = false;
	}
}

void FightState::checkIfAnyoneDead()
{
	if (enemydead == true)
	{
		std::cout << "wygrana\n";
		playerExp = playerExp + enemyExp;
		std::cout << "EXP gain: " << playerExp << "\n";

		this->player_fight->saveStatsToFile("player_stats.txt", this->playerHp, this->playerDef, this->playerBaseDMG, this->playerMaxDMG, this->playerMana, this->playerExp, this->playerLvl, this->playerdead);

		currentEnemies.clear();

		this->endState();
	}
	else if (playerdead == 1)
	{
		playerHp = 0;

		playerBarWidth = 1 * 1.f;

		this->player_fight->saveStatsToFile("player_stats.txt", this->playerHp, this->playerDef, this->playerBaseDMG, this->playerMaxDMG, this->playerMana, this->playerExp, this->playerLvl, this->playerdead);

		this->endState();
	}
}

void FightState::changeBarSize()
{
	this->playerBarWidth = playerHp * 1.f;
	this->PlayerBarHp.setSize(sf::Vector2f(playerBarWidth, 30.f));

	this->enemyBarWidth = enemyHp * 1.f;
	this->enemyBarHp.setSize(sf::Vector2f(enemyBarWidth, 30.f));
}

const bool FightState::getKeyTime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void FightState::updateInput(const float& dtime)
{

}

void FightState::updateKeyTime(const float& dtime)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 5.f * dtime;
	}
}

void FightState::updateButtons(const float& dtime)
{
	this->updateKeyTime(dtime);

	for (auto i : this->buttons)
	{
		i.second->update(this->mousePositionWindow);
	}

	//fighting
	if (turn == true)
	{

		if (this->buttons["FIGHT"]->isPressed() && this->getKeyTime())
		{
			attack();
			changeBarSize();
			turn = false;
		}

		//fighting
		if (this->buttons["DEFEND"]->isPressed() && this->getKeyTime())
		{
			defend();
			changeBarSize();
			turn = false;
		}

		//fighting
		if (this->buttons["USE_ITEM"]->isPressed() && this->getKeyTime())
		{
			useItem();
			changeBarSize();
			turn = false;
		}

		//Finish fight
		if (this->buttons["RUN"]->isPressed() && this->getKeyTime())
		{
			tryRun();

			changeBarSize();
			turn = true;
		}
		checkIfAnyoneDead();
	}

	//enemyTurn
	if (turn == false)
	{
		enemyAttack();

		changeBarSize();
		checkIfAnyoneDead();

		turn = true;
	}
}

void FightState::update(const float& dtime)
{
	this->updateMousePositions();
	this->updateKeyTime(dtime);
	this->updateInput(dtime);

	this->updateButtons(dtime);
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
	this->playerBar->render(target);
	target.draw(PlayerBarHp);

	this->enemyBar->render(target);
	target.draw(enemyBarHp);
}

void FightState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->player_fight->render(*target);

	this->renderButtons(*target);
}
