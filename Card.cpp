#include "Card.h"

Card::Card()
{
	_color = RED;
	_shape = OVAL;
	_amount = 1;
	_fill = SOLID;
}

Card::Card(int color, int shape, int amount, int fill) : _color(color), _shape(shape), _amount(amount), _fill(fill)
{
}

int Card::getColor() const
{
	return _color;
}

int Card::getShape() const
{
	return _shape;
}

int Card::getAmount() const
{
	return _amount;
}

int Card::getFill() const
{
	return _fill;
}

void Card::setColor(int color)
{
	_color = color;
}

void Card::setShape(int shape)
{
	_shape = shape;
}

void Card::setAmount(int amount)
{
	_amount = amount;
}

void Card::setFill(int fill)
{
	_fill = fill;
}

void Card::printCardValues() const
{
	std::cout << "Color: " << _color << ", Shape: " << _shape << ", Amount: " << _amount << ", Fill: " << _fill << std::endl;
}

bool Card::checkSet(Card card1, Card card2)
{
	if (((_color + card1.getColor() + card2.getColor()) % 3) != 0) {
		return false;
	}
	if (((_amount + card1.getAmount() + card2.getAmount()) % 3) != 0) {
		return false;
	}
	if (((_shape + card1.getShape() + card2.getShape()) % 3) != 0) {
		return false;
	}
	if (((_fill + card1.getFill() + card2.getFill()) % 3) != 0) {
		return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	os << card.getColor() * 1000 + card.getShape() * 100 + card.getAmount() * 10 + card.getFill();
	return os;
}

