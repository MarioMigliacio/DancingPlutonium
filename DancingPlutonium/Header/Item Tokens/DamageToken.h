#pragma once

#include "ItemToken.h"

namespace DancingPlutonium
{
	class DamageToken : public ItemToken
	{
	public:
		#pragma region Ctor/Dtors

		/* DamageToken constructor accepting a rendertarget input parameter */
		DamageToken();
		/* DamageToken copy constructor */
		DamageToken(const DamageToken& _ref) {}
		/* DamageToken destructor */
		~DamageToken() {}

		#pragma endregion

	private:
		#pragma region Unique Behavior

		/* Sets the sprite for this particular DamageToken object */
		virtual void SetSprite() override;

		#pragma endregion

		const float defaultSpeed = 100.f;						/* Defines the speed that this DamageToken can move at during updating. */
	};
}