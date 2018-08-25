#pragma once

#include "ItemToken.h"

namespace DancingPlutonium
{
	class BombToken : public ItemToken
	{
	public:
		#pragma region Ctor/Dtors

		/* BombToken constructor accepting a rendertarget input parameter */
		BombToken();
		/* BombToken copy constructor */
		BombToken(const BombToken& _ref) {}
		/* BombToken destructor */
		~BombToken() {}

		#pragma endregion

	private:
		#pragma region Unique Behavior

		/* Sets the sprite for this particular BombToken object */
		virtual void SetSprite() override;

		#pragma endregion

		const float defaultSpeed = 100.f;						/* Defines the speed that this BombToken can move at during updating. */
	};
}