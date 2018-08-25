#pragma once

#include "IRng.h"
#include "ItemToken.h"
#include "BombToken.h"
#include "DamageToken.h"
#include "FireRateToken.h"
#include "FreeScoreToken.h"
#include "LifeToken.h"
#include "PatternToken.h"

namespace DancingPlutonium
{
	/* TokenFactory deploys the factory design pattern and uses a Static member function to return projectile object references based on input parameters. */
	class TokenFactory
	{
	private:
		#pragma region Ctor

		/* Disallow access to creating the TokenFactory class. It holds useful static methods which can be queried by using syntax: TokenFactory::<member name>. */
		TokenFactory() {}

		#pragma endregion

	public:
		#pragma region Dtor

		/* The TokenFactory destructor */
		~TokenFactory() {}

		#pragma endregion

		#pragma region Factory Method

	private:
		/* Determine which token we should spawn. */
		static sf::Uint32 GetRandomToken();

	public:
		/* Gets a reference to an ItemToken based on enum type. */
		static ItemToken* GetToken();

		#pragma endregion
	};
}