#include "pch.h"
#include "GameOver.h"

//initializer functions
GameOver::GameOver(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//init bg
	this->background.setSize(sf::Vector2f
	(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y))
	);

	this->background.setFillColor(sf::Color(56, 49, 51, 200));

	//init button
	this->box.setSize(sf::Vector2f
	(
		static_cast<float>(window.getSize().x / 2.f),
		static_cast<float>(window.getSize().y - 90.f))
	);

	this->box.setFillColor(sf::Color(99, 65, 78, 160));
	this->box.setPosition(window.getSize().x / 2.f - this->box.getSize().x / 2.f, 30.f);

	//init text
	this->menutext.setFont(font);
	this->menutext.setFillColor(sf::Color(237, 221, 226, 200));
	this->menutext.setCharacterSize(80);
	this->menutext.setString("GAME OVER");
	this->menutext.setPosition(this->box.getPosition().x + this->box.getSize().x / 2.f - this->menutext.getGlobalBounds().width / 2.f, this->box.getPosition().y + 70.f);
}

GameOver::~GameOver()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, Button*>& GameOver::getButtons()
{
	return this->buttons;
}

//functions
void GameOver::addButton(const std::string key, float x, float y, const std::string text)
{
	this->buttons[key] = new Button(x, y, 400.f, 60.f,
		&this->font, text, 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),		//text color
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));
}

const bool GameOver::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void GameOver::update(const sf::Vector2i& mousePositionWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePositionWindow);					//make an update key time for this too (one for buttons is in fightstate)
	}
}

void GameOver::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->box);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menutext);
}