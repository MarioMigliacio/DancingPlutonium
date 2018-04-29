#include "Weapon_TripleShot.h"

DancingPlutonium::Weapon_TripleShot::Weapon_TripleShot(const sf::Vector2f& _pos)
{
	leftProjectile = new Weapon_BasicShot(_pos);
	centerProjectile = new Weapon_BasicShot(_pos);
	rightProjectile = new Weapon_BasicShot(_pos);
	position = _pos;
	speed = 200.0f;
	SetSprite(position);
}

DancingPlutonium::Weapon_TripleShot::~Weapon_TripleShot()
{
	delete leftProjectile;
	delete centerProjectile;
	delete rightProjectile;
}

void DancingPlutonium::Weapon_TripleShot::SetSprite(const sf::Vector2f& _origin)
{
	/*auto leftBoi = leftProjectile->GetPosition();
	leftBoi.x -= 5.0f;
	leftProjectile->SetPosition(leftBoi);
	auto centerboi = centerProjectile->GetPosition();
	centerboi.x = 0.0f;
	centerProjectile->SetPosition(leftBoi);
	auto rightBoi = rightProjectile->GetPosition();
	rightBoi.x += 5.0f;
	rightProjectile->SetPosition(rightBoi);*/
}

void DancingPlutonium::Weapon_TripleShot::Update(float _dt)
{
	// get that side shot action boiyee
	auto leftboi = leftProjectile->GetPosition();
	leftboi.x -= (_dt * speed) * .33f;
	leftboi.y -= _dt * speed * allegiance;
	leftProjectile->SetPosition(leftboi);
	auto centerboi = centerProjectile->GetPosition();
	centerboi.y -= _dt * speed * allegiance;
	centerProjectile->SetPosition(centerboi);
	auto rightboi = rightProjectile->GetPosition();
	rightboi.x += (_dt * speed) * .33f;
	rightboi.y -= _dt * speed * allegiance;
	rightProjectile->SetPosition(rightboi);
}

void DancingPlutonium::Weapon_TripleShot::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(leftProjectile->GetSprite());
	_rt.draw(centerProjectile->GetSprite());
	_rt.draw(rightProjectile->GetSprite());
}
