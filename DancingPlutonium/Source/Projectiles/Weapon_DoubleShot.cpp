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
	//SetPosition(sf::Vector2f(GetPosition().x, GetPosition().y - _dt * speed));

	// get that double shot action boiyee
	auto leftboi = leftProjectile->GetPosition();
	leftboi.y -= _dt * speed * allegiance;
	leftProjectile->SetPosition(leftboi);
	auto rightboi = rightProjectile->GetPosition();
	rightboi.y -= _dt * speed * allegiance;
	rightProjectile->SetPosition(rightboi);
}

void DancingPlutonium::Weapon_DoubleShot::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(leftProjectile->GetSprite());
	_rt.draw(rightProjectile->GetSprite());
}

std::vector<sf::FloatRect> DancingPlutonium::Weapon_DoubleShot::GetBounds()
{
	auto leftBounds = leftProjectile->GetSprite();
	auto rightBounds = rightProjectile->GetSprite();

	std::vector<sf::FloatRect> retVal = std::vector<sf::FloatRect>();
	retVal.push_back(leftBounds.getGlobalBounds());
	retVal.push_back(rightBounds.getGlobalBounds());

	return retVal;
}

bool DancingPlutonium::Weapon_DoubleShot::GetActiveState(const sf::RenderTarget& _rt)
{
	if ((leftProjectile->GetPosition().y < 0 || leftProjectile->GetPosition().x < 0 ||
		leftProjectile->GetPosition().y > _rt.getSize().y || leftProjectile->GetPosition().x > _rt.getSize().x) &&
		(rightProjectile->GetPosition().y < 0 || rightProjectile->GetPosition().x < 0 ||
			rightProjectile->GetPosition().y > _rt.getSize().y || rightProjectile->GetPosition().x > _rt.getSize().x))
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::vector<sf::Sprite> DancingPlutonium::Weapon_DoubleShot::GetAllSprites()
{
	auto leftSprite = leftProjectile->GetSprite();
	auto rightSprite = rightProjectile->GetSprite();

	std::vector<sf::Sprite> retVal = std::vector<sf::Sprite>();
	retVal.push_back(leftSprite);
	retVal.push_back(rightSprite);

	return retVal;
}
