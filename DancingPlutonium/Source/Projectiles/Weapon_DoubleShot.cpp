#include "Weapon_DoubleShot.h"

DancingPlutonium::Weapon_DoubleShot::Weapon_DoubleShot(const sf::Vector2f& _pos)
{
	leftProjectile = new Weapon_BasicShot(_pos);
	rightProjectile = new Weapon_BasicShot(_pos);
	position = _pos;
	speed = defaultSpeed;
	damage = defaultDamage;
	innert = false;
	SetSprite(_pos);
}

DancingPlutonium::Weapon_DoubleShot::Weapon_DoubleShot(const sf::Vector2f& _pos, const float& _dmg, const float& _vel, const short& _alle)
{
	leftProjectile = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::BasicShot, _pos, _dmg, _vel, _alle);
	rightProjectile = BulletFactory::GetProjectile(AbstractBaseProjectile::ProjectilePattern::BasicShot, _pos, _dmg, _vel, _alle);
	position = _pos;
	damage = defaultDamage * _dmg;
	speed = _vel * defaultSpeed;
	allegiance = _alle;
	leftProjectile->SetDamage(damage);
	rightProjectile->SetDamage(damage);
	leftProjectile->SetSpeed(speed);
	rightProjectile->SetSpeed(speed);
	SetSprite(position);
	innert = false;
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
	if (leftProjectile->IsInnert() == false)
	{
		auto leftboi = leftProjectile->GetPosition();
		leftboi.y -= _dt * speed * allegiance;
		leftProjectile->SetPosition(leftboi);
	}
	if (rightProjectile->IsInnert() == false)
	{
		auto rightboi = rightProjectile->GetPosition();
		rightboi.y -= _dt * speed * allegiance;
		rightProjectile->SetPosition(rightboi);
	}
}

void DancingPlutonium::Weapon_DoubleShot::Draw(sf::RenderTarget& _rt)
{
	if (leftProjectile->IsInnert() == false)
	{
		_rt.draw(leftProjectile->GetSprite());
	}
	if (rightProjectile->IsInnert() == false)
	{
		_rt.draw(rightProjectile->GetSprite());
	}
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

std::vector<DancingPlutonium::AbstractBaseProjectile*> DancingPlutonium::Weapon_DoubleShot::GetAllComponentBullets()
{
	auto retVal = std::vector<AbstractBaseProjectile*>();

	retVal.push_back(leftProjectile);
	retVal.push_back(rightProjectile);

	return retVal;
}
