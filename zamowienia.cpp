#include "zamowienia.hpp"
#include "punkty.hpp"
#include <iostream>
using namespace std;
Zamowienie::Zamowienie() {
    zamowionaPizzaID = 0;
    czyZadowolony = false;
    punkty = 0;
    czyZadowolony = false;
    punkty = 0;
    zrobionePizze = 0;
    zadowoleniKlienci = 0;
}

Zamowienie::Zamowienie(int zamowionaPizzaID, bool czyZadowolony, int punkty,int zrobionePizze,int zadowoleniKlienci) : zamowionaPizzaID(zamowionaPizzaID), czyZadowolony(czyZadowolony), punkty(punkty), zrobionePizze(zrobionePizze), zadowoleniKlienci(zadowoleniKlienci) {}



void Zamowienie::wylosujPizzaID() {
    zamowionaPizzaID = rand() % 5 + 1;
}

void Zamowienie::sprawdzPoprawnosc(bool pizzaDodana, bool sosDodany, bool serDodany,bool peperoniDodane, bool pieczarkiDodane, bool cebulaDodana,bool popranwiePrzypieczona) {
    if (zamowionaPizzaID == 1 && pizzaDodana == true && sosDodany == true && serDodany == true&& peperoniDodane == false && pieczarkiDodane == false && cebulaDodana == false && popranwiePrzypieczona == true) {
        
        czyZadowolony = true;
        punkty = punkty + 10;
        zrobionePizze++;
        zadowoleniKlienci++;

    } else if (zamowionaPizzaID == 2 && pizzaDodana == true && sosDodany == true && serDodany == true && peperoniDodane == true && pieczarkiDodane == false && cebulaDodana == false && popranwiePrzypieczona == true) {
       
        czyZadowolony = true;
        punkty =  punkty + 10;
        zrobionePizze++;
        zadowoleniKlienci++;

    } else if (zamowionaPizzaID == 3 && pizzaDodana == true && sosDodany == true && serDodany == true && peperoniDodane == false && pieczarkiDodane == true && cebulaDodana == false && popranwiePrzypieczona == true) {
       
        czyZadowolony = true;
        punkty =  punkty + 10;
        zrobionePizze++;
        zadowoleniKlienci++;

    } else if (zamowionaPizzaID == 4 && pizzaDodana == true && sosDodany == true && serDodany == true &&  peperoniDodane == false && pieczarkiDodane == false && cebulaDodana == true && popranwiePrzypieczona == true) {
       
        czyZadowolony = true;
        punkty =  punkty + 10;
        zrobionePizze++;
        zadowoleniKlienci++;

    } else if (zamowionaPizzaID == 5 && pizzaDodana == true && sosDodany == true && serDodany == true && peperoniDodane == true && pieczarkiDodane == true && cebulaDodana == true && popranwiePrzypieczona == true) {
       
        czyZadowolony = true;
        punkty = punkty + 10;
        zrobionePizze++;
        zadowoleniKlienci++;

    } else {
       
        czyZadowolony = false;
        popranwiePrzypieczona = false;
        punkty = punkty - 5;
        zrobionePizze++;
    }
}

std::string Zamowienie::tekstZamowienia() const {
    switch (zamowionaPizzaID) {
        case 1: 
            return "Pizza Margarita";
        case 2: 
            return "Pizza Peperonii";
        case 3: 
            return "Pizza z Pieczarkami";
        case 4: 
            return "Pizza z Cebula";
        case 5: 
            return "Pizza z Peperonii, z Pieczarkami i z Cebula";
    }
}

bool Zamowienie::getCzyZadowolony() const {
    return czyZadowolony;
}

int Zamowienie::getPunkty() const {
    return punkty;
}

int Zamowienie::getPizzaID() const {
    return zamowionaPizzaID;
}

int Zamowienie::getZrobionePizze() const {
    return zrobionePizze;
}

int Zamowienie::getZadowoleniKlienci() const {
    return zadowoleniKlienci;
}
