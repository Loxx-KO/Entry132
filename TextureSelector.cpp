#include "pch.h"
#include "TextureSelector.h"

TextureSelector::TextureSelector(float x, float y, float width, float heigth, float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string button_text)
	:keyTime(0.f), keyTimeMax(1.f)
{
	this->gridSize = gridSize;
	this->active = false;
	this->hidden = false;

	this->bounds.setSize(sf::Vector2f(width, heigth));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	this->hide_button = new Button(0.f, 20.f, 60.f, 60.f,
		&font, button_text, 24,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 200),
		sf::Color(176, 95, 95, 200), sf::Color(196, 106, 106, 200), sf::Color(224, 123, 123, 200));
}

TextureSelector::~TextureSelector()
{
	delete this->hide_button;
}

//accessors
const bool& TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool TextureSelector::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}

//functions
void TextureSelector::updateKeyTime(const float& dtime)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 5.f * dtime;
	}
}

void TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dtime)
{
	this->updateKeyTime(dtime);
	this->hide_button->update(mousePosWindow);

	if (this->hide_button->isPressed() && this->getKeyTime())
	{
		if (this->hidden)
		{
			this->hidden = false;
		}
		else
			this->hidden = true;
	}

	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->active = true;
		}
		else this->active = false;

		if (this->active)
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<int>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<int>(this->gridSize);
			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);

			//update texture rectangle after moving the selector
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void TextureSelector::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
			target.draw(this->selector);
	}
	this->hide_button->render(target);
}
