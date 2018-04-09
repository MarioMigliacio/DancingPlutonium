#pragma once

#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Bullet.h"
#include "BasicBullet.h"
#include "Enums.h"

namespace DancingPlutonium
{
	/* PlutoniumShip represents the player in this game */
	class PlutoniumShip
	{
	public:
		#pragma region WeaponState enum

		/* WeaponState maintains the state of this PlutoniumShip object's projectile when player shoots */
		enum WeaponState
		{
			s_uninitialized,
			s_basic,
			s_sidecannons,
			s_lazerstream,
			s_widelazer,
			s_homing
		};

		#pragma endregion
	public:
		#pragma region Ctor/Dtors

		/* PlutoniumShip constructor that accepts a RenderTarget as input parameter */
		PlutoniumShip(const sf::RenderTarget& _rt);
		/* PlutoniumShip deconstructor */
		~PlutoniumShip() {}

		#pragma endregion

		#pragma region Public Methods

		/* Returns the amount lives remaining for this PlutoniumShip object */
		int LivesRemaining() const;
		/* Returns the score the player has amassed for this PlutoniumShip object */
		int GetScore() const;
		/* Adds score to the this PlutoniumShip object based on the _value input parameter */
		void AddScore(const int _value);
		/* Returns the health for this PlutoniumShip object */
		int GetHealth() const;
		/* Modifies this PlutoniumShip object's health value based on the _value input parameter */
		void ModifyHealth(const int _value);
		/* Returns the fireRate for this PlutoniumShip object */
		float GetFireRate() const;
		/* Returns the fireDamage for this PlutoniumShip object */
		int GetFireDamage() const;
		/* Modifies this PlutoniumShip object's weaponry to the next state */
		void UpgradeWeapon();
		/* Returns the speed for this PlutoniumShip object */
		float GetSpeed() const;
		/* Returns true if this PlutoniumShip object is alive, false otherwise */
		bool GetActiveState() const;
		/* Returns true if this PlutoniumShip is within the bounds of the game window, false otherwise */
		bool IsWithinBounds(const sf::RenderTarget& _rt);
		/* Modifies this PlutoniumShip object's movement state based on _state input parameter*/
		void SetMovingState(bool _state);
		/* Returns the sprite for this PlutoniumShip object */
		sf::Sprite& GetSprite();
		/* Returns the position for this PlutoniumShip object */
		sf::Vector2f GetPosition() const;
		/* Returns the global bounds rectangle for this PlutoniumShip object */
		sf::FloatRect GetBounds() const;
		/* Returns the current weaponry state for this PlutoniumShip object */
		sf::Uint32 GetWeaponState() const;
		/* Sets the movement state for this PlutoniumShip object based on the _state input parameter */
		void SetMoveState(const sf::Uint32 _state);
		/* Sets the position for this PlutoniumShip object based on the _pos input parameter */
		void SetPosition(const sf::Vector2f& _pos);
		/* Update this PlutoniumShip in the world based on the clock and render winder input parameters */
		void Update(float dt, const sf::RenderTarget& _rt);
		/* Draw this PlutoniumShip sprite onto the render window _rt */
		void Draw(sf::RenderTarget& _rt);
		/* Shoot a projectile  */
		void Shoot(const sf::RenderTarget& _rt);
		/* Free up lost bullets if they go out of bounds */
		void CleanAmmunition(const sf::RenderTarget& _rt);

		#pragma endregion
	private:
		#pragma region Members

		int bombs;							/* Represents the bombs count for this PlutoniumShip object */
		int lives;							/* Represents the lives count for this PlutoniumShip object */
		int score;							/* Represents the score for this PlutoniumShip object */
		int health;							/* Represents the health of this PlutoniumShip object */
		float fireRate;						/* Represents the fireRate of this PlutoniumShip object */
		float accumulator;					/* Represents the accumulation of clock time, for special use with fireRate */
		int fireDamage;						/* Represents the fireDamage of this PlutoniumShip object */
		float speed;						/* Represents the speed of this PlutoniumShip object */
		bool isActive;						/* Represents the isActive state for this PlutoniumShip object */
		bool isMoving;						/* Represents the isMoving state for this PlutoniumShip object */
		std::vector<Bullet*> ammunition;	/* Represents the ammunition container of bullets for this PlutoniumShip object */
		sf::String name;					/* Represents the name of this PlutoniumShip object */
		sf::Sprite sprite;					/* Represents the sprite for this PlutoniumShip object */
		sf::Texture texture;				/* Represents the texture for this PlutoniumShip object */
		sf::Vector2f position;				/* Represents the position of this PlutoniumShip object */

		#pragma endregion

		#pragma region Private Methods

		/* Sets the Weaponry state for this PlutoniumShip to a safe default state */
		void InitializeWeaponry();
		/* Sets this PlutoniumShips sprite, texture and default position */
		void SetSprite(const sf::RenderTarget& _rt);

		#pragma endregion
	private:
		#pragma region Static State Members

		static sf::Uint32 m_weapon;		/* Static variable which maintains the state for this PlutoniumShips weaponry */
		static sf::Uint32 m_movement;	/* Static variable which maintains the state for this PlutoniumShips movement */
		//static sf::Uint32 m_action;		/* Static variable which maintains the state for this PlutoniumShips action */

		#pragma endregion
	};
}