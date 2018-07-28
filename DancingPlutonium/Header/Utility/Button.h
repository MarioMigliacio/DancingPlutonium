#pragma once

#include<SFML/Graphics.hpp>

namespace DancingPlutonium
{
	/*
	   Button class is a specialized object which utilizes sfml fonts/colors and texts to render a button
	   which can have features built into it (fade in, fade out, grow, etc..) 
	*/
	class Button
	{
	public:
		#pragma region Ctor/Dtors

		/* Button constructor accepting a string name, fill color, boarder color, and boolean state for isClickable input parameters */
		Button(const sf::String _name, const sf::Color& _fillColor, const sf::Color& _boarderColor, int _size, bool _clickable);
		/* Button copy constructor */
		Button(const Button& _ref);
		/* Button deconstructor */
		~Button() {}

		#pragma endregion
		
		#pragma region Methods

		/* Draw this Button sprite onto the render window _rt */
		void Draw(sf::RenderTarget& _rt) const;
		/* Update this Button in the world based on the clock and render window  */
		void Update(float _dt, sf::RenderWindow& _window);
		/* Returns true if this Button is clicked on with the mouse, false otherwise */
		bool IsClicked();
		/* Returns the name of this Button */
		sf::String getName() const;
		/* Sets this Buttons origin based on the _pos input parameter */
		void SetOrigin(const sf::Vector2f _pos);
		/* Sets this Buttons position based on the _pos input parameter */
		void SetPosition(const sf::Vector2f _pos);
		/* fadeIn method accepts the clock as input parameter and increases the alpha value of this Button */
		void FadeIn(float _dt);
		/* fadeOut method accepts the clock as input parameter and decreases the alpha value of this Button */
		void FadeOut(float _dt);
		/* Returns the bounding rectangle of this Button */
		sf::FloatRect GetBounds() const;

		#pragma endregion

	private:

		#pragma region Members

		bool isFading;					/* Represents the state of whether or not this Button is fading */
		bool isClickable;				/* Represents the state of whether or not this Button is clickable */
		bool isClicked;					/* Represents the state of whether or not this Button has been clicked */
		float accumulator;				/* Represents the accumulator value used to update this Button based on the clock */

		sf::Uint8 alpha;				/* Represents the alpha color value for this Button */
		sf::Text buttonName;			/* Represents this Buttons name */
		sf::Color buttonFillColor;		/* Represents the inside color of this Button */
		sf::Color buttonBoarderColor;	/* Represents the outside color of this Button */
		sf::Vector2f location;			/* Represents the default location to construct this Button with */
		sf::FloatRect bounds;			/* Represents the bounding rectangle for this Button */
		sf::Font font;					/* Represents the font for this Button */

		#pragma endregion
	private:
		#pragma region Private Setters

		/* Sets the color of this Button based on the _fillColor and _boarderColor input parameters */
		void SetColor(const sf::Color& _fillColor, const sf::Color& _boarderColor);
		/* Sets the font of this Button from the content folders font */
		void LoadFont();

		#pragma endregion
	};
}