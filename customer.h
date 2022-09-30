// =========================================================
// File: customer.h
// Author: Mauricio Garcia Villanueva -A01704098
// Date: 6 / Junio / 2022
// Description: Implementacion de la clase customer
// =========================================================
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <sstream>
#include <iomanip>
#include "bill.h"
#include "operator.h"

class Customer {
private:
  int id, age, totalSpentTalkingTime, totalMessageSent, totalInternetUsage;
  std::string name;
  Operator *op;
  Bill *bill;

public:
  Customer(int, std::string, int, Operator*, double);
  Customer(const Customer&);
  ~Customer();

  int getId() const;
  int getAge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  std::string getName() const;
  Operator* getOperator() const;
  Bill* getBill() const;

  void setOperator(Operator*);

  std::string toString() const;

  void talk (int, Customer&);
  void message(int, const Customer&);
  void connection(double);
  void pay(double);
};

//Constructor con 5 parámetros. Recibe el id, el nombre, la edad, el operador y el
// límite de crédito. Se debe crear el objeto de la clase Bill.
Customer::Customer(int i, std::string nom, int ag, Operator *o, double la){
    id = i;
    name = nom;
    age = ag;
    op = o;
    bill = new Bill (la);
    totalSpentTalkingTime = 0;
    totalMessageSent = 0;
    totalInternetUsage = 0;
}
//Constructor de copia.
Customer::Customer(const Customer &other){
    id = other.id;
    name = other.name;
    age = other.age;
    bill = other.bill;
    op = other.getOperator();
    totalSpentTalkingTime = other.totalSpentTalkingTime;
    totalMessageSent = other.totalMessageSent;
    totalInternetUsage = other.totalInternetUsage;
}
//Destructor. Debe eliminar la factura.
//Todos los apuntadores debe ser igualados a nulo.
Customer::~Customer(){
    delete bill;
    bill = NULL;
    op = NULL;
}

//Métodos de acceso para todas las variables de instancia
int Customer:: getId() const{
    return id;
}
int Customer:: getAge() const{
    return age;
}
int Customer:: getTotalSpentTalkingTime() const{
    return totalSpentTalkingTime;
}
int Customer::getTotalMessageSent() const{
    return totalMessageSent;
}
double Customer::getTotalInternetUsage() const{
    return totalInternetUsage;
}
std::string Customer::getName() const{
    return name;
}
Operator* Customer:: getOperator() const{
    return op;
}
Bill* Customer:: getBill() const{
    return bill;
}

//Método de modificación para la variable op.
void Customer:: setOperator(Operator *o){
    op = o;
}

//Si la cantidad es mayor a 0 y other es un cliente diferente, se calcula el costo
// por los minutos que duró la llamada. Si todavía hay límite de crédito en la factura,
// deberá agregar el costo a la factura y agrega los minutos empleados tanto en el conteo de
// los clientes involucrados como del operador de este cliente.
void Customer:: talk (int minutes, Customer &other){
    double cost;
    bool canIContinue = ((minutes > 0) && (id != other.id));
    if(canIContinue){
        cost = op->calculateTalkingCost(minutes, age);
        if(bill->check(cost)){
            bill->add(cost);
            totalSpentTalkingTime += minutes;
            op->addTalkingTime(minutes);
            if(other.op->getId() != op->getId()){
                other.op->addTalkingTime(minutes);
            }
        }
    }
}


//Si la cantidad es mayor a 0 y other es un cliente diferente, se calcula el costo por los
// mensajes enviados. Si todavía hay límite de crédito en la factura, deberá agregar el costo
// a la factura y agrega los mensajes enviados en el conteo del cliente y del operador.
void Customer::message (int quantity, const Customer &other){
    double cost;
    bool canIContinue = ((quantity > 0) && (id != other.id));
    if(canIContinue){
        cost = op->calculateMessageCost(quantity, op->getId(), other.op->getId());
        if(bill->check(cost)){
            bill->add(cost);
            totalMessageSent += quantity;
            op->addTotalMessageSent(quantity);
        }
    }
}

//Si la cantidad es mayor a 0, se calcula el costo por el uso de Internet. Si todavía hay
// límite de crédito en la factura, deberá agregar el costo a la factura y agrega los GB
// utilizados tanto en el conteo del cliente y del operador.
void Customer::connection(double amount){
    double cost;
    bool canIContinue = (amount > 0);
    if(canIContinue){
        cost = op->calculateNetworkCost(amount);
        if(bill->check(cost)){
            bill->add(cost);
            totalInternetUsage += amount;
            op->addTotalInternetUsage(amount);
        }

    }
}
//Si la cantidad es mayor a 0 paga
void Customer::pay(double amount){
    if(amount > 0){
        bill->pay(amount);
    }
}


//Regresa un string con el siguiente formato: "Customer #id : totalMoneySpend currentDebt".
// Todas las cantidades de punto flotantes deben tener una precisión de dos números decimales.
std::string Customer:: toString() const{
    std::stringstream aux;

    aux << std::fixed << std::setprecision(2);
    aux << "Customer " << id << ": " << bill->getTotalMoneySpent() << " " << bill->getCurrentDebt();

    return aux.str();
}


#endif
