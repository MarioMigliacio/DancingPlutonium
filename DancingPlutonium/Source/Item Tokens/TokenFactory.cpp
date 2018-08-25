#include "TokenFactory.h"

sf::Uint32 DancingPlutonium::TokenFactory::GetRandomToken()
{
	auto criteria = RandomFloatRange();
	sf::Uint32 retVal = ItemToken::ItemType::Uninitialized;

	// no drop = 30%
	// free score = 25%
	// bomb = 10%
	// upgrade pattern = 10%
	// damage = 10%
	// fireRate = 10%
	// life = 5%

	if (criteria < .05f)
	{
		retVal = ItemToken::ItemType::LifeToken;
	}
	else if (criteria < .10f)
	{
		retVal = ItemToken::ItemType::FireRateToken;
	}
	else if (criteria < .15f)
	{
		retVal = ItemToken::ItemType::DamageToken;
	}
	else if (criteria < .20f)
	{
		retVal = ItemToken::ItemType::PatternToken;
	}
	else if (criteria < .25f)
	{
		retVal = ItemToken::ItemType::BombToken;
	}
	else if (criteria < .50f)
	{
		retVal = ItemToken::ItemType::FreeScoreToken;
	}

	return retVal;
}

DancingPlutonium::ItemToken* DancingPlutonium::TokenFactory::GetToken()
{
	ItemToken* retVal = nullptr;
	sf::Uint32 toMake = GetRandomToken();

	switch (toMake)
	{
		case ItemToken::ItemType::BombToken:
			retVal = new BombToken();
			break;
		case ItemToken::ItemType::DamageToken:
			retVal = new DamageToken();
			break;
		case ItemToken::ItemType::FireRateToken:
			retVal = new FireRateToken();
			break;
		case ItemToken::ItemType::FreeScoreToken:
			retVal = new FreeScoreToken();
			break;
		case ItemToken::ItemType::LifeToken:
			retVal = new LifeToken();
			break;
		case ItemToken::ItemType::PatternToken:
			retVal = new PatternToken();
			break;
		default:
			break;
	}

	return retVal;
}
