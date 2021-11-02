//============================================================================
// Name        : inventory.cpp
// Assignment  : #4
// Author      : Dylan Harper
// Description : A menu driven order entry system that allows various users
//				 to interact with it. This system is used to keep track of
//				 customers, their orders for parts, and warehouse inventory.
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
	bool incQty(string, int);
	bool decQty(string, int);
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

bool Inventory::incQty(string p, int inc) {
	bool found = false;
	int qty;
	for (int i = 0; (i < _inv.size() && !found); i++){
		if (_inv[i]->getPartNum() == p){
			found = true;
			qty = _inv[i]->getStock();
			_inv[i]->setStock(qty + inc);
		}
	}
	return found;
}

bool Inventory::decQty(string p, int dec) {
	bool found = false;
	int qty;
	for (int i = 0; (i < _inv.size() && !found); i++){
		if (_inv[i]->getPartNum() == p){
			found = true;
			qty = _inv[i]->getStock();
			_inv[i]->setStock(qty - dec);
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
	int getOrdnum() const {return _ordnum;}
	string getCnum() const {return _cnum;}
	bool isShipped() const {return _shipped;}
	void addPart(string p, int q) {
		_parts.push_back(p);
		_qtys.push_back(q);
	}
	bool deletePart(string);
	bool findPart(string);
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

bool Order::findPart(string p) {
	bool found = false;
	for (int i = 0; (i < _parts.size() && !found); i++){
		if (_parts[i] == p){
			found = true;
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
	bool findPart(int, string, string);
	bool modQty(int, string, string, int);
	bool isShipped(int, string) const;
	bool shipped(int, string);
	bool findOrder(int, string);
	bool deleteOrder(int, string);
	bool printOrder(int, string, ostream&) const;
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

bool AllOrders::findPart(int ordnum, string cnum, string partNum) {
	bool found = false, exist = false;
	for(int i = 0; i < _orders.size() && !found; i++) {
		if(_orders[i]->getOrdnum() == ordnum && _orders[i]->getCnum() == cnum) {
			found = true;
			bool exist = _orders[i]->findPart(partNum);
		}
	}
	return exist;
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

bool AllOrders::isShipped(int ordnum, string cnum) const {
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

bool AllOrders::findOrder(int ordnum, string cnum) {
	bool found = false;
	for(int i = 0; i < _orders.size() && !found; i++) {
		if(_orders[i]->getOrdnum() == ordnum && _orders[i]->getCnum() == cnum) {
			found = true;
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

bool AllOrders::printOrder(int ordnum, string cnum, ostream& os) const {
	bool found = false;
	for(int i = 0; (i < _orders.size() && !found); i++) {
		if(_orders[i]->getOrdnum() == ordnum && _orders[i]->getCnum() == cnum) {
			found = true;
			_orders[i]->printOrder(os);
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
	string getStreet() const {return _street;}
	string getCity() const {return _city;}
	string getState() const {return _state;}
	string getZip() const {return _zip;}
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
	string getCnum() const {return _cnum;}
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

//pre: first param is a newly instantiated Inventory object, second param is an input file
//	   containing data to populate the member variables in the objects
//post: The Inventory object's member variables are populated
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

//pre: first param is a newly instantiated AllCustomers object, second param is an input file
//	   containing data to populate the member variables in the objects
//post: The AllCustomers object's member variables are populated
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

//pre: first param is a newly instantiated AllOrders object, second param is an input file
//	   containing data to populate the member variables in the objects
//post: The AllOrders object's member variables are populated
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

//pre: first param is the AllOrders object with populated member variables
//post: A new Order object is created and populated. The Allorders object has a pointer
//	    pointing to the new Order object
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
			cout << "\nNot an option" << endl;
		}
		cout << "\nEnter another part? (y/n): ";
		cin >> choice;
	}
}

//pre: first param is the AllOrders object with populated member variables
//post: An Order object being pointed to by the AllOrders object has it's member variables modified
void csrMod(AllOrders& ords) {
	string custNum, partNum;
	int ordNum, qty;
	cout << "\nEnter order number: ";
	cin >> ordNum;
	cout << "Enter customer number: ";
	cin >> custNum;
	if(!ords.findOrder(ordNum, custNum)) {
		cout << "\nOrder does not exist" << endl;
		cout << "Returning to last menu" << endl;
	} else {
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
				cout << "\nEnter part number: ";
				cin >> partNum;
				if(option == 1) {
					cout << "Enter quantity: ";
					cin >> qty;
					ords.addPart(ordNum, custNum, partNum, qty);
				} else if(!ords.findPart(ordNum, custNum, partNum)) {
					cout << "\nPart does not exist in order" << endl;
				} else if(option == 2) {
					ords.deletePart(ordNum, custNum, partNum);
				} else if(option == 3) {
					cout << "Enter new quantity: ";
					cin >> qty;
					ords.modQty(ordNum, custNum, partNum, qty);
				} else {
					cout << "\nNot an option" << endl;
				}
				cout << "\nEnter number to choose option" << endl;
				cout << "1) Add part" << endl;
				cout << "2) Delete part" << endl;
				cout << "3) Modify quantity" << endl;
				cout << "4) Return to last menu" << endl;
				cin >> option;
			}
		} else {
			cout << "\nOrder already shipped" << endl;
		}
	}
}

//pre: first param is the AllOrders object with populated member variables
//post: A new Order object being pointed to by the AllOrders object is created and populated,
//		an existing Order object is deleted or modified
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
			cout << "\nEnter order number: ";
			cin >> ordNum;
			cout << "Enter customer number: ";
			cin >> custNum;
			if(!ords.findOrder(ordNum, custNum)) {
				cout << "\nOrder does not exist" << endl;
				cout << "Returning to last menu" << endl;
			} else {
				bool shipped = ords.isShipped(ordNum, custNum);
				if(!shipped) {
					ords.deleteOrder(ordNum, custNum);
				} else {
					cout << "\nOrder already shipped" << endl;
				}
			}
		} else if(option == 3) {
			csrMod(ords);
		} else {
			cout << "\nNot an option" << endl;
		}
		cout << "\nEnter number to choose option" << endl;
		cout << "1) Add order" << endl;
		cout << "2) Delete order" << endl;
		cout << "3) Modify order" << endl;
		cout << "4) Return to main menu" << endl;
		cin >> option;
	}
}

//pre: first param is the Inventory object with populated member variables
//post: A new Part object is created and populated, or an existing Part has it's
//	    member variables modified
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
			cout << "\nEnter part number: ";
			cin >> partNum;
			cout << "Enter description: ";
			cin >> desc;
			cout << "Enter quantity: ";
			cin >> qty;
			inv.addPart(partNum, desc, qty);
		} else if(option == 2) {
			cout << "\nEnter part number: ";
			cin >> partNum;
			cout << "Enter quantity to add: ";
			cin >> qty;
			if(!inv.incQty(partNum, qty)) {
				cout << "\nPart does not exist" << endl;
			}
		} else {
			cout << "\nNot an option" << endl;
		}
		cout << "\nEnter number to choose option" << endl;
		cout << "1) Add part" << endl;
		cout << "2) Add stock" << endl;
		cout << "3) Return to main menu" << endl;
		cin >> option;
	}
}

//pre: first param is the Inventory object with populated member variables, second param
//	   is the Orders object with populated member variables
//post: Existing Order object and Part objects being pointed to by the Orders object and
//		Inventory object respectively have their member variables modified
void shipper(Inventory& inv, AllOrders& ords) {
	string partNum, custNum;
	int qty, ordNum;
	cout << "\nSet order status to shipped" << endl;
	cout << "Enter order number: ";
	cin >> ordNum;
	cout << "Enter customer number: ";
	cin >> custNum;
	if(!ords.findOrder(ordNum, custNum)) {
		cout << "\nOrder does not exist" << endl;
		cout << "Returning to last menu" << endl;
	} else {
		if(!ords.isShipped(ordNum, custNum)) {
			ords.shipped(ordNum, custNum);
			cout << "\nOrder processed: " << endl;
			ords.printOrder(ordNum, custNum, cout);
			cout << "\nDecrement inventory stock" << endl;
			cout << "Enter part number: ";
			cin >> partNum;
			cout << "Enter quantity to subtract: ";
			cin >> qty;
			if(!inv.decQty(partNum, qty)) {
				cout << "\nPart does not exist" << endl;
			} else {
				char choice;
				cout << "\nDecrement inventory stock of another part? (y/n): ";
				cin >> choice;
				while(choice != 'n') {
					if(choice == 'y') {
						cout << "Enter part number: ";
						cin >> partNum;
						cout << "Enter quantity: ";
						cin >> qty;
						if(!inv.decQty(partNum, qty)) {
							cout << "\nPart does not exist" << endl;
						}
					} else {
						cout << "\nNot an option" << endl;
					}
					cout << "\nDecrement inventory stock of another part? (y/n): ";
					cin >> choice;
				}
			}
		} else {
			cout << "\nOrder already shipped" << endl;
		}
	}
}

int main() {
	Inventory inv;
	AllOrders ords;
	AllCustomers custs;

	ifstream infile("data.txt");
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
