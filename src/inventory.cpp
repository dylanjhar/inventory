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
	bool modQty(string, int);
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

bool Inventory::modQty(string p, int q) {
	bool found = false;
	for (int i = 0; (i < _inv.size() && !found); i++){
		if (_inv[i]->getPartNum() == p){
			found = true;
			_inv[i]->setStock(q);
		}
	}
	return found;
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
		os << "\nPart: " << _inv[i]->getPartNum() << endl;
		os << "Description: " << _inv[i]->getDesc() << endl;
		os << "Stock Qty: " << _inv[i]->getStock() << endl;
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
	void setCnum(string c){_cnum = c;}
	void shipped() {_shipped = true;}
	int getOrdnum(){return _ordnum;}
	string getCnum(){return _cnum;}
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
	os << "\nOrder number: " << _ordnum << endl;
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
	bool addPart(int, string, string, int);
	bool deletePart(int, string, string);
	bool modQty(int, string, string, int);
	bool isShipped(int, string);
	bool shipped(int, string);
	bool deleteOrder(int, string);
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

bool AllOrders::addPart(int ordnum, string cnum, string partNum, int qty) {
	bool found = false;
	for(int i = 0; i < _orders.size() && !found; i++) {
		if(_orders[i]->getOrdnum() == ordnum && _orders[i]->getCnum() == cnum) {
			found = true;
			_orders[i]->addPart(partNum, qty);
		}
	}
	return found;
}

bool AllOrders::deletePart(int ordnum, string cnum, string partNum) {
	bool found = false;
	for(int i = 0; i < _orders.size() && !found; i++) {
		if(_orders[i]->getOrdnum() == ordnum && _orders[i]->getCnum() == cnum) {
			found = true;
			_orders[i]->deletePart(partNum);
		}
	}
	return found;
}

bool AllOrders::modQty(int ordnum, string cnum, string partNum, int qty) {
	bool found = false;
	for(int i = 0; i < _orders.size() && !found; i++) {
		if(_orders[i]->getOrdnum() == ordnum && _orders[i]->getCnum() == cnum) {
			found = true;
			_orders[i]->modQty(partNum, qty);
		}
	}
	return found;
}

bool AllOrders::isShipped(int ordnum, string cnum) {
	bool shipped = false, found = false;
	for(int i = 0; i < _orders.size() && !found; i++) {
		if(_orders[i]->getOrdnum() == ordnum && _orders[i]->getCnum() == cnum) {
			found = true;
			shipped = _orders[i]->isShipped();
		}
	}
	return shipped;
}

bool AllOrders::shipped(int ordnum, string cnum) {
	bool found = false;
	for(int i = 0; i < _orders.size() && !found; i++) {
		if(_orders[i]->getOrdnum() == ordnum && _orders[i]->getCnum() == cnum) {
			found = true;
			_orders[i]->shipped();
		}
	}
	return found;
}

bool AllOrders::deleteOrder(int ordnum, string cnum) {
	bool found = false;
	for(int i = 0; (i < _orders.size() && !found); i++) {
		if(_orders[i]->getOrdnum() == ordnum && _orders[i]->getCnum() == cnum) {
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
	os << "Street: " << _street << endl;
	os << "City: " << _city << endl;
	os << "State: " << _state << endl;
	os << "Zip: " << _zip << endl;
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
	os << "\nCustomer number: " << _cnum << endl;
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
	stringstream ss(line);

	getline(ss, partNum, ',');
	getline(ss, desc, ',');
	getline(ss, stock, ',');
	while(partNum != "0" && desc != "0" && stock != "0") {
		inv.addPart(partNum, desc.substr(1), stoi(stock));

		getline(infile, line);
		stringstream ss(line);

		getline(ss, partNum, ',');
		getline(ss, desc, ',');
		getline(ss, stock, ',');
	}
}

void loadCusts(AllCustomers& custs, ifstream& infile) {
	string line, custNum, street, city, state, zip;
	getline(infile, line);
	stringstream ss(line);

	getline(ss, custNum, ',');
	getline(ss, street, ',');
	getline(ss, city, ',');
	getline(ss, state, ',');
	getline(ss, zip, ',');
	while(custNum != "0" && street != "0" && city != "0" && state != "0" && zip != "0") {
		custs.addCustomer(custNum, street.substr(1), city.substr(1),
				state.substr(1), zip.substr(1));
		getline(infile, line);
		stringstream ss(line);

		getline(ss, custNum, ',');
		getline(ss, street, ',');
		getline(ss, city, ',');
		getline(ss, state, ',');
		getline(ss, zip, ',');
	}
}

void loadOrds(AllOrders& ords, ifstream& infile) {
	string line, ordNum, custNum, partNum, qty;
	getline(infile, line);
	stringstream ss(line);

	getline(ss, ordNum, ',');
	getline(ss, custNum, ',');
	while(ordNum != "0" && custNum != "0") {
		ords.addOrder(stoi(ordNum), custNum.substr(1));
		getline(infile, line);
		stringstream ss(line);

		getline(ss, partNum, ',');
		getline(ss, qty, ',');
		while(partNum != "0" && qty != "0") {
			ords.addPart(stoi(ordNum), custNum.substr(1), partNum, stoi(qty));
			getline(infile, line);
			stringstream ss(line);

			getline(ss, partNum, ',');
			getline(ss, qty, ',');
		}
		getline(infile, line);
		stringstream ss2(line);

		getline(ss2, ordNum, ',');
		getline(ss2, custNum, ',');
	}
}

void csrAdd(AllOrders& ords) {
	string custNum, partNum;
	int ordNum, qty;
	cout << "\nEnter order number: ";
	cin >> ordNum;
	cout << "Enter customer number: ";
	cin >> custNum;
	ords.addOrder(ordNum, custNum);
	cout << "Enter part number: ";
	cin >> partNum;
	cout << "Enter quantity: ";
	cin >> qty;
	ords.addPart(ordNum, custNum, partNum, qty);
	char choice;
	cout << "\nEnter another part? (y/n): ";
	cin >> choice;
	while(choice != 'n') {
		if(choice == 'y') {
			cout << "Enter part number: ";
			cin >> partNum;
			cout << "Enter quantity";
			cin >> qty;
			ords.addPart(ordNum, custNum, partNum, qty);
		} else {
			cout << "Not an option" << endl;
		}
		cout << "\nEnter another part? (y/n): ";
		cin >> choice;
	}
}

void csrMod(AllOrders& ords) {
	string custNum, partNum;
	int ordNum, qty;
	cout << "\nEnter order number: ";
	cin >> ordNum;
	cout << "Enter customer number: ";
	cin >> custNum;
	bool shipped = ords.isShipped(ordNum, custNum);
	if(!shipped) {
		cout << "\nEnter number to choose option" << endl;
		cout << "1) Add part" << endl;
		cout << "2) Delete part" << endl;
		cout << "3) Modify quantity" << endl;
		cout << "4) Return to last menu" << endl;
		int option;
		cin >> option;
		while(option != 4) {
			cout << "Enter part number: ";
			cin >> partNum;
			cout << "Enter quantity: ";
			cin >> qty;
			if(option == 1) {
				ords.addPart(ordNum, custNum, partNum, qty);
			} else if(option == 2) {
				ords.deletePart(ordNum, custNum, partNum);
			} else if(option == 3) {
				ords.modQty(ordNum, custNum, partNum, qty);
			} else {
				cout << "Not an option" << endl;
			}
			cout << "\nEnter number to choose option" << endl;
			cout << "1) Add part" << endl;
			cout << "2) Delete part" << endl;
			cout << "3) Modify quantity" << endl;
			cout << "4) Return to last menu" << endl;
			cin >> option;
		}
	} else {
		cout << "Order already shipped" << endl;
	}
}

void csr(AllOrders& ords) {
	cout << "\nEnter number to choose option" << endl;
	cout << "1) Add order" << endl;
	cout << "2) Delete order" << endl;
	cout << "3) Modify order" << endl;
	cout << "4) Return to main menu" << endl;
	int option;
	cin >> option;
	while(option != 4) {
		if(option == 1) {
			csrAdd(ords);
		} else if(option == 2) {
			string custNum;
			int ordNum;
			cout << "Enter order number: ";
			cin >> ordNum;
			cout << "Enter customer number: ";
			cin >> custNum;
			bool shipped = ords.isShipped(ordNum, custNum);
			if(!shipped) {
				ords.deleteOrder(ordNum, custNum);
			} else {
				cout << "Order already shipped" << endl;
			}
		} else if(option == 3) {
			csrMod(ords);
		} else {
			cout << "Not an option" << endl;
		}
		cout << "\nEnter number to choose option" << endl;
		cout << "1) Add order" << endl;
		cout << "2) Delete order" << endl;
		cout << "3) Modify order" << endl;
		cout << "4) Return to main menu" << endl;
		cin >> option;
	}
}

void receiver(Inventory& inv) {
	cout << "\nEnter number to choose option" << endl;
	cout << "1) Add part" << endl;
	cout << "2) Add stock" << endl;
	cout << "3) Return to main menu" << endl;
	int option;
	cin >> option;
	while(option != 3) {
		string partNum, desc;
		int qty;
		if(option == 1) {
			cout << "Enter part number: ";
			cin >> partNum;
			cout << "Enter description: ";
			cin >> desc;
			cout << "Enter quantity: ";
			cin >> qty;
			inv.addPart(partNum, desc, qty);
		} else if(option == 2) {
			cout << "Enter part number: ";
			cin >> partNum;
			cout << "Enter quantity: ";
			cin >> qty;
			inv.modQty(partNum, qty);
		} else {
			cout << "Not an option" << endl;
		}
		cout << "\nEnter number to choose option" << endl;
		cout << "1) Add part" << endl;
		cout << "2) Add stock" << endl;
		cout << "3) Return to main menu" << endl;
		cin >> option;
	}
}

void shipper(Inventory& inv, AllOrders& ords) {
	string partNum, custNum;
	int qty, ordNum;
	cout << "\nSet order status to shipped" << endl;
	cout << "Enter order number: ";
	cin >> ordNum;
	cout << "Enter customer number: ";
	cin >> custNum;
	bool shipped = ords.isShipped(ordNum, custNum);
	if(!shipped) {
		ords.shipped(ordNum, custNum);
		cout << "Modify inventory stock" << endl;
		cout << "Enter part number: ";
		cin >> partNum;
		cout << "Enter quantity: ";
		cin >> qty;
		inv.modQty(partNum, qty);
		char choice;
		cout << "Modify inventory stock of another part? (y/n): ";
		cin >> choice;
		while(choice != 'n') {
			if(choice == 'y') {
				cout << "Enter part number: ";
				cin >> partNum;
				cout << "Enter quantity: ";
				cin >> qty;
				inv.modQty(partNum, qty);
			} else {
				cout << "Not an option" << endl;
			}
			cout << "Modify inventory stock of another part? (y/n): ";
			cin >> choice;
		}
	} else {
		cout << "Order already shipped" << endl;
	}
}

int main() {
	Inventory inv;
	AllOrders ords;
	AllCustomers custs;

	string file;
	cout << "Enter the data file: ";
	cin >> file;
	ifstream infile(file);
	if(!infile) {
		cout << "Unable to get file" << endl;
		exit(-1);
	}

	loadInv(inv, infile);
	loadCusts(custs, infile);
	loadOrds(ords, infile);

	cout << "\nEnter number to choose option" << endl;
	cout << "1) Customer Service Rep" << endl;
	cout << "2) Warehouse Receiver" << endl;
	cout << "3) Warehouse Shipper" << endl;
	cout << "4) Dump Data" << endl;
	cout << "5) Exit" << endl;
	int option;
	cin >> option;
	while(option != 5) {
		if(option == 1) {
			csr(ords);
		} else if(option == 2) {
			receiver(inv);
		} else if(option == 3) {
			shipper(inv, ords);
		} else if(option == 4) {
			inv.printInventory(cout);
			ords.printOrders(cout);
			custs.printCustomers(cout);
		} else {
			cout << "Not an option" << endl;
		}
		cout << "\nEnter number to choose option" << endl;
		cout << "1) Customer Service Rep" << endl;
		cout << "2) Warehouse Receiver" << endl;
		cout << "3) Warehouse Shipper" << endl;
		cout << "4) Dump Data" << endl;
		cout << "5) Exit" << endl;
		cin >> option;
	}

	return 0;
}
