// =========================================================
// File: main.cpp
// Author: Mauricio Garcia Villanueva - A01704098
// Date: 14 Junio 2022
// Description: En este archivo se realiza la lectura y/o escitura de archivos
// To compile: g++ -std=c++11 main.cpp -o app
// To execute: ./app input_file output_file
// =========================================================
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bill.h"
#include "operator.h"
#include "vox.h"
#include "internet.h"
#include "customer.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputFile;
    ofstream outputFile;
    int C, O, N;

    if (argc != 3) {
        cout << "usage: " << argv[0] << " input_file output_file\n";
        return -1;
    }
    inputFile.open(argv[1]);
    if (!inputFile.is_open()) {
        cout << argv[0] << ": File \"" << argv[1] << "\" not found\n";
        return -1;
    }

    outputFile.open(argv[2]);
    inputFile >> C >> O >> N;


    vector <Customer*> customers(C);
    vector <Operator*> operators(O);
    int operation, operatorid, age, discountRate, optype, idcustomer1, idcustomer2, time, quantity;
    double amount, limitingAmount, talkingCharge, messageCost, networkCharge;
    string name;

    int idCustomer = 0;
    int idOperator = 0;

    for(int i = 0; i < N; i++){
        inputFile >> operation;
        switch (operation) {
            case 1:
                inputFile >> name >> age >> operatorid >> limitingAmount;
                customers[idCustomer] = new Customer(idCustomer, name, age, operators[operatorid], limitingAmount);
                idCustomer++;
                break;

            case 2:
                inputFile >> optype >> talkingCharge >> messageCost >> networkCharge >> discountRate;
                if (optype == 1){
                    operators[idOperator] = new VoxOperator(idOperator, talkingCharge, messageCost,  networkCharge, discountRate, VOX);
                }
                else {
                    operators[idOperator] = new InternetOperator(idOperator, talkingCharge, messageCost, networkCharge, discountRate,
                                                          INTERNET);
                }
                idOperator++;
                break;

            case 3:
                inputFile >> idcustomer1 >> idcustomer2 >> time;
                customers[idcustomer1]->talk(time, *customers[idcustomer2]);
                break;

            case 4:
                inputFile >> idcustomer1 >> idcustomer2 >> quantity;
                customers[idcustomer1]->message(quantity, *customers[idcustomer2]);
                break;

            case 5:
                inputFile >> idcustomer1 >> amount;
                customers[idcustomer1]->connection(amount);
                break;

            case 6:
                inputFile >> idcustomer1 >> amount;
                customers[idcustomer1]->pay(amount);
                break;

            case 7:
                inputFile >> idcustomer1 >> operatorid;
                customers[idcustomer1]->setOperator(operators[operatorid]);
                break;

            case 8:
                inputFile >> idcustomer1 >> amount;
                customers[idcustomer1]->getBill()->changeTheLimit(amount);
        }
    }
//Salida

vector <Operator*>::iterator i;
    for (i = operators.begin(); i != operators.end(); i++){
        outputFile << (*i)->toString() << endl;
    }
    Customer  *Talker = *(customers.begin()), *Messager= *(customers.begin()), *PlusGB = *(customers.begin());


    vector<Customer*>::iterator icustomers;
    for(icustomers = customers.begin(); icustomers != customers.end(); icustomers++){
        outputFile << (*icustomers)->toString() << "\n";
        if(Talker->getTotalSpentTalkingTime() < (*icustomers)->getTotalSpentTalkingTime()){
            Talker = (*icustomers);
        }
        if(Messager->getTotalMessageSent() < (*icustomers)->getTotalMessageSent()){
            Messager = (*icustomers);
        }
        if(PlusGB->getTotalInternetUsage() < (*icustomers)->getTotalInternetUsage()){
            PlusGB = (*icustomers);
        }
    }

    outputFile << (Talker)->getName() << ": " << (Talker)->getTotalSpentTalkingTime() << endl;
    outputFile << (Messager)->getName() << ": " << (Messager)->getTotalMessageSent() << endl;
    outputFile << (PlusGB)->getName() << ": " << fixed << setprecision(2) << (PlusGB)->getTotalInternetUsage() << endl;


    inputFile.close();
    outputFile.close();
    

    return 0;
}
