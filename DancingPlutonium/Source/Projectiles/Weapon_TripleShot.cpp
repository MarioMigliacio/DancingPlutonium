#include "Weapon_TripleShot.h"

DancingPlutonium::Weapon_TripleShot::Weapon_TripleShot(const sf::Vector2f& _pos)
{
	leftProjectile = new Weapon_BasicShot(_pos);
	centerProjectile = new Weapon_BasicShot(_pos);
	rightProjectile = new Weapon_BasicShot(_pos);
	position = _pos;
	speed = defaultSpeed;
	damage = defaultDamage;
	innert = false;
}

DancingPlutonium::Weapon_TripleShot::Weapon_TripleShot(const sf::Vector2f& _pos, const float& _dmg, const float& _vel, const short& _alle)
{
	leftProjectile = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::BasicShot, _pos, _dmg, _vel, _alle);
	centerProjectile = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::BasicShot, _pos, _dmg, _vel, _alle);
	rightProjectile = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::BasicShot, _pos, _dmg, _vel, _alle);
	position = _pos;
	damage = defaultDamage * _dmg;
	speed = _vel * defaultSpeed;
	allegiance = _alle;
	leftProjectile->SetDamage(damage);
	centerProjectile->SetDamage(damage);
	rightProjectile->SetDamage(damage);
	leftProjectile->SetSpeed(speed);
	centerProjectile->SetSpeed(speed);
	rightProjectile->SetSpeed(speed);
	SetSprite(position);
	innert = false;
}

DancingPlutonium::Weapon_TripleShot::~Weapon_TripleShot()
{
	delete leftProjectile;
	delete centerProjectile;
	delete rightProjectile;
}

void DancingPlutonium::Weapon_TripleShot::SetSprite(const sf::Vector2f& _origin)
{
	// since the basic shots origin is the point of which we want all three shots to start from, do nothing.
}

void DancingPlutonium::Weapon_TripleShot::Update(float _dt)
{
	if (leftProjectile->IsInnert() == false)
	{
		auto leftboi = leftProjectile->GetPosition();
		leftboi.x -= (_dt * speed) * .33f;
		leftboi.y -= _dt * speed * allegiance;
		leftProjectile->SetPosition(leftboi);
	}
	if (centerProjectile->IsInnert() == false)
	{
		auto centerboi = centerProjectile->GetPosition();
		centerboi.y -= _dt * speed * allegiance;
		centerProjectile->SetPosition(centerboi);
	}
	if (rightProjectile->IsInnert() == false)
	{
		auto rightboi = rightProjectile->GetPosition();
		rightboi.x += (_dt * speed) * .33f;
		rightboi.y -= _dt * speed * allegiance;
		rightProjectile->SetPosition(rightboi);
	}
}

void DancingPlutonium::Weapon_TripleShot::Draw(sf::RenderTarget& _rt)
{
	if (leftProjectile->IsInnert() == false)
	{
		_rt.draw(leftProjectile->GetSprite());
	}
	
	if (centerProjectile->IsInnert() == false)
	{
		_rt.draw(centerProjectile->GetSprite());
	}
	
	if (rightProjectile->IsInnert() == false)
	{
		_rt.draw(rightProjectile->GetSprite());
	}	
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

std::vector<DancingPlutonium::AbstractBaseProjectile*> DancingPlutonium::Weapon_TripleShot::GetAllComponentBullets()
{
	auto retVal = std::vector<AbstractBaseProjectile*>();

	retVal.push_back(leftProjectile);
	retVal.push_back(centerProjectile);
	retVal.push_back(rightProjectile);

	return retVal;
}
