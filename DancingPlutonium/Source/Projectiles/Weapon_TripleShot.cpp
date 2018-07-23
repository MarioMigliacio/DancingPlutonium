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

std::vector<sf::FloatRect> DancingPlutonium::Weapon_TripleShot::GetBounds()
{
	auto leftBounds = leftProjectile->GetSprite();
	auto midBounds = centerProjectile->GetSprite();
	auto rightBounds = rightProjectile->GetSprite();

	std::vector<sf::FloatRect> retVal = std::vector<sf::FloatRect>();
	retVal.push_back(leftBounds.getGlobalBounds());
	retVal.push_back(midBounds.getGlobalBounds());
	retVal.push_back(rightBounds.getGlobalBounds());

	return retVal;
}

bool DancingPlutonium::Weapon_TripleShot::GetActiveState(const sf::RenderTarget& _rt)
{
	if ((leftProjectile->GetPosition().y < 0 || leftProjectile->GetPosition().x < 0 ||
		leftProjectile->GetPosition().y > _rt.getSize().y || leftProjectile->GetPosition().x > _rt.getSize().x) &&
		(centerProjectile->GetPosition().y < 0 || centerProjectile->GetPosition().x < 0 ||
			centerProjectile->GetPosition().y > _rt.getSize().y || centerProjectile->GetPosition().x > _rt.getSize().x) &&
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

std::vector<sf::Sprite> DancingPlutonium::Weapon_TripleShot::GetAllSprites()
{
	auto leftSprite = leftProjectile->GetSprite();
	auto midSprite = centerProjectile->GetSprite();
	auto rightSprite = rightProjectile->GetSprite();

	std::vector<sf::Sprite> retVal = std::vector<sf::Sprite>();
	retVal.push_back(leftSprite);
	retVal.push_back(midSprite);
	retVal.push_back(rightSprite);

	return retVal;
}
