#pragma once

#include "ItemToken.h"

namespace DancingPlutonium
{
	class PatternToken : public ItemToken
	{
	public:
		#pragma region Ctor/Dtors

		/* PatternToken constructor accepting a rendertarget input parameter */
		PatternToken();
		/* PatternToken copy constructor */
		PatternToken(const PatternToken& _ref) {}
		/* PatternToken destructor */
		~PatternToken() {}

		#pragma endregion

	private:
		#pragma region Unique Behavior

		/* Sets the sprite for this particular PatternToken object */
		virtual void SetSprite() override;

		#pragma endregion

		const float defaultSpeed = 100.f;						/* Defines the speed that this PatternToken can move at during updating. */
	};
}