#pragma once
#include <iostream>
#define RED 1
#define GREEN 2
#define BLUE 3
#define OVAL 1
#define DIAMOND 2
#define WAVE 3
#define SOLID 1
#define HATCHED 2
#define EMPTY 3

class Card
{
private:
	int _color;
	int _shape;
	int _amount;
	int _fill;
public:
	Card();
	Card(int color, int shape, int amount, int fill);

	int getColor() const;
	int getShape() const;
	int getAmount() const;
	int getFill() const;
	void setColor(int color);
	void setShape(int shape);
	void setAmount(int amount);
	void setFill(int fill);

	void printCardValues() const;
	bool checkSet(Card card1, Card card2);

	friend std::ostream& operator<<(std::ostream& os, const Card& card);
};

