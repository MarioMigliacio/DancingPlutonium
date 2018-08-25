#pragma once

#include "ItemToken.h"

namespace DancingPlutonium
{
	class FireRateToken : public ItemToken
	{
	public:
		#pragma region Ctor/Dtors

		/* FireRateToken constructor accepting a rendertarget input parameter */
		FireRateToken();
		/* FireRateToken copy constructor */
		FireRateToken(const FireRateToken& _ref) {}
		/* FireRateToken destructor */
		~FireRateToken() {}

		#pragma endregion

	private:
		#pragma region Unique Behavior

		/* Sets the sprite for this particular FireRateToken object */
		virtual void SetSprite() override;

		#pragma endregion

		const float defaultSpeed = 100.f;						/* Defines the speed that this FireRateToken can move at during updating. */
	};
}