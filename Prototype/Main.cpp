#include <iostream>
#include <map>
using namespace std;

//Abstract Prototype:
class Player
{
public:
	virtual ~Player(){}
	virtual void print()const = 0;
	virtual Player* clone()const = 0;
};

//Concrete Prototype:
class CarPlayer :public Player
{
	std::string name;
	int id;
public:
	CarPlayer(const std::string name, int id): name(name), id(id)
	{
		cout << "CarConstructor:\t" << this << endl;
	}
	CarPlayer(const CarPlayer&other ):name(other.name), id(other.id) 
	{
		cout << "CarCopyConstructor:\t" << this << endl;
	}
	~CarPlayer()
	{
		cout << "CarDestructor:\t" << this << endl;
	}
	void print()const override
	{
		cout << "Car player: " << name << " " << id << endl;
	}
	Player* clone()const
	{
		return new CarPlayer(*this);
	}
};
class BikePlayer :public Player
{
	std::string name;
	int id;
public:
	BikePlayer(const std::string& name, int id) :name(name), id(id)
	{
		cout << "BikeConstructor:\t" << this << endl;
	}
	BikePlayer(const BikePlayer& other) :name(other.name), id(other.id)
	{
		cout << "BikeCopyConstructor:\t" << this << endl;
	}
	~BikePlayer()
	{
		cout << "BikeDestructor:\t" << this << endl;
	}
	void print()const
	{
		cout << "Bike player: " << name << " " << id << endl;
	}
	Player* clone()const
	{
		return new BikePlayer(*this);
	}
};

enum PlayerType {CAR, BIKE};

class PlayerFactory
{
	std::map<PlayerType, Player*> players;
public:
	PlayerFactory()
	{
		players[CAR] = new CarPlayer("BMW", 1000);
		players[BIKE] = new BikePlayer("HarleyDavidson", 777);
	}
	~PlayerFactory()
	{
		delete players[CAR];
		delete players[BIKE];
	}
	Player* CreatePlayer(PlayerType type)
	{
		return players[type]->clone();
	}
};

void main()
{
	setlocale(LC_ALL, "");
	PlayerFactory factory;
	cout << "\n--------------------\n";
	Player* player1 = factory.CreatePlayer(CAR);
	player1->print();
	cout << "\n--------------------\n";
	Player* player2 = factory.CreatePlayer(BIKE);
	player2->print();
	cout << "\n--------------------\n";
}