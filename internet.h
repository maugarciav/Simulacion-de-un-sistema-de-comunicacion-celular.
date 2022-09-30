// =========================================================
// File: internet.h
// Author: Mauricio Garcia Villanueva - A01704098
// Date: 6 /Junio/ 2022
// Description:Este tipo de operador se especializa en aquellas personas
// que hacen un uso más intensivo de Internet. Deriva de Operator.
// =========================================================

#ifndef InternetOperator_H
#define InternetOperator_H

#include "operator.h"

class InternetOperator : public Operator {
private:
  const double LIMITGB = 1.0;

public:
  InternetOperator(int, double, double, double, int, OperatorType);
  InternetOperator(const InternetOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

//Constructor con 6 parámetros. Recibe el id, el costo por minuto de llamada, el costo por envío de
// mensaje, el costo por GB, el porcentaje de descuento y el tipo de operador.
// Debe invocar al constructor de la clase superior.
InternetOperator:: InternetOperator(int id, double costTalk, double costMess , double costGB, int disc, OperatorType t)
        :Operator (id, costTalk, costMess, costGB, disc, t){
}

//Constructor de copia. Debe invocar al constructor de la clase superior.
InternetOperator:: InternetOperator(const InternetOperator &other)
        :Operator(other){
}

//Si la cantidad de minutos o la edad es menor igual a 0, regresará 0. En caso contrario, calcula el costo
//de la llamada tomando en cuenta el costo por minuto definido. Si la cantidad de minutos
//es menor a 2, le aplica el descuento definido.
double InternetOperator:: calculateTalkingCost(int minute , int age){
    double costtalk;
   if (minute <= 0){
        return 0;
    }
    if (age <= 0){
        return 0;
    }
    if (minute < 2){
        costtalk = (1-(discountRate/100.0)) * (talkingCharge * minute);
    }
    else{
        costtalk = talkingCharge * minute;
    }

    return costtalk;
}

//Si la cantidad de mensajes es menor igual a 0, regresará 0. En caso contrario, calcula el costo de enviar los
// mensajes tomando en cuenta el costo por envío definido. Si la cantidad de
// mensajes enviados es menor a 3, le aplica el descuento definido.
double InternetOperator:: calculateMessageCost(int quantity, int thisOpId, int otherOpId){
    double costmess;
    if (quantity <= 0){
        return 0;
    }

    if (quantity < 3){
        costmess = (1-(double(discountRate)/100)) * (messageCost * quantity);
    }
    else{
        costmess = messageCost * quantity;
    }
    return costmess;

}


//Si la cantidad de GB es menor o igual a cero, regresará 0.
// Sólo se aplicarán cargos si la cantidad de GB utilizados en total, excede al limite de 1GB.
double InternetOperator:: calculateNetworkCost(double amount) {
    double costnet = 0;
    if (amount <= 0) {
        return 0;
    }
    if (amount + totalInternetUsage > LIMITGB) {
        costnet = (amount - LIMITGB) * networkCharge;
    }
    return costnet;
}

#endif
