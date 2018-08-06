#include "Weapon_TripleShot.h"

DancingPlutonium::Weapon_TripleShot::Weapon_TripleShot(const sf::Vector2f& _pos)
{
	leftProjectile = new Weapon_BasicShot(_pos);
	centerProjectile = new Weapon_BasicShot(_pos);
	rightProjectile = new Weapon_BasicShot(_pos);
	position = _pos;
	speed = 200.0f;
	damage = 60.0f;
	innert = false;
}

DancingPlutonium::Weapon_TripleShot::~Weapon_TripleShot()
{
	delete leftProjectile;
	leftProjectile = NULL;
	delete centerProjectile;
	centerProjectile = NULL;
	delete rightProjectile;
	rightProjectile = NULL;
}

void DancingPlutonium::Weapon_TripleShot::SetSprite(const sf::Vector2f& _origin)
{
	// since the basic shots origin is the point of which we want all three shots to start from, do nothing.
}

void DancingPlutonium::Weapon_TripleShot::Update(float _dt)
{
	if (leftProjectile)
	{
		if (!leftProjectile->IsInnert())
		{
			auto leftboi = leftProjectile->GetPosition();
			leftboi.x -= (_dt * speed) * .33f;
			leftboi.y -= _dt * speed * allegiance;
			leftProjectile->SetPosition(leftboi);
		}
		else
		{
			delete leftProjectile;
			leftProjectile = NULL;
		}
	}
	if (!centerProjectile->IsInnert())
	{
		auto centerboi = centerProjectile->GetPosition();
		centerboi.y -= _dt * speed * allegiance;
		centerProjectile->SetPosition(centerboi);
	}
	else
	{
		delete centerProjectile;
		centerProjectile = NULL;
	}
	if (!rightProjectile->IsInnert())
	{
		auto rightboi = rightProjectile->GetPosition();
		rightboi.x += (_dt * speed) * .33f;
		rightboi.y -= _dt * speed * allegiance;
		rightProjectile->SetPosition(rightboi);
	}
	else
	{
		delete rightProjectile;
		rightProjectile = NULL;
	}
}

void DancingPlutonium::Weapon_TripleShot::Draw(sf::RenderTarget& _rt)
{
	if (leftProjectile)
	{
		if (!leftProjectile->IsInnert() && leftProjectile->GetActiveState(_rt))
		{
			_rt.draw(leftProjectile->GetSprite());
		}
	}
	if (centerProjectile)
	{
		if (!centerProjectile->IsInnert() && centerProjectile->GetActiveState(_rt))
		{
			_rt.draw(centerProjectile->GetSprite());
		}
	}
	if (rightProjectile)
	{
		if (!rightProjectile->IsInnert() && rightProjectile->GetActiveState(_rt))
		{
			_rt.draw(rightProjectile->GetSprite());
		}
	}
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
	// NEW: if a bullet goes off screen it should be treated the same as innert, and in new updates innert bullets get cleaned up
	if ((leftProjectile->GetPosition().y < 0 || leftProjectile->GetPosition().x < 0 ||
		leftProjectile->GetPosition().y > _rt.getSize().y || leftProjectile->GetPosition().x > _rt.getSize().x))
	{
		leftProjectile->RenderInnert();
	}
	if ((centerProjectile->GetPosition().y < 0 || centerProjectile->GetPosition().x < 0 ||
		centerProjectile->GetPosition().y > _rt.getSize().y || centerProjectile->GetPosition().x > _rt.getSize().x))
	{
		centerProjectile->RenderInnert();
	}
	if ((rightProjectile->GetPosition().y < 0 || rightProjectile->GetPosition().x < 0 ||
		rightProjectile->GetPosition().y > _rt.getSize().y || rightProjectile->GetPosition().x > _rt.getSize().x))
	{
		rightProjectile->RenderInnert();
	}

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

std::vector<DancingPlutonium::AbstractBaseProjectile*> DancingPlutonium::Weapon_TripleShot::GetAllComponentBullets()
{
	auto retVal = std::vector<AbstractBaseProjectile*>();

	retVal.push_back(leftProjectile);
	retVal.push_back(centerProjectile);
	retVal.push_back(rightProjectile);

	return retVal;
}
