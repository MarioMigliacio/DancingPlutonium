#pragma once

#include "GenericEnemyUnit.h"

class BasicShip : public GenericEnemyUnit
{
public:
	BasicShip(const sf::RenderTarget& _rt);
	BasicShip(const BasicShip& _ref) {}
	~BasicShip() {}

	void SetSpriteImage();

	// Inherited via GenericEnemyUnit
	virtual int GetValue() const override;
	virtual int GetHealth() const override;
	virtual float GetFireRate() const override;
	virtual int GetFireDamage() const override;
	virtual float GetSpeed() const override;
	virtual bool GetActiveState() const override;
	virtual sf::Sprite& GetSprite() override;
	virtual sf::Vector2f GetPosition() const override;
	virtual sf::FloatRect GetBounds() const override;
	virtual void SetPosition(const sf::Vector2f& _pos) override;
	virtual void Draw(sf::RenderTarget& _rt) override;
	virtual void EmplaceRandomly(const sf::RenderTarget& _rt) override;
};