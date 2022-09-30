// =========================================================
// File: bill.h
// Author: Mauricio Garcia Villanueva - A01704098
// Date: 04/ Junio / 2022
// Description: Implementacion de la clase bill
// =========================================================

#ifndef BILL_H
#define BILL_H

class Bill {
private:
  double limitAmount, currentDebt, totalMoneySpent;

public:
  Bill();
  Bill(double);
  Bill(const Bill&);

  double getLimitAmount() const;
  double getCurrentDebt() const;
  double getTotalMoneySpent() const;

  void add(double);
  void pay(double);
  void changeTheLimit(double);
  bool check(double) const;
};

//Constructor Default
Bill :: Bill (){
    limitAmount = 0;
    currentDebt = 0;
    totalMoneySpent = 0;

}

//Constructor con un parámetro (el límite de crédito). Este método deberá inicializar el resto de variables a 0.
Bill :: Bill (double la){
    if(la >= 0){
        limitAmount = la;
    }
    else{
        limitAmount = 0;
    }
    currentDebt = 0;
    totalMoneySpent = 0;

}
//Constructor de copia.
Bill :: Bill (const Bill &other){
    limitAmount = other.limitAmount;
    currentDebt = other.currentDebt;
    totalMoneySpent = other.totalMoneySpent;
}

// Métodos de acceso para todas las variables de instancia
double Bill :: getLimitAmount() const{
    return limitAmount;
}
double Bill :: getCurrentDebt() const{
    return currentDebt;
}
double Bill :: getTotalMoneySpent() const{
    return totalMoneySpent;
}

// Agrega cargos a la factura. Si la cantidad es menor o igual 0, no deberá hacer cambios.
void Bill :: add(double amount){
    if(amount > 0){
        currentDebt += amount;
    }
}

//Reduce la deuda en la cantidad dada. Si la cantidad es menor o igual a 0, no
// deberá hacer cambios. Nunca se podrá pagar más cantidad que la deuda actual.
void Bill :: pay(double amount){
    if (amount > 0) {
        if (amount > currentDebt){
            totalMoneySpent += currentDebt;
            currentDebt = 0;
        }
        else{
            currentDebt -= amount;
            totalMoneySpent += amount;
        }
    }
}


//Cambia el límite de crédito, siempre y cuando sea mayor a la deuda
// actual. Si la cantidad es menor o igual a 0, no deberá hacer cambios.
void Bill:: changeTheLimit(double amount){
    if (amount > 0 && amount >= currentDebt){
        limitAmount = amount;
    }
}

//Regresa verdadero si la cantidad más la deuda actual no existe el límite de crédito.
bool Bill::  check(double amount) const{
    return ((amount + currentDebt) < limitAmount);
}

#endif
