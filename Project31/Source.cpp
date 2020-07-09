#include<iostream>
#include<string>
#include<ctime>
using namespace std;
class CombatVehicle {
protected:
	string type;
	string model;
	int health;
public:
	CombatVehicle(string type, string model, int health):type(type),model(model){
		if (health < 1)
			health = 1;
		this->health = health;
	}
	virtual ~CombatVehicle()=0 {}

	virtual bool IsDestroyed()const {
		return health <= 0;
	}

	virtual void ShowInfo()const {
		cout << "Type: " << type << "\nModel: " << model <<"\nHealth:"<<health<< endl;
	}
	virtual int Attack() = 0;
	virtual void Defense(int damage) = 0;
};
class Tank:public CombatVehicle {
	int recharge;
	int accuracy;
	int thickness;
public:
	Tank(string model, int recharge, int accuracy, int thickness,int health)
		:CombatVehicle("Tank",model,health){
		SetRecharge(recharge);
		SetAccuracy(accuracy);
		SetThickness(thickness);
	}
	void SetRecharge(int recharge) {
		if (recharge < 1)
			recharge = 1;
		this->recharge = recharge;
	}
	void SetAccuracy(int accuracy) {
		if (accuracy < 1)
			accuracy = 1;
		this->accuracy = accuracy;
	}
	void SetThickness(int thickness) {
		if (thickness < 1)
			thickness = 1;
		this->thickness = thickness;
	}
	int Attack()override {
		int damage = (100 * accuracy / recharge);
		return damage;
	}

	void Defense(int damage)override {
		health -= (damage - thickness);
	}

	void ShowInfo()const override{
		CombatVehicle::ShowInfo();
			cout << "Recharge: " << recharge << "\nAccuracy: " <<
			accuracy << "\nThickness: " << thickness << endl;
	}
};
class ArmoredCar :public CombatVehicle {
	int countWeapons;
	int speed;
public:
	ArmoredCar(string model, int countWeapons, int speed, int health):CombatVehicle("Armored Car", model, health){
		SetCountWeapons(countWeapons);
		SetSpeed(speed);
	}
	void SetCountWeapons(int countWeapons) {
		if (countWeapons < 1)
			countWeapons = 1;
		this->countWeapons = countWeapons;
	}
	void SetSpeed(int speed) {
		if (speed < 1)
			speed = 1;
		this->speed = speed;
	}
	int Attack()override {
		int damage = 50 * countWeapons;
		return damage;
	}

	void Defense(int damage)override {
		health -= (damage - speed / 2);
	}

	void ShowInfo()const override {
		CombatVehicle::ShowInfo();
		cout << "Count weapons: " << countWeapons <<
			"\nSpeed: " << speed << endl;
	}
};
class AirDefenseVehicle:public CombatVehicle {
	int rate;
	int length;
	int mobility;
public:
	AirDefenseVehicle(string model,int rate, int length, int mobility,int health)
		:CombatVehicle("Air Defense Vehicle", model, health){
		SetRate(rate);
		SetLength(length);
		SetMobility(mobility);
	}
	void SetRate(int rate) {
		if (rate < 1)
			rate = 1;
		this->rate = 1;
	}
	void SetLength(int length) {
		if (length < 1)
			length = 1;
		this->length = length;
	}
	void SetMobility(int mobility) {
		if (mobility < 1)
			mobility = 1;
		this->mobility = mobility;
	}
	int Attack()override {
		int damage =150+length*(rate/10);
		return damage;
	}
	void Defense(int damage)override {
		health -= (damage / mobility);
	}
	void ShowInfo()const override {
		CombatVehicle::ShowInfo();
		cout << "Rate: " << rate <<"\nLength: " << length <<"\nMobility: "<<mobility<< endl;
	}
};
bool Round(CombatVehicle& v1, CombatVehicle& v2) {
	do {
		cout << endl;
		v1.CombatVehicle::ShowInfo();
		cout << "*---Attack---* \n";
		v2.CombatVehicle::ShowInfo();
		v2.Defense(v1.Attack());
		if (v2.IsDestroyed())
			return true;
		cout << endl;
		v2.CombatVehicle::ShowInfo();
		cout << "*---Attack---* \n";
		v1.CombatVehicle::ShowInfo();
		v1.Defense(v2.Attack());
		if (v1.IsDestroyed())
			return false;
		cout << endl;
	} while (!v2.IsDestroyed() && !v1.IsDestroyed());

}
int main() {
	srand(time(0));
	const int SIZE = 5;
	int size1, size2,r1Attack, r2Attack;
	size1=size2=SIZE;
	CombatVehicle* army1[SIZE]{};
	CombatVehicle* army2[SIZE]{};
	int randType = 0;
	for (int i = 0; i < SIZE; i++) {
		randType = 1 + rand() % 3;
		if (randType == 1)
			army1[i] = new Tank("T-34", 3 + rand() % 8, 1 + rand() % 5, 10 + rand() % 21, 220 + rand() % 181);
		else if (randType == 2)
			army1[i] = new ArmoredCar("A-12", 1 + rand() % 4, 10 + rand() % 16, 150 + rand() % 101);
		else
			army1[i] = new AirDefenseVehicle("D-20", 1 + rand() % 5, 1 + rand() % 10, 1 + rand() % 10, 120 + rand() % 101);
	}
		for (int i = 0; i < SIZE; i++) {
			randType = 1 + rand() % 3;
			if (randType == 1)
				army2[i] = new Tank("T-34", 3 + rand() % 8, 1 + rand() % 5, 20 + rand() % 31, 220 + rand() % 181);
			else if (randType == 2)
				army2[i] = new ArmoredCar("A-12", 1 + rand() % 4, 10 + rand() % 16, 150 + rand() % 101);
			else
				army2[i] = new AirDefenseVehicle("D-20", 1 + rand() % 5, 1 + rand() % 10, 1 + rand() % 10, 120 + rand() % 101);
		}
	do {
		cout << "First team:\n";
		for (int i = 0; i < size1; i++) {
			cout << i + 1 << ".";
			army1[i]->ShowInfo();
			cout << endl;
		}
		cout << "-----------------------------------------------------------\n";
		cout << "Second team:\n";
		for (int i = 0; i < size2; i++) {
			cout << i + 1 << ".";
			army2[i]->ShowInfo();
			cout << endl;
		}
		cout << "\n\n";
		system("pause");
		system("cls");
		r1Attack = rand() % size1;
		r2Attack = rand() % size2;
		army1[r1Attack]->ShowInfo();
		cout << "    VS\n";
		army2[r2Attack]->ShowInfo();
		system("pause");
		system("cls");
		if (Round(*army1[r1Attack], *army2[r2Attack])) {
			cout << "\n*--------Winner--------*\n";
			army1[r1Attack]->ShowInfo();
			delete army2[r2Attack];
			army2[r2Attack] = nullptr; 
			--size2;
			if (size2 == 0)
				break; 
			army2[r2Attack] = army2[size2];	
			
			system("pause");
		}
		else {
			cout << "\n*--------Winner--------*\n";
			army2[r2Attack]->ShowInfo();
			delete army1[r1Attack];
			army1[r1Attack] = nullptr;
			--size1;
			if (size1  == 0)
				break;	
			army1[r1Attack] = army1[size1];
			system("pause");
		}
		system("cls");

		cout << "First team:\n";
		for (int i = 0; i < size1; i++) {
			cout << i + 1 << ".";
			army1[i]->ShowInfo();
			cout << endl;
		}
		cout << "-----------------------------------------------------------\n";
		cout << "Second team:\n";
		for (int i = 0; i < size2; i++) {
			cout << i + 1 << ".";
			army2[i]->ShowInfo();
			cout << endl;
		}

		cout << "\n\n";
		system("pause");
		system("cls");
		r1Attack = rand() % size1;
		r2Attack = rand() % size2;
		army2[r2Attack]->ShowInfo();
		cout << "    VS\n";
		army1[r1Attack]->ShowInfo();
 		system("pause");
		system("cls");
		if (Round(*army2[r2Attack], *army1[r1Attack])) {
			cout << "\n*--------Winner--------*\n";
			army2[r2Attack]->ShowInfo();
			delete army1[r1Attack];
			army1[r1Attack] = nullptr;
			--size1;
			if (size1  == 0)
				break;
			army1[r1Attack] = army1[size1];
			system("pause");
		}
		else {
			cout << "\n*--------Winner--------*\n";
			army1[r1Attack]->ShowInfo();
			delete army2[r2Attack];
			army2[r2Attack] = nullptr;
			--size2;
			if (size2  == 0) 
				break;
			army2[r2Attack] = army2[size2];
			system("pause");
		}
		
		
 		system("cls");
	}while (size1>0 && size2>0);
	system("cls");
	if (size1 > 0) {
		cout << "First team win!\n";
		for (int i = 0; i < size1; i++) {
			cout << i + 1 << ".";
			army1[i]->ShowInfo();	
			cout << endl;
			delete army1[i];
			
		}
	}
	else {
		cout << "Second team win!\n";
		for (int i = 0; i < size2; i++) {
			cout << i + 1 << ".";
			army2[i]->ShowInfo();
			cout << endl;
			delete army2[i];
			
		}
	}
	
	
 	return 0;
}