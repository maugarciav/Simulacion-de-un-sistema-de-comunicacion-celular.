// =========================================================
// File: vox.h
// Author: Mauricio Garcia Villanueva - A01704098
// Date: 5 / junio /2022
// Description: Este tipo de operador se especializa en aquellas personas que
// hacen un uso más intensivo de las llamadas y los mensajes de texto. Deriva de Operator.
// =========================================================

#ifndef VOXOPERATOR_H
#define VOXOPERATOR_H

#include "operator.h"

class VoxOperator : public Operator {
public:
  VoxOperator(int, double, double, double, int, OperatorType);
  VoxOperator(const VoxOperator&);

  double calculateTalkingCost(int, int);
  double calculateMessageCost(int, int, int);
  double calculateNetworkCost(double);
};

// Constructor con 6 parámetros. Recibe el id, el costo por minuto de llamada, el costo por envío de
// mensaje, el costo por GB, el porcentaje de descuento y el tipo de operador. Debe invocar
// al constructor de la clase superior.
VoxOperator:: VoxOperator(int id, double costTalk, double costMess , double costGB, int disc, OperatorType t)
        :Operator (id, costTalk, costMess, costGB, disc, t){
}


//Constructor de copia. Debe invocar al constructor de la clase superior.
VoxOperator:: VoxOperator(const VoxOperator &other)
    :Operator(other){
}

// Si la cantidad de minutos o la edad es menor igual a 0, regresará 0. En caso contrario, calcula el
// costo de la llamada tomando en cuenta el costo por minuto definido. Si la persona es menor a
// 18 o mayor a 65, le aplica el descuento definido.
double VoxOperator ::  calculateTalkingCost(int minute, int age){
    double costtalk;
    if (minute <= 0){
        return 0;
    }
    if (age <= 0){
        return 0;
    }
    if ((age < 18) || (age > 65) ){
        costtalk =  (1-(double(discountRate)/100)) * (talkingCharge * minute);
    }
    else{
        costtalk =  talkingCharge * minute ;
    }

    return costtalk;
}

//Si la cantidad de mensajes es menor igual a 0, regresará 0. En caso contrario, calcula el costo
//de enviar los mensajes tomando en cuenta el costo por envío definido.
//Si los mensajes son enviados al mismo operador, le aplica el descuento definido.
double VoxOperator:: calculateMessageCost(int quantity, int thisOpId, int otherOpId){
    double costmess;
    if (quantity <= 0){
        return 0;
    }
    if(thisOpId == otherOpId){
        costmess = (1-(double(discountRate)/100)) * (messageCost * quantity);
    }
    else{
        costmess =  messageCost * quantity;
    }

    return costmess;

}

//Si la cantidad de GB es mayor a 0, calcula el costo por GB.
double VoxOperator:: calculateNetworkCost(double amount){
    double costnet;
    if (amount <= 0){
        return 0;
    }
    else{
        costnet = networkCharge * amount;
    }
    return costnet;

}
#endif
