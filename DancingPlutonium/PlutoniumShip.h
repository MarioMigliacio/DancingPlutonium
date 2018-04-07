#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"

namespace DancingPlutonium
{
	class PlutoniumShip
	{
	public:
		enum WeaponState
		{
			s_uninitialized,
			s_basic,
			s_sidecannons,
			s_lazerstream,
			s_widelazer,
			s_homing
		};
		
	public:
		PlutoniumShip(const sf::RenderTarget& _rt);
		~PlutoniumShip() {}
		int LivesRemaining() const;
		int GetScore() const;
		void AddScore(const int _value);
		int GetHealth() const;
		void ModifyHealth(const int _value);
		float GetFireRate() const;
		int GetFireDamage() const;
		void UpgradeWeapon();
		float GetSpeed() const;
		bool GetActiveState() const;
		void SetMovingState(bool _state);
		sf::Sprite& GetSprite();
		sf::Vector2f GetPosition() const;
		sf::FloatRect GetBounds() const;
		sf::Uint32 GetWeaponState() const;
		void SetMoveState(const sf::Uint32 _state);
		void SetPosition(const sf::Vector2f& _pos);
		void Update(float dt);
		void Draw(sf::RenderTarget& _rt);
		
	private:
		int bombs;
		int lives;
		int score;
		int health;
		float fireRate;
		int fireDamage;
		float speed;
		bool isActive;
		bool isMoving;
		sf::String name;
		sf::Sprite sprite;
		sf::Texture texture;
		sf::Vector2f position;

		void InitializeWeaponry();
		void SetSprite(const sf::RenderTarget& _rt);

	private:
		static sf::Uint32 m_weapon;
		static sf::Uint32 m_movement;
	};

}