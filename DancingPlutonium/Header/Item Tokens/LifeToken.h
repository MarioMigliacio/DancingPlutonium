#pragma once

#include "ItemToken.h"

namespace DancingPlutonium
{
	class LifeToken : public ItemToken
	{
	public:
		#pragma region Ctor/Dtors

		/* LifeToken constructor accepting a rendertarget input parameter */
		LifeToken();
		/* LifeToken copy constructor */
		LifeToken(const LifeToken& _ref) {}
		/* LifeToken destructor */
		~LifeToken() {}

		#pragma endregion

	private:
		#pragma region Unique Behavior

		/* Sets the sprite for this particular LifeToken object */
		virtual void SetSprite() override;

		#pragma endregion

		const float defaultSpeed = 100.f;						/* Defines the speed that this LifeToken can move at during updating. */
	};
}