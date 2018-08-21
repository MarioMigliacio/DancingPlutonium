#pragma once

#include "ItemToken.h"

namespace DancingPlutonium
{
	class PatternToken : public ItemToken
	{
	public:
		#pragma region Ctor/Dtors

		/* BasicShip constructor accepting a rendertarget input parameter */
		PatternToken();
		/* BasicShip copy constructor */
		PatternToken(const PatternToken& _ref) {}
		/* BasicShip destructor */
		~PatternToken() {}

		#pragma endregion

	private:

		// Inherited via ItemToken
		virtual void SetSprite() override;

		virtual void Update(const float& _dt, const sf::RenderTarget& _rt) override;

		const float defaultSpeed = 100.f;
	};
}