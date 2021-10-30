//============================================================================
// Name        : inventory.cpp
// Assignment  : #4
// Author      : Dylan Harper
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

//CLASS PART

class Part{
private:
	string _partnum;
	string _desc;
	int _stockqty;
public:
	Part(){}
	Part(string p, string d, int s): _partnum(p), _desc(d), _stockqty(s){}
	void setPartNum(string p) {_partnum = p;}
	string getPartNum() const {return _partnum;}
	void setDesc(string d) {_desc = d;}
	string getDesc() const {return _desc;}
	void setStock(int s) {_stockqty = s;}
	int getStock() const {return _stockqty;}
};

//CLASS INVENTORY

class Inventory{
private:
	vector<Part*> _inv;
public:
	Inventory(){}
	~Inventory();
	Inventory(const Inventory& b);
	const Inventory& operator=(const Inventory& b);
	void addPart(string, string, int);
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
		_inv.push_back(new Part(*(b._inv[i])));
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

void Inventory::addPart(string p, string d, int s){
	Part* ptr = new Part(p, d, s);
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
			" Stock Qty: " << _inv[i]->getStock() << endl;
	}
}

//CLASS ORDER

class Order{
private:
	int _ordnum;
	string _cnum;
	bool _shipped;
	vector<string> _parts;
	vector<int> _qtys;
public:
	Order(){}
	Order(int, string);
	void setOrdnum(int o){_ordnum = o;}
	void setName(string c){_cnum = c;}
	void shipped() {_shipped = true;}
	int getOrdnum(){return _ordnum;}
	string getName(){return _cnum;}
	bool isShipped() {return _shipped;}
	void addPart(string p, int q) {
		_parts.push_back(p);
		_qtys.push_back(q);
	}
	bool deletePart(string);
	bool modQty(string, int);
	void printOrder(ostream&) const;
};

Order::Order(int ordnum, string cnum) {
	_ordnum = ordnum;
	_cnum = cnum;
	_shipped = false;
}

bool Order::deletePart(string p) {
	bool found = false;
	for (int i = 0; (i < _parts.size() && !found); i++){
		if (_parts[i] == p){
			found = true;
			_parts.erase(_parts.begin() + i);
			_qtys.erase(_qtys.begin() + i);
		}
	}
	return found;
}

bool Order::modQty(string p, int q) {
	bool found = false;
	for (int i = 0; (i < _parts.size() && !found); i++){
		if (_parts[i] == p){
			found = true;
			_qtys[i] = q;
		}
	}
	return found;
}

void Order::printOrder(ostream& os) const {
	os << "Order number: " << _ordnum << endl;
	os << "Customer number: " << _cnum << endl;
	os << "Shipped: " << _shipped << endl;
	for(int i = 0; i < _parts.size(); i++) {
		os << "Part: " << _parts[i] << " Quantity: " << _qtys[i] << endl;
	}
}

//CLASS ALLORDERS

class AllOrders{
private:
	vector<Order*> _orders;
public:
	AllOrders(){}
	~AllOrders();
	AllOrders(const AllOrders& b);
	const AllOrders& operator=(const AllOrders& b);
	void addOrder(int, string);
	bool deleteOrder(int);
	void printOrders(ostream&) const;
};

AllOrders::~AllOrders() {
	for(int i = 0; i < _orders.size(); i++) {
		delete _orders[i];
	}
}

AllOrders::AllOrders(const AllOrders& b) {
	for(int i = 0; i < b._orders.size(); i++) {
		_orders.push_back(new Order(*(b._orders[i])));
	}
}

const AllOrders& AllOrders::operator=(const AllOrders& b) {
	if(this != &b) {
		for(int i = 0; i < _orders.size(); i++) {
			delete _orders[i];
		}
		for(int i = 0; i < b._orders.size(); i++) {
			_orders.push_back(new Order(*(b._orders[i])));
		}
	}
	return *this;
}

void AllOrders::addOrder(int ordnum, string cnum) {
	Order* order = new Order(ordnum, cnum);
	_orders.push_back(order);
}

bool AllOrders::deleteOrder(int ordnum) {
	bool found = false;
	for(int i = 0; (i < _orders.size() && !found); i++) {
		if(_orders[i]->getOrdnum() == ordnum) {
			found = true;
			delete _orders[i];
			_orders.erase(_orders.begin() + i);
		}
	}
	return found;
}

void AllOrders::printOrders(ostream& os) const {
	os << "\nCurrent Order File" << endl;
	for(int i = 0; i < _orders.size(); i++) {
		_orders[i]->printOrder(os);
	}
}

//CLASS ADDRESS

class Address {
private:
	string _street;
	string _city;
	string _state;
	string _zip;
public:
	Address(){}
	Address(string, string, string, string);
	void setStreet(string s) {_street = s;}
	void setCity(string c) {_city = c;}
	void setState(string s) {_state = s;}
	void setZip(string z) {_zip = z;}
	string getStreet() {return _street;}
	string getCity() {return _city;}
	string getState() {return _state;}
	string getZip() {return _zip;}
	void printAddress(ostream&) const;
};

Address::Address(string street, string city, string state, string zip) {
	_street = street;
	_city = city;
	_state = state;
	_zip = zip;
}

void Address::printAddress(ostream& os) const {
	os << "Street: " << _street;
	os << "City: " << _city;
	os << "State: " << _state;
	os << "Zip: " << _zip;
}

//CLASS CUSTOMER

class Customer {
private:
	string _cnum;
	Address _addr;
public:
	Customer(){}
	Customer(string, string, string, string, string);
	void setCnum(string c) {_cnum = c;}
	string getCnum() {return _cnum;}
	void printCustomer(ostream&) const;
};

Customer::Customer(string cnum, string str, string cit, string st, string zip) {
	_cnum = cnum;
	_addr.setStreet(str);
	_addr.setCity(cit);
	_addr.setState(st);
	_addr.setZip(zip);
}

void Customer::printCustomer(ostream& os) const {
	os << "Customer number: " << _cnum << endl;
	_addr.printAddress(os);
}

//CLASS ALLCUSTOMERS

class AllCustomers {
private:
	vector<Customer*> _customers;
public:
	AllCustomers(){}
	~AllCustomers();
	AllCustomers(const AllCustomers& b);
	const AllCustomers& operator=(const AllCustomers& b);
	void addCustomer(string, string, string, string, string);
	bool deleteCustomer(string);
	void printCustomers(ostream&) const;
};

AllCustomers::~AllCustomers() {
	for(int i = 0; i < _customers.size(); i++) {
		delete _customers[i];
	}
}

AllCustomers::AllCustomers(const AllCustomers& b) {
	for(int i = 0; i < b._customers.size(); i++) {
		_customers.push_back(new Customer(*(b._customers[i])));
	}
}

const AllCustomers& AllCustomers::operator=(const AllCustomers& b) {
	if(this != &b) {
		for(int i = 0; i < _customers.size(); i++) {
			delete _customers[i];
		}
		for(int i = 0; i < b._customers.size(); i++) {
			_customers.push_back(new Customer(*(b._customers[i])));
		}
	}
	return *this;
}

void AllCustomers::addCustomer(string cnum, string str, string cit, string st, string zip) {
	Customer* cstmr = new Customer(cnum, str, cit, st, zip);
	_customers.push_back(cstmr);
}

bool AllCustomers::deleteCustomer(string cnum) {
	bool found = false;
	for(int i = 0; (i < _customers.size() && !found); i++) {
		if(_customers[i]->getCnum() == cnum) {
			found = true;
			delete _customers[i];
			_customers.erase(_customers.begin() + i);
		}
	}
	return found;
}

void AllCustomers::printCustomers(ostream& os) const {
	os << "\nCurrent Customer File" << endl;
	for(int i = 0; i < _customers.size(); i++) {
		_customers[i]->printCustomer(os);
	}
}

//MAIN

void loadInv(Inventory& inv, ifstream& infile) {
	string line, partNum, desc, stock;
	getline(infile, line);
	stringstream str(line);

	getline(str, partNum, ',');
	getline(str, desc, ',');
	getline(str, stock, ',');
	while(partNum != '0' && desc != '0' && stock != '0') {
		inv.addPart(partNum, desc, stoi(stock));

		getline(infile, line);
		stringstream str(line);

		getline(str, partNum, ',');
		getline(str, desc, ',');
		getline(str, stock, ',');
	}
}

void loadCusts(AllCustomers& custs, ifstream& infile) {
	string line, custNum, street, city, state, zip;
	getline(infile, line);
	stringstream str(line);

	getline(str, custNum, ',');
	getline(str, street, ',');
	getline(str, city, ',');
	getline(str, state, ',');
	getline(str, zip, ',');
	while(custNum != '0' && street != '0' && city != '0' && state != '0' && zip != '0') {
		custs.addCustomer(custNum, street, city, state, zip);
		getline(infile, line);
		stringstream str(line);

		getline(str, custNum, ',');
		getline(str, street, ',');
		getline(str, city, ',');
		getline(str, state, ',');
		getline(str, zip, ',');
	}
}

void loadOrds(AllOrders& ords, ifstream& infile) {
	string line, ordNum, custNum, partNum, qty;
	getline(infile, line);
	stringstream str(line);

	getline(str, ordNum, ',');
	getline(str, custNum, ',');
	while(ordNum != '0' && custNum != '0') {
		getline(infile, line);
		stringstream str(line);

		getline(str, partNum, ',');
		getline(str, qty, ',');
		while(partNum != '0' && qty != '0') {
			ords.addOrder(stoi(ordNum), custNum);

		}
	}
}

int main() {
	Inventory inv;
	AllOrders ords;
	AllCustomers custs;

	string file;
	cout << "Enter the data file: " << endl;
	cin >> file;
	ifstream infile(file);
	if(!infile) {
		cout << "Unable to get file" << endl;
		exit(-1);
	}

	return 0;
}
