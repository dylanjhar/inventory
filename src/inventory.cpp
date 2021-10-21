//============================================================================
// Name        : inventory.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Part{
private:
	string _partnum;
	int _stockqty;
public:
	Part(){}
	Part(string p, int s): _partnum(p), _stockqty(s){}
	void setPartNum(string p){_partnum = p;}
	string getPartNum() const {return _partnum;}
	void setStock(int s){_stockqty = s;}
	int getStock() const {return _stockqty;}
};

class Inventory{
private:
	vector<Part*> _inv;
public:
	Inventory(){}
	~Inventory();
	Inventory(const Inventory& b);
	const Inventory& operator=(const Inventory& b);
	void addPart(string, int);
	bool deletePart(string);
	void printInventory(ostream&) const;
};

Inventory::~Inventory() {
	for(int i = 0; i < _inv.size(); i++) {
		delete _inv[i];
	}
}

Inventory::Inventory(const Inventory& b) {
	for(int i = 0; i < b._inv.size(); i++) {
		_inv.push_back(new Part(b._inv[i]->getPartNum(), b._inv[i]->getStock()));
	//	_inv.push_back(new Part(*(b._inv[i])));
	}
}

const Inventory& Inventory::operator=(const Inventory& b) {
	if(this != &b) {
		for(int i = 0; i < _inv.size(); i++) {
			delete _inv[i];
		}
		for(int i = 0; i < b._inv.size(); i++) {
			_inv.push_back(new Part(*(b._inv[i])));
		}
	}
	return *this;
}

void Inventory::addPart(string p, int s){
	Part* ptr = new Part(p, s);
	_inv.push_back(ptr);
}

bool Inventory::deletePart(string p){
	bool found = false;
	for (int i = 0; (i < _inv.size() && !found); i++){
		if (_inv[i]->getPartNum() == p){
			found = true;
			delete _inv[i];
			_inv.erase(_inv.begin() + i);
		}
	}
	return found;
}

void Inventory::printInventory(ostream& os) const {
	os << "\nCurrent Inventory File" << endl;
	for (int i = 0; i < _inv.size(); i++){
		os << "Part: " << _inv[i]->getPartNum() <<
			"  Stock Qty: " << _inv[i]->getStock() << endl;
		os << &*_inv[i] << endl;
		os << _inv[i] << endl;
	}
}
class Order{
private:
	int _ordnum;
	string _cname;
	vector<string> _parts;
	vector<int> _qtys;
public:
	Order();
	void setOrdnum(int o){_ordnum = o;}
	void setName(string c){_cname = c;}
	int getOrdnum(){return _ordnum;}
	string getName(){return _cname;}
	void addPart(string p, int q) {
		_parts.push_back(p);
		_qtys.push_back(q);
	}
	void print(ofstream&);
};

void Order::print(ofstream& os) {

}

class AllOrders{
private:
	vector<Order*> _orders;
public:

};


int main() {
	Inventory inv;
	inv.addPart("p100", 10);
	inv.addPart("p200", 20);
	inv.addPart("p300", 30);
	inv.printInventory(cout);
	inv.deletePart("p200");
	inv.printInventory(cout);

	Inventory inv2 = inv;
	inv.printInventory(cout);

	AllOrders ords;

	return 0;
}
