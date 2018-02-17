#pragma once

#include<SFML/Graphics.hpp>
#include "IRng.h"
#include "BulletPattern.h"
#include "Bullet.h"

class GenericEnemyUnit
{
protected:
	int value;
	int health;
	int fireDamage;
	float fireRate;
	float speed;
	bool isActive;
	sf::String name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	std::vector<BulletPattern::Pattern> bulletPatterns;
	std::vector<Bullet*> shotsFired;
	
public:	
	virtual int GetValue() const;
	virtual int GetHealth() const;
	virtual int GetFireDamage() const;
	virtual float GetFireRate() const;
	virtual float GetSpeed() const;
	virtual bool GetActiveState(const sf::RenderTarget& _rt) const;
	virtual bool CheckIfColliding(const Bullet& _shot) const;
	virtual sf::String GetName() const;
	virtual sf::Sprite GetSprite() const;
	virtual sf::Texture GetTexture() const;
	virtual sf::Vector2f GetPosition() const;
	virtual sf::FloatRect GetBounds() const;

	virtual void SetPosition(const sf::Vector2f& _pos);
	virtual void SetHealth(const int _val);
	
	virtual void SpawnRandomly(const sf::RenderTarget& _rt);
	virtual void Update(float _dt);
	virtual void Draw(const sf::RenderTarget& _rt) const;
	
	virtual void SetSprite() = 0;
	virtual void SetBulletPatterns() = 0;
	virtual void ShootBullet() = 0;
};
