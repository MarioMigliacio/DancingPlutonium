#include "Bomb.h"

DancingPlutonium::Bomb::Bomb(const sf::Vector2f& _pos) : 
	isExploding(false),
	accumulator(0.f)
{
	isActive = true;
	SetPosition(_pos);
	SetSprite(_pos);
	InitializeAnimationSpriteSheet();
}

DancingPlutonium::Bomb::~Bomb()
{
	delete currentAnimation;
}

void DancingPlutonium::Bomb::SetPosition(const sf::Vector2f& _pos)
{
	position = _pos;
	sprite.setPosition(_pos);
	animatedSprite.setPosition(sf::Vector2f(_pos.x - (imgwidth / 2) * scale, _pos.y - (imgwidth / 2) * scale));
}

void DancingPlutonium::Bomb::SetSprite(const sf::Vector2f& _origin)
{
	if (!isExploding)
	{
		texture.loadFromFile("Content/Images/BulletRed.png");
		sprite.setTexture(texture);
		sprite.setOrigin(sf::Vector2f(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f));
		sprite.setPosition(_origin);
		position = _origin;
	}
}

void DancingPlutonium::Bomb::Update(float _dt)
{
	accumulator += _dt;

	if (accumulator >= 2.0f && !isExploding)
	{
		isExploding = true;
		animatedSprite.play(*currentAnimation);
		animatedSprite.setScale(scale, scale);
	}

	if (!isExploding)
	{
		SetPosition(sf::Vector2f(position.x, position.y - _dt * defaultSpeed));
	}
	else if (isExploding)
	{
		animatedSprite.update(_dt);
	}

	if (accumulator > 4.f)
	{
		isActive = false;
	}
}

void DancingPlutonium::Bomb::Draw(sf::RenderTarget& _rt)
{
	if (isActive)
	{
		if (!isExploding)
		{
			_rt.draw(sprite);
		}
		else if (isExploding)
		{
			_rt.draw(animatedSprite);
		}
	}
}

bool DancingPlutonium::Bomb::GetActiveState()
{
	return isActive;
}

sf::Sprite DancingPlutonium::Bomb::GetSprite()
{
	return sprite;
}

void DancingPlutonium::Bomb::InitializeAnimationSpriteSheet()
{
	explodingTexture.loadFromFile("Content/Images/BombBlast_Original.png");
	
	bombAnimation.setSpriteSheet(explodingTexture);

	bombAnimation.addFrame(sf::IntRect(384, 384, 128, 128));
	bombAnimation.addFrame(sf::IntRect(0, 0, 128, 128));
	bombAnimation.addFrame(sf::IntRect(128, 0, 128, 128));
	bombAnimation.addFrame(sf::IntRect(256, 0, 128, 128));
	bombAnimation.addFrame(sf::IntRect(384, 0, 128, 128));
	bombAnimation.addFrame(sf::IntRect(0, 128, 128, 128));
	bombAnimation.addFrame(sf::IntRect(128, 128, 128, 128));
	bombAnimation.addFrame(sf::IntRect(256, 128, 128, 128));
	bombAnimation.addFrame(sf::IntRect(384, 128, 128, 128));
	bombAnimation.addFrame(sf::IntRect(0, 256, 128, 128));
	bombAnimation.addFrame(sf::IntRect(128, 256, 128, 128));
	bombAnimation.addFrame(sf::IntRect(256, 256, 128, 128));
	bombAnimation.addFrame(sf::IntRect(384, 256, 128, 128));
	bombAnimation.addFrame(sf::IntRect(0, 384, 128, 128));
	bombAnimation.addFrame(sf::IntRect(128, 384, 128, 128));
	bombAnimation.addFrame(sf::IntRect(256, 384, 128, 128));

	currentAnimation = &bombAnimation;
	animatedSprite = AnimatedSprite(0.2f, true, false);
}
