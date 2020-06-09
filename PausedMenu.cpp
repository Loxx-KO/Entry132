#include "pch.h"
#include "PausedMenu.h"

PausedMenu::PausedMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//init bg
	this->background.setSize(sf::Vector2f
	(
		static_cast<float>(window.getSize().x), 
		static_cast<float>(window.getSize().y))
	);

	this->background.setFillColor(sf::Color(56, 49, 51, 100));

	//init button
	this->box.setSize(sf::Vector2f
	(
		static_cast<float>(window.getSize().x / 4.f),
		static_cast<float>(window.getSize().y - 90.f))
	);

	this->box.setFillColor(sf::Color(99, 65, 78, 160));
	this->box.setPosition(window.getSize().x / 2.f - this->box.getSize().x / 2.f, 30.f);

	//init text
	this->menutext.setFont(font);
	this->menutext.setFillColor(sf::Color(237, 221, 226, 200));
	this->menutext.setCharacterSize(80);
	this->menutext.setString("PAUSED");
	this->menutext.setPosition(this->box.getPosition().x + this->box.getSize().x / 2.f - this->menutext.getGlobalBounds().width / 2.f, this->box.getPosition().y + 70.f);
}

PausedMenu::~PausedMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, Button*>& PausedMenu::getButtons()
{
	return this->buttons;
}

//functions
void PausedMenu::addButton(const std::string key, float x, float y, const std::string text)
{
	this->buttons[key] = new Button(x, y , 400.f, 60.f,
		&this->font, text, 34,
		sf::Color(237, 221, 226, 200), sf::Color(247, 218, 231, 200), sf::Color(255, 235, 244, 200),		//text color
		sf::Color(125, 1, 47, 200), sf::Color(145, 1, 55, 200), sf::Color(166, 2, 63, 200));
}

const bool PausedMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PausedMenu::update(const sf::Vector2i& mousePositionWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePositionWindow);					//make an update key time for this too (one for buttons is in fightstate)
	}
}

void PausedMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->box);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
	//auto &i
	//T        // I'm copying this
	//T&       // I'm modifying this
	//const T& // I'm reading this

	target.draw(this->menutext);
}
