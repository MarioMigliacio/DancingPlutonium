#pragma once

#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "AbstractBaseUnit.h"
#include "Enums.h"
#include "Weapon.h"

namespace DancingPlutonium
{
	/* PlutoniumShip represents the player in this game */
	class PlutoniumShip : public AbstractBaseUnit
	{
	public:
		#pragma region Ctor/Dtors

		/* PlutoniumShip constructor that accepts a RenderTarget as input parameter */
		PlutoniumShip(const sf::RenderTarget& _rt);
		/* PlutoniumShip copy constructor */
		PlutoniumShip(const PlutoniumShip& _ref) {}
		/* PlutoniumShip deconstructor */
		~PlutoniumShip();

		#pragma endregion

		#pragma region Public Methods

		sf::FloatRect GetRect() const;
		/* Returns the amount lives remaining for this PlutoniumShip object */
		int LivesRemaining() const;
		/* Adds to the life count for this PlutoniumShip object */
		void AddLife();
		/* Minus one to the life count for this PlutoniumShip object */
		void RemoveLife();
		/* Returns the score the player has amassed for this PlutoniumShip object */
		int GetScore() const;
		/* Adds score to the this PlutoniumShip object based on the _value input parameter */
		void AddScore(const int _value);
		/* Returns true if this PlutoniumShip is within the bounds of the game window, false otherwise */
		bool IsWithinBounds(const sf::RenderTarget& _rt) override;
		/* Modifies this PlutoniumShip object's movement state based on _state input parameter*/
		void SetMovingState(bool _state);
		/* Returns the current weaponry state for this PlutoniumShip object */
		sf::Uint32 GetWeaponState() const;
		/* Allows access to this PlutoniumShip objects weapon pointer */
		Weapon* GetWeaponEquipped();
		/* Sets the movement state for this PlutoniumShip object based on the _state input parameter */
		void SetMoveState(const sf::Uint32 _state);
		/* Sets the position for this PlutoniumShip object based on the _pos input parameter */
		void SetPosition(const sf::Vector2f& _pos);
		/* Update this PlutoniumShip in the world based on the clock and render winder input parameters */
		void Update(float dt, sf::RenderTarget& _rt);
		/* Draw this PlutoniumShip sprite onto the render window _rt */
		void Draw(sf::RenderTarget& _rt);
		/* If a projectile is allowed to be fired, ShootBullet adds the ammunition to the Weapon container */
		virtual void ShootBullet(const float _dt) override;
		/* Free up lost bullets if they go out of bounds */
		void CleanAmmunition(const sf::RenderTarget& _rt);
		/* Gets the sprite object for THIS unit. There was an issue with the abstract base class owning this method. */
		virtual sf::Sprite& GetSprite() override;

		#pragma endregion
	private:
		#pragma region Members

		short bombs;										/* Represents the bombs count for this PlutoniumShip object */
		short lives;										/* Represents the lives count for this PlutoniumShip object */
		int score;											/* Represents the score for this PlutoniumShip object */
		bool isMoving;										/* Represents the isMoving state for this PlutoniumShip object */
		sf::String name;									/* Represents the name for this PlutoniumShip object */
		sf::Sprite sprite;									/* Represents the sprite for this PlutoniumShip object */
		sf::Texture texture;								/* Represents the texture for this PlutoniumShip object */
		sf::Vector2f position;								/* Represents the position for this PlutoniumShip object */
		Weapon* weapon;										/* Represents the weapon for this PlutoniumShip object */

		#pragma endregion

		#pragma region Private Methods

		/* Sets the Weaponry state for this PlutoniumShip to a safe default state */
		virtual void InitializeWeaponry() override;
		/* Sets this PlutoniumShips sprite, texture and default position */
		void SetSprite(const sf::RenderTarget& _rt);

		#pragma endregion
	private:
		#pragma region Static State Members

		static sf::Uint32 m_movement;						/* Static variable which maintains the state for this PlutoniumShips movement */

		#pragma endregion

															// Inherited via AbstractBaseUnit
		
	};
}