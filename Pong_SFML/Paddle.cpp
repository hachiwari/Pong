#include "Paddle.h"

Paddle::Paddle(RenderWindow &Window, Settings &Settings, Vector2f Size, Color Color)
{
	_PaddleObject.setSize(Size);
	_PaddleObject.setFillColor(Color);

	this->_Window = &Window;
	this->_Settings = &Settings;
}

Paddle::~Paddle()
{
}

void Paddle::initPaddle(Vector2f Position)
{
	_PaddleObject.setPosition(Position);
}

void Paddle::draw()
{
	_Window->draw(_PaddleObject);
}

void Paddle::move(float deltaTime, controlPaddle control)
{
	if (control == UP)
	{
		_PaddleObject.move(0, -PADDLE_SPEED * deltaTime);
	}
	else if (control == DOWN)
	{
		_PaddleObject.move(Vector2f(0, PADDLE_SPEED * deltaTime));
	}
}

bool Paddle::isCollision(RectangleShape Rectangle)
{
	if (_PaddleObject.getGlobalBounds().intersects(Rectangle.getGlobalBounds()))
		return true;

	return false;
}

void Paddle::setPosition(Vector2f Position)
{
	_PaddleObject.setPosition(Position);
}

Vector2f Paddle::getPosition()
{
	return _PaddleObject.getPosition();
}

FloatRect Paddle::getRect()
{
	return _PaddleObject.getGlobalBounds();
}

Vector2f Paddle::getSize()
{
	return _PaddleObject.getSize();
}
