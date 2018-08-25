#include "ItemToken.h"

void DancingPlutonium::ItemToken::Draw(sf::RenderTarget& _rt)
{
	_rt.draw(sprite);
}

bool DancingPlutonium::ItemToken::IsActive() const
{
	return isActive;
}

void DancingPlutonium::ItemToken::ToggleActiveState()
{
	isActive ? isActive = false : isActive = true;
}

sf::Sprite& DancingPlutonium::ItemToken::GetSprite()
{
	return sprite;
}

sf::Vector2f DancingPlutonium::ItemToken::GetPosition() const
{
	return position;
}

void DancingPlutonium::ItemToken::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
}

sf::Uint32 DancingPlutonium::ItemToken::GetType()
{
	return itemType;
}

void DancingPlutonium::ItemToken::SpawnRandomly(const sf::RenderTarget& _rt)
{
	int randomX = static_cast<int>(_rt.getSize().x - sprite.getGlobalBounds().width / 2.0f);
	randomX = RandomIntRange(static_cast<int>(sprite.getGlobalBounds().width / 2.0f), randomX) % randomX;

	int randomY = static_cast<int>(_rt.getSize().y - sprite.getGlobalBounds().height / 2.0f);
	randomY = RandomIntRange(static_cast<int>(sprite.getGlobalBounds().height / 2.0f), randomY) % randomY;

	SetPosition(sf::Vector2f(static_cast<float>(randomX), static_cast<float>(randomY)));
}

DancingPlutonium::ItemToken* DancingPlutonium::ItemToken::GetRandomToken()
{
	auto criteria = RandomFloatRange();
	ItemToken* retVal = nullptr;

	// no drop = 30%
	// free score = 25%
	// bomb = 10%
	// upgrade pattern = 10%
	// damage = 10%
	// fireRate = 10%
	// life = 5%

	/*if (criteria < .05f)
	{
		retVal = TokenFactory::GetToken(ItemToken::ItemType::LifeToken);
	}
	else if (criteria < .15)
	{
		retVal = TokenFactory::GetToken(ItemToken::ItemType::FireRateToken);
	}
	else if (criteria < .25)
	{
		retVal = TokenFactory::GetToken(ItemToken::ItemType::DamageToken);
	}
	else if (criteria < .35)
	{
		retVal = TokenFactory::GetToken(ItemToken::ItemType::PatternToken);
	}
	else if (criteria < .45)
	{
		retVal = TokenFactory::GetToken(ItemToken::ItemType::BombToken);
	}
	else if (criteria < .70)
	{
		retVal = TokenFactory::GetToken(ItemToken::ItemType::FreeScoreToken);
	}*/

	return retVal;
}

bool DancingPlutonium::ItemToken::IsWithinBounds(const sf::RenderTarget& _rt)
{
	auto rect = sprite.getGlobalBounds();
	sf::FloatRect gameBounds = sf::FloatRect(0.0f, 0.0f, static_cast<float>(_rt.getSize().x), static_cast<float>(_rt.getSize().y));

	if (gameBounds.intersects(rect))
	{
		return true;
	}
	else
	{
		isActive = false;
		return false;
	}
}

void DancingPlutonium::ItemToken::Update(const float & _dt, const sf::RenderTarget & _rt)
{
	if (IsWithinBounds(_rt))
	{
		accumulator += _dt;

		if (accumulator >= 3.f)
		{
			auto tempPos = position;
			tempPos.y += _dt * speed;
			SetPosition(tempPos);
		}
	}
}
