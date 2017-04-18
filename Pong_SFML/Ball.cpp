#include "Ball.h"

Vector2f Speed(0.2f, 0.2f);

Ball::Ball(RenderWindow &Window, Settings &Settings, float Radius)
{
	if (!_PaddleHit.loadFromFile("pack/Audio/paddleHit.wav"))
	{
		cout << "Error - no files (pack/Audio/paddleHit.wav)" << endl;
		exit(0);
	}
#ifdef _DEBUG
	else
		cout << "Ball# - Audio loaded" << endl;
#endif

	this->_Window = &Window;
	this->_Settings = &Settings;
	this->_fRadius = Radius;

	_SoundPaddleHit.setBuffer(_PaddleHit);
	_BallObject.setRadius(_fRadius);
}

Ball::~Ball()
{
}

void Ball::initBall(Vector2f Position)
{
	_BallObject.setPosition(Position);
	_vCurrentSpeed = Speed;

	_Color = _Settings->getDefaultColorBall();
	_BallObject.setFillColor(_Color);
}

void Ball::draw()
{
	_Window->draw(_BallObject);
}

void Ball::move()
{
	_BallObject.move(_vCurrentSpeed.x, _vCurrentSpeed.y);
}

bool Ball::isCollision(RectangleShape Rectangle)
{
	if (_BallObject.getGlobalBounds().intersects(Rectangle.getGlobalBounds()))
		return true;

	return false;
}

bool Ball::isCollision(FloatRect Rect)
{
	if (_BallObject.getGlobalBounds().intersects(Rect))
		return true;

	return false;
}

void Ball::reflection(axis axis)
{
	if (axis == X)
	{
		_vCurrentSpeed.x = -_vCurrentSpeed.x;

#ifdef _DEBUG
		cout << "reflectionX(" << _vCurrentSpeed.y << ") " << endl;
#endif
	}
	else if (axis == Y)
	{
		_vCurrentSpeed.y = -_vCurrentSpeed.y;

#ifdef _DEBUG
		cout << "reflectionY(" << _vCurrentSpeed.x << ") " << endl;
#endif
	}
}

void Ball::playHitSound()
{
	_SoundPaddleHit.play();
}

void Ball::acceleration(Paddle Paddle)
{
	_vCurrentSpeed.y = (_BallObject.getGlobalBounds().top + _BallObject.getGlobalBounds().height / 2 - Paddle.getRect().top - Paddle.getRect().height / 2) / 100;
}

void Ball::resetSpeed(int sign)
{
	_vCurrentSpeed = Speed;
	Speed.y = Speed.y * sign;
	Speed.x = Speed.x * sign;
}

Vector2f Ball::getPosition()
{
	return _BallObject.getPosition();
}

float Ball::getRadius()
{
	return _BallObject.getRadius();
}
