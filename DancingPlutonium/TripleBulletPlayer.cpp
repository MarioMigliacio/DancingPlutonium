#include "TripleBulletPlayer.h"
#include <iostream>

DancingPlutonium::TripleBulletPlayer::TripleBulletPlayer(const sf::Vector2f& _pos)
{
	leftProjectile = new BasicBulletPlayer(_pos);
	rightProjectile = new BasicBulletPlayer(_pos);
	position = _pos;
	speed = 100.0f;
	SetSprite(position);
}

DancingPlutonium::TripleBulletPlayer::~TripleBulletPlayer()
{
	delete leftProjectile;
	delete rightProjectile;
}

void DancingPlutonium::TripleBulletPlayer::SetSprite(const sf::Vector2f& _origin)
{
	texture.loadFromFile("Content/Images/BulletGreen.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
	sprite.setPosition(_origin);
	position = _origin;
}

void DancingPlutonium::TripleBulletPlayer::Update(float _dt)
{
	SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - _dt * speed));

	// get that side shot action boiyee
	auto leftboi = leftProjectile->GetPosition();
	leftboi.x -= (_dt * speed) * .33f;
	leftboi.y -= _dt * speed;
	leftProjectile->SetPosition(leftboi);
	auto rightboi = rightProjectile->GetPosition();
	rightboi.x += (_dt * speed) * .33f;
	rightboi.y -= _dt * speed;
	rightProjectile->SetPosition(rightboi);
}

void DancingPlutonium::TripleBulletPlayer::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
	_rt.draw(leftProjectile->GetSprite());
	_rt.draw(rightProjectile->GetSprite());
}
