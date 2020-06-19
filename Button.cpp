#include "pch.h"
#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned font_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor)
{
	//button time 
	this->buttonTime = 0.f;
	this->buttonTimeMax = 5.f;

	//button
	this->buttonState = BUTTON_IDLE;

	this->buttonshape.setSize(sf::Vector2f(width, height));
	this->buttonshape.setPosition(sf::Vector2f(x, y));

	//button colors
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->buttonshape.setFillColor(idleColor);

	//text 
	this->font = font;
	this->fontSize = font_size;
	this->buttontext.setFont(*this->font);
	this->buttontext.setString(text);
	this->buttontext.setFillColor(text_idle_color);
	this->buttontext.setCharacterSize(font_size);
	this->buttontext.setPosition(
		this->buttonshape.getPosition().x + (this->buttonshape.getGlobalBounds().width / 2.f) - this->buttontext.getGlobalBounds().width / 2.f,
		this->buttonshape.getPosition().y + (this->buttonshape.getGlobalBounds().height / 2.f) - this->buttontext.getGlobalBounds().height / 1.5f
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;
}

Button::~Button()
{

}

//accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BUTTON_PRESSED)
	{
		return true;
	}
	return false;
}

//functions
void Button::update(const sf::Vector2i& mousePositionWindow)
{
	//update the bool for hover and pressed button

	this->buttonState = BUTTON_IDLE;

	//hover
	if (this->buttonshape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePositionWindow)))
	{
		this->buttonState = BUTTON_HOVER;

		//pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BUTTON_PRESSED;
		}
	}

	switch (this->buttonState)
	{
	case BUTTON_IDLE:
		this->buttonshape.setFillColor(this->idleColor);
		this->buttontext.setFillColor(this->textIdleColor);
		break;

	case BUTTON_HOVER:
		this->buttonshape.setFillColor(this->hoverColor);
		this->buttontext.setFillColor(this->textHoverColor);
		break;

	case BUTTON_PRESSED:
		this->buttonshape.setFillColor(this->pressedColor);
		this->buttontext.setFillColor(this->textActiveColor);
		break;

	default:
		this->buttonshape.setFillColor(sf::Color::Red);	
		this->buttontext.setFillColor(sf::Color::Black); //"error"
		break;
	}

}

const bool Button::getButtonTime()
{
	if (this->buttonTime >= this->buttonTimeMax)
	{
		//resets the button time
		this->buttonTime = 0.f;
		return true;
	}

	return false;
}

void Button::updateButtonTime(const float& dtime)
{
	if (this->buttonTime < this->buttonTimeMax)
	{
		this->buttonTime += 100.f * dtime;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->buttonshape);
	target.draw(this->buttontext);
}
