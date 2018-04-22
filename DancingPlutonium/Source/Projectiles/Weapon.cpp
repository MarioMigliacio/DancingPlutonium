#include "Weapon.h"

sf::Uint32 DancingPlutonium::Weapon::weaponPattern = ProjectilePattern::NoBullet;

DancingPlutonium::Weapon::Weapon()
{
	SetPattern(ProjectilePattern::BasicShot);
	ammunition = std::vector<Projectile*>();
	accumulator = 0.0f;
}

DancingPlutonium::Weapon::~Weapon()
{
	for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
	{
		delete ammunition[i];
		ammunition.erase(ammunition.begin() + i);		
	}
}

void DancingPlutonium::Weapon::AddMunition(sf::Vector2f& _pos)
{
	/* it did */
	Projectile* omgDoesThisWork;

	switch (weaponPattern)
	{
		case ProjectilePattern::BasicShot:
			omgDoesThisWork = BulletFactory::GetProjectile(ProjectilePattern::BasicShot, _pos);
			ammunition.push_back(omgDoesThisWork);
			break;
		case ProjectilePattern::IncendiaryShot:
			break;
		case ProjectilePattern::GrowingShot:
			omgDoesThisWork = BulletFactory::GetProjectile(ProjectilePattern::GrowingShot, _pos);
			ammunition.push_back(omgDoesThisWork);
			break;
		case ProjectilePattern::AimedShot:
			break;
		case ProjectilePattern::DoubleShot:
			break;
		case ProjectilePattern::HomingShot:
			break;
		case ProjectilePattern::TripleShot:
			omgDoesThisWork = BulletFactory::GetProjectile(ProjectilePattern::TripleShot, _pos);
			ammunition.push_back(omgDoesThisWork);
			break;
		case ProjectilePattern::StandardLazer:
			break;
		case ProjectilePattern::JoesLazer:
			break;
		case ProjectilePattern::QuadShot:
			break;
		case ProjectilePattern::PhotonPacket:
			break;
		case ProjectilePattern::PhotonStream:
			break;
		case ProjectilePattern::PhotonTriplet:
			break;
		case ProjectilePattern::PhotonQuartet:
			break;
		default:
			break;
	}
}

DancingPlutonium::Projectile* DancingPlutonium::Weapon::GetIndexOfAmmunition(int _index)
{
	if (static_cast<int>(ammunition.size()) > 0 && static_cast<int>(ammunition.size()) > _index)
	{
		return ammunition[_index];
	}

	return nullptr;
}

int DancingPlutonium::Weapon::GetSizeOfAmmunition()
{
	return static_cast<int>(ammunition.size());
}

void DancingPlutonium::Weapon::Update(sf::RenderTarget& _rt, float _dt)
{
	if (ammunition.size() != 0)
	{
		CleanAmmunition(_rt);

		for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
		{
			ammunition[i]->Update(_dt);
		}
	}
}

void DancingPlutonium::Weapon::Draw(sf::RenderTarget& _rt)
{
	for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
	{
		ammunition[i]->Draw(_rt);
	}
}

void DancingPlutonium::Weapon::InitializeWeaponry()
{
	SetPattern(ProjectilePattern::BasicShot);
	ammunition = std::vector<Projectile*>();
	accumulator = 0.0f;
}

void DancingPlutonium::Weapon::SetPattern(ProjectilePattern _wepPattern)
{
	weaponPattern = _wepPattern;
}

sf::Uint32 DancingPlutonium::Weapon::GetPattern()
{
	return weaponPattern;
}

void DancingPlutonium::Weapon::UpgradeWeaponry()
{
	switch (weaponPattern)
	{
		case ProjectilePattern::BasicShot:
			weaponPattern = ProjectilePattern::GrowingShot;
			//weaponPattern = ProjectilePattern::GrowingShot;
			break;
		case ProjectilePattern::GrowingShot:
			weaponPattern = ProjectilePattern::TripleShot;
			break;
		case ProjectilePattern::IncendiaryShot:
			weaponPattern = ProjectilePattern::AimedShot;
			break;
		case ProjectilePattern::AimedShot:
			weaponPattern = ProjectilePattern::DoubleShot;
			break;
		case ProjectilePattern::DoubleShot:
			weaponPattern = ProjectilePattern::HomingShot;
			break;
		case ProjectilePattern::HomingShot:
			weaponPattern = ProjectilePattern::TripleShot;
			break;
		case ProjectilePattern::TripleShot:
			weaponPattern = ProjectilePattern::BasicShot;
			//weaponPattern = ProjectilePattern::StandardLazer;
			break;
		case ProjectilePattern::StandardLazer:
			weaponPattern = ProjectilePattern::JoesLazer;
			break;
		case ProjectilePattern::JoesLazer:
			weaponPattern = ProjectilePattern::QuadShot;
			break;
		case ProjectilePattern::QuadShot:
			weaponPattern = ProjectilePattern::PhotonPacket;
			break;
		case ProjectilePattern::PhotonPacket:
			weaponPattern = ProjectilePattern::PhotonStream;
			break;
		case ProjectilePattern::PhotonStream:
			weaponPattern = ProjectilePattern::PhotonTriplet;
			break;
		case ProjectilePattern::PhotonTriplet:
			weaponPattern = ProjectilePattern::PhotonQuartet;
			break;
		case ProjectilePattern::PhotonQuartet:
			weaponPattern = ProjectilePattern::IMMAFIRINMAHLAZOR;
			break;
		default:
			break;
	}
}

void DancingPlutonium::Weapon::CleanAmmunition(sf::RenderTarget& _rt)
{
	if (ammunition.size() != 0)
	{
		for (int i = 0; i < static_cast<int>(ammunition.size()); i++)
		{
			if (ammunition[i]->GetActiveState(_rt) == false)
			{
				delete ammunition[i];
				ammunition.erase(ammunition.begin() + i);
			}
		}
	}
}
