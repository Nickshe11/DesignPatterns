#include <iostream>
using namespace std;

//Product
class Computer
{
	std::string type;
	std::string cpu;
	std::string ram;
	std::string video;
	std::string disk;
	std::string power;
	bool on;
public:
	void set_type(const std::string& type)
	{
		this->type = type;
	}
	void set_cpu(const std::string& cpu)
	{
		this->cpu = cpu;
	}
	void set_ram(const std::string& ram)
	{
		this->ram = ram;
	}
	void set_video(const std::string& video)
	{
		this->video = video;
	}
	void set_disk(const std::string& disk)
	{
		this->disk = disk;
	}
	void set_power(const std::string& power)
	{
		this->power = power;
	}
	
	/*Computer(const std::string& cpu, const std::string& ram, const std::string& video, const std::string& disk, const std::string& power) :
		cpu(cpu), ram(ram), video(video), disk(disk), power(power)
	{
		on = false;
		cout << "CConstructor:\t" << this << endl;
	}*/
	Computer()
	{
		on = false;
		cout << "CConstructor:\t" << this << endl;
	}
	virtual~Computer()
	{
		cout << "CDestructor:\t" << this << endl;
	}
	void power_button()
	{
		on = on ? false : true;
	}
	virtual void info()const
	{
		cout << "\n---------------------------------\n";
		if (on)
		{
			cout << type << ":\t ";
			cout << "CPU: " << cpu << ", ";
			cout << "RAM: " << ram << ", ";
			cout << "Video: " << video << ", ";
			cout << "Disk: " << disk << ", ";
			cout << "Power: " << power << ";\n";
		}
		else
		{
			cout << "Please turn me on" << endl;
		}
		cout << "\n---------------------------------\n";
	}
};

//AbstractBuilder
class ComputerBuilder
{
protected:
	Computer* computer;
public:
	ComputerBuilder()
	{
		this->computer = new Computer;
	}
	virtual ~ComputerBuilder()
	{
		delete this->computer;
	}
	Computer* get_computer()const
	{
		return computer;
	}
	virtual void set_type() = 0;
	virtual void set_cpu() = 0;
	virtual void set_ram() = 0;
	virtual void set_video() = 0;
	virtual void set_disk() = 0;
	virtual void set_power() = 0;
};

//ConcreteBuilders
class CheapComputerBuilder : public ComputerBuilder
{
public:
	~CheapComputerBuilder(){}
	void set_type()
	{
		computer->set_type("CheapComputer");
	}
	void set_cpu()
	{
		computer->set_cpu("Intel Celeron 7300");

	}
	void set_ram()
	{
		computer->set_ram("SiliconPower 4 GB");
	}
	void set_video()
	{
		computer->set_video("Intel UHD 12G");
	}
	void set_disk()
	{
		computer->set_disk("Kingston SSD Now 128GB");
	}
	void set_power()
	{
		computer->set_power("Chieftec 400W");
	}
};

class OfficeComputerBuilder : public ComputerBuilder
{
public:
	~OfficeComputerBuilder() {}
	void set_type()
	{
		computer->set_type("OfficeComputer");
	}
	void set_cpu()
	{
		computer->set_cpu("Intel Core-i3 13100");

	}
	void set_ram()
	{
		computer->set_ram("kingston DDR3-3200 8GB");
	}
	void set_video()
	{
		computer->set_video("Intel UHD Graphics 730");
	}
	void set_disk()
	{
		computer->set_disk("Samsung 750 Evo 256 GB");
	}
	void set_power()
	{
		computer->set_power("Chieftec 500W Silver");
	}
};

class GameComputerBuilder : public ComputerBuilder
{
public:
	~GameComputerBuilder() {}
	void set_type()
	{
		computer->set_type("GameComputer");
	}
	void set_cpu()
	{
		computer->set_cpu("Intel Core-i7 13700");

	}
	void set_ram()
	{
		computer->set_ram("kingston DDR5-5600 32GB");
	}
	void set_video()
	{
		computer->set_video("nVidia GeForce RTX 4090");
	}
	void set_disk()
	{
		computer->set_disk("2TB Samsung 850 Pro M.2");
	}
	void set_power()
	{
		computer->set_power("Seasonic 1000W Platinum");
	}
};

class Sysadmin
{
	ComputerBuilder* builder;
public:Sysadmin():builder(nullptr){}
	void assembly_computer(ComputerBuilder* builder)
	{
		this->builder = builder;
		builder->set_type();
		builder->set_cpu();
		builder->set_ram();
		builder->set_disk();
		builder->set_power();
	}
	void turn_on_the_computer()
	{
		if (builder)
		{
			builder->get_computer()->power_button();
			builder->get_computer()->info();
		}
		else
		{
			cout << "Средства на сборку компьютера не были выданы :-(" << endl;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	/*Computer comp("Core i5 12400", "Kingston 8GB", "Intel HD Graphics", "Samsung 870 Evo 500 GB", "Chieftec 500 Gold");
	comp.info();*/
	Sysadmin nice_guy;
	CheapComputerBuilder computer_for_director;
	nice_guy.assembly_computer(&computer_for_director);
	nice_guy.turn_on_the_computer();
	computer_for_director.get_computer()->power_button();
	computer_for_director.get_computer()->info();

	OfficeComputerBuilder computer_for_bookkeeper;
	nice_guy.assembly_computer(&computer_for_bookkeeper);
	nice_guy.turn_on_the_computer();

	GameComputerBuilder computer_for_sysadmin;
	nice_guy.assembly_computer(&computer_for_sysadmin);
	nice_guy.turn_on_the_computer();
}