#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "AbstractBaseUnit.h"
#include "Collision.h"
#include "PlutoniumShip.h"
#include "BasicShip.h"
#include "ItemToken.h"
#include "TokenFactory.h"
#include "Bomb.h"

namespace DancingPlutonium
{
	/* The LevelObserver object represents an observer that takes in units and players positions and projectiles and manages important game states. */
	class LevelObserver
	{
	public:
		#pragma region Ctor/Dtors

		/* LevelObserver default constructor. Note that it is NOT A COPY CONSTRUCTOR. It needs a reference to player object. */
		LevelObserver(PlutoniumShip& _player);
		/* LevelObserver destructor */
		~LevelObserver();

		#pragma endregion

	public:
		#pragma region Basic Level Functionality
		
		/* Spawn an enemy unit into the game world. */
		void SpawnEnemyUnit(sf::RenderTarget& _rt);
		/* Need this done. */
		void SpawnEnemyWave(sf::RenderTarget& _rt);
		/* Spawn a Pattern Token! THIS IS A CHEAT MECHANISM DELETE THIS MARIO. */
		void SpawnItemToken(const sf::Vector2f& _pos);
		/* THIS IS A CHEAT MECHANISM DELETE THIS MARIO. */
		void KillCommand();
		/* Once an enemy unit has been destroyed by combat, add the score of the _unit to the player. */
		void EnemyUnitDeath(AbstractBaseUnit& _unit);
		/* Perform a weapon upgrade on the _unit in question. */
		void UpgradeUnitWeaponry(AbstractBaseUnit& _unit);
		/* Call for an update on our LevelObserver object. */
		void Update(sf::RenderTarget& _rt, float _dt);
		/* Call to Draw our LevelObserver components to the render target. */
		void Draw(sf::RenderTarget& _rt);

		#pragma endregion

	private:
		#pragma region Container Member Variables

		/* A reference to the player unit ship. */
		PlutoniumShip& _playerRef;
		/* A container which holds pointers to observable enemy units. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<AbstractBaseUnit*> EnemyShipContainer;
		/* A container which holds pointers to the projectiles of enemy units. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<AbstractBaseProjectile*> EnemyProjectileContainer;
		/* A container which holds pointers to the projectiles of the player. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<AbstractBaseProjectile*> PlayerProjectileContainer;
		/* A container which holds pointers to the item tokens active in the world. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<ItemToken*> ItemTokens;
		/* A container which holds pointers to the bomb objects active in the world. LevelObserver is responsible for the cleanup and update of this container. */
		std::vector<Bomb*> BombContainer;

		#pragma endregion

	private:
		#pragma region Private Functionality

		/* Check if a collision occurs between enemy units and the Bomb objects in the BombContainer. */
		void CheckForBombCollision();
		/* Check if a collision occurs between player and any units contained in the EnemyShips container. */
		void CheckForUnitToUnitCollision();
		/* Check if a collision occurs between any units contained in the EnemyShip container and the PlayerProjectile container. */
		void CheckForPlayerShotHit();
		/* Check if a collision occurs between player and any projectiles within the EnemyShip container container. */
		void CheckForEnemyShotHit();
		/* Checks if a collision occurs between player and any item tokens within the ItemTokens container.  */
		void CheckForItemCollision();
		/* Clean up projectiles which have become Inactive */
		void CleanAmmunition(sf::RenderTarget& _rt);
		/* Clean up projectiles which have become Inactive */
		void CleanPlayerAmmunition(sf::RenderTarget& _rt);
		/* Clean up enemy ships which have become Inactive. */
		void CleanEnemyShips();
		/* Clean up ItemTokens which have become Inactive */
		void CleanItemTokens(sf::RenderTarget& _rt);
		/* Clean up Bombs which have become Inactive  */
		void CleanBombs(sf::RenderTarget& _rt);
		/* Disposes of memory within the EnemyShipContainer vector. */
		void ClearEnemyShipContainer();
		/* Disposes of memory within the EnemyProjectileContainer vector. */
		void ClearEnemyProjectileContainer();
		/* Disposes of memory within the PlayerProjectileContainer vector. */
		void ClearPlayerProjectileContainer();
		/* Disposes of memory within the ItemTokens vector. */
		void ClearItemTokens();
		/* Disposes of memory within the BombContainer vector. */
		void ClearBombs();

		#pragma endregion
	};
}