// =========================================================
// File: operator.h
// Author: Mauricio Garcia Villanueva
// Date: 04/ Junio / 2022
// Description: Implementacion de la clase base operador
// =========================================================

#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <sstream>
#include <iomanip>

typedef enum{VOX, INTERNET} OperatorType;

class Operator {
protected:
  int id, discountRate;
  double talkingCharge, messageCost, networkCharge, totalInternetUsage;
  int totalSpentTalkingTime, totalMessageSent;
  OperatorType type;

public:
  Operator(int, double, double, double, int, OperatorType);
  Operator(const Operator&);

  int getId() const;
  int getDiscountRate() const;
  double getTalkingChage() const;
  double getMessageCost() const;
  double getNetworkCharge() const;
  int getTotalSpentTalkingTime() const;
  int getTotalMessageSent() const;
  double getTotalInternetUsage() const;
  OperatorType getType() const;

  void addTalkingTime(int);
  void addTotalMessageSent(int);
  void addTotalInternetUsage(double);

  std::string toString() const;

  virtual double calculateTalkingCost(int, int) = 0;
  virtual double calculateMessageCost(int, int, int) = 0;
  virtual double calculateNetworkCost(double) = 0;
};

//Constructor con 6 parámetros. Recibe el id, el costo por minuto de llamada, el costo por envío de mensaje, el costo
// por GB, el porcentaje de descuento y el tipo de operador. El resto de las variables debe inicializarse a 0.
Operator :: Operator(int id, double costTalk, double costMess , double costGB, int disc, OperatorType t){
    this -> id = id;
    discountRate = disc;
    talkingCharge = costTalk;
    messageCost = costMess;
    networkCharge = costGB;
    totalSpentTalkingTime = 0;
    totalMessageSent = 0;
    totalInternetUsage = 0;
    type = t;
}

//Constructor de copia
Operator:: Operator(const Operator &other){
    id = other.id;
    discountRate = other.discountRate;
    talkingCharge = other.talkingCharge;
    messageCost = other.messageCost;
    networkCharge = other.networkCharge;
    totalSpentTalkingTime = other.totalSpentTalkingTime;
    totalMessageSent = other.totalMessageSent;
    totalInternetUsage = other.totalInternetUsage;
    type = other.type;
}

// Métodos de acceso para todas las variables de instancia

int Operator :: getId() const{
    return id;
}

int Operator ::  getDiscountRate() const{
    return discountRate;
}

double Operator :: getTalkingChage() const{
    return talkingCharge;
}

double Operator :: getMessageCost() const{
    return messageCost;
}
double Operator :: getNetworkCharge() const{
    return networkCharge;
}

int Operator :: getTotalSpentTalkingTime() const{
    return totalSpentTalkingTime;
}

int Operator :: getTotalMessageSent() const{
    return totalMessageSent;
}

double Operator :: getTotalInternetUsage() const{
    return totalInternetUsage;
}
OperatorType Operator :: getType() const{
    return type;
}

//Si la cantidad es mayor a 0, agrega la cantidad al tiempo total que se ha empleado en llamadas.
void Operator :: addTalkingTime(int minute){
    if (minute < 0){
        return;
    }
    totalSpentTalkingTime += minute;
}

//Si la cantidad es mayor a 0, agrega la cantidad al total de mensajes enviados.
void Operator :: addTotalMessageSent(int quantity){
    if (quantity < 0){
        return;
    }
    totalMessageSent += quantity;
}

//Si la cantidad es mayor a 0, agrega la cantidad a los GB's totales empleados.
void Operator :: addTotalInternetUsage(double amount){
    if (amount < 0){
        return;
    }
    totalInternetUsage += amount;
}

//Regresa un string con el siguiente formato: "Operator #id : totalSpentTalkingTime totalMessageSent
// addTotalInternetUsage". Todas las cantidades de punto flotantes deben tener una precisión de dos números decimales.
std::string Operator :: toString() const{
  std::stringstream aux;

    aux << std::fixed << std::setprecision(2);
    aux << "Operator " << id << ": " << std::fixed << std::setprecision(2) << totalSpentTalkingTime << " " << totalMessageSent << " " << totalInternetUsage;

    return aux.str();
}


#endif
