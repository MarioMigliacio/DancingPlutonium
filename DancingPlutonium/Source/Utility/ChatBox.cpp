#include "ChatBox.h"

DancingPlutonium::ChatBox::ChatBox(const sf::String& _nameOfBox, const sf::Vector2f _sizeOfBox)
{
	isRead = false;
	canDispose = false;
	accumulator = 0;
	indexer = 0;
	alpha = 128;

	chatBoxName = _nameOfBox;
	outLine.setSize(_sizeOfBox);

	outlineFillColor = sf::Color(0, 0, 0, alpha);
	outlineOutColor = sf::Color(128, 128, 128, alpha);
	outLine.setFillColor(outlineFillColor);
	outLine.setOutlineColor(outlineOutColor);
	outLine.setOutlineThickness(2);

	LoadFont();
	entireMessage = sf::Text(_nameOfBox, font, 24);
	entireFillColor = sf::Color(255, 0, 0, alpha);
	entireOutColor = sf::Color(128, 128, 128, alpha);
	entireMessage.setFillColor(entireFillColor);
	entireMessage.setOutlineColor(entireOutColor);
	entireMessage.setOutlineThickness(1);
}

DancingPlutonium::ChatBox::ChatBox(const ChatBox& _ref)
{
	isRead = _ref.isRead;
	canDispose = _ref.canDispose;
	alpha = _ref.alpha;
	accumulator = _ref.accumulator;
	indexer = _ref.indexer;
	entireMessage = _ref.entireMessage;
	typeWriterMessage = _ref.typeWriterMessage;
	outLine = _ref.outLine;
	chatBoxName = _ref.chatBoxName;
	font = _ref.font;
	outlineFillColor = _ref.outlineFillColor;
	outlineOutColor = _ref.outlineOutColor;
	entireFillColor = _ref.entireFillColor;
	entireOutColor = _ref.entireOutColor;
}

void DancingPlutonium::ChatBox::Draw(sf::RenderTarget& _rt) const
{
	if (isRead == false)
	{
		_rt.draw(outLine);
		_rt.draw(typeWriterMessage);
	}
}

void DancingPlutonium::ChatBox::Update(float _dt, float _killTimer)
{
	accumulator += _dt;

	TypeWriterEffect(accumulator);

	if (_killTimer >= 2.f)
	{
		FadeOut(accumulator);

		if (isRead)
		{
			canDispose = true;
		}
	}
}

sf::String DancingPlutonium::ChatBox::GetName() const
{
	return chatBoxName;
}

void DancingPlutonium::ChatBox::SetOrigin(const sf::Vector2f _pos)
{
	outLine.setOrigin(_pos);
}

sf::Vector2f DancingPlutonium::ChatBox::GetPosition()
{
	return outLine.getPosition();
}

void DancingPlutonium::ChatBox::SetPosition(const sf::Vector2f _pos)
{
	outLine.setPosition(_pos);

	entireMessage.setPosition(_pos.x + entireMessage.getCharacterSize(), _pos.y + entireMessage.getCharacterSize());
}

sf::FloatRect DancingPlutonium::ChatBox::GetBounds() const
{
	return outLine.getGlobalBounds();
}

sf::RectangleShape& DancingPlutonium::ChatBox::GetChatBoxOutline()
{
	return this->outLine;
}

bool DancingPlutonium::ChatBox::CanDispose()
{
	return canDispose;
}

void DancingPlutonium::ChatBox::TypeWriterEffect(float _dt)
{
	typeWriterMessage = entireMessage;
	
	sf::String temp = entireMessage.getString().substring(0, indexer);
	typeWriterMessage.setString(temp);

	if (indexer < entireMessage.getString().getSize() && accumulator >= 0.025f)
	{
		indexer++;
		accumulator = 0.f;
	}
}

void DancingPlutonium::ChatBox::FadeOut(float _dt)
{
	if (alpha <= 255 && accumulator >= 0.025f)
	{
		alpha++;
		accumulator = 0.0f;
	}

	outLine.setFillColor(sf::Color(outlineFillColor.r, outlineFillColor.g, outlineFillColor.b, alpha));
	outLine.setOutlineColor(sf::Color(outlineOutColor.r, outlineOutColor.g, outlineOutColor.b, alpha));
	typeWriterMessage.setFillColor(sf::Color(entireFillColor.r, entireFillColor.g, entireFillColor.b, alpha));
	typeWriterMessage.setOutlineColor(sf::Color(entireOutColor.r, entireOutColor.g, entireOutColor.b, alpha));

	if (alpha == 256)
	{
		isRead = true;
	}
}

void DancingPlutonium::ChatBox::LoadFont()
{
	font.loadFromFile("Content/Fonts/Dejavu.ttf");
}