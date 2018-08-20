#include "ItemToken.h"

DancingPlutonium::ItemToken::ItemToken(const sf::Vector2f& _pos)
{
}

void DancingPlutonium::ItemToken::Update(const float& _dt)
{

}

void DancingPlutonium::ItemToken::Draw(const sf::RenderTarget& _rt)
{

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

void DancingPlutonium::ItemToken::SetSprite(const sf::Vector2f& _origin)
{

}
