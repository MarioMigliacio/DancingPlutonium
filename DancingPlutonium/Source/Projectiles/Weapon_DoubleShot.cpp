#include "Weapon_DoubleShot.h"

DancingPlutonium::Weapon_DoubleShot::Weapon_DoubleShot(const sf::Vector2f& _pos)
{
	leftProjectile = new Weapon_BasicShot(_pos);
	rightProjectile = new Weapon_BasicShot(_pos);
	position = _pos;
	speed = 190.0f;
	SetSprite(_pos);
}

DancingPlutonium::Weapon_DoubleShot::~Weapon_DoubleShot()
{
	delete leftProjectile;
	delete rightProjectile;
}

void DancingPlutonium::Weapon_DoubleShot::SetSprite(const sf::Vector2f& _origin)
{
	auto leftBoi = leftProjectile->GetPosition();
	leftBoi.x -= 5.0f;
	leftProjectile->SetPosition(leftBoi);
	auto rightBoi = rightProjectile->GetPosition();
	rightBoi.x += 5.0f;
	rightProjectile->SetPosition(rightBoi);
}

void DancingPlutonium::Weapon_DoubleShot::Update(float _dt)
{
	SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - _dt * speed));

	// get that double shot action boiyee
	auto leftboi = leftProjectile->GetPosition();
	leftboi.y -= _dt * speed;
	leftProjectile->SetPosition(leftboi);
	auto rightboi = rightProjectile->GetPosition();
	rightboi.y -= _dt * speed;
	rightProjectile->SetPosition(rightboi);
}

void DancingPlutonium::Weapon_DoubleShot::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(leftProjectile->GetSprite());
	_rt.draw(rightProjectile->GetSprite());
}
