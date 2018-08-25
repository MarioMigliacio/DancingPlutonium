#pragma once

#include "ItemToken.h"

namespace DancingPlutonium
{
	class FreeScoreToken : public ItemToken
	{
	public:
		#pragma region Ctor/Dtors

		/* FreeScoreToken constructor accepting a rendertarget input parameter */
		FreeScoreToken();
		/* FreeScoreToken copy constructor */
		FreeScoreToken(const FreeScoreToken& _ref) {}
		/* FreeScoreToken destructor */
		~FreeScoreToken() {}

		#pragma endregion

	private:
		#pragma region Unique Behavior

		/* Sets the sprite for this particular FreeScoreToken object */
		virtual void SetSprite() override;

		#pragma endregion

		const float defaultSpeed = 100.f;						/* Defines the speed that this FreeScoreToken can move at during updating. */
	};
}