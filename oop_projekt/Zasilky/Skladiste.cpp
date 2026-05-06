//
// Created by ovast on 4/20/2026.
//

#include "Skladiste.h"

#include <iostream>
#include <exception>

ID_Manager Skladiste::id_manager;


Skladiste::Skladiste(uint8_t kapacita) {
    this->kapacita = kapacita;
    this->id = id_manager.get_id();
}


/// Prida do skladu zasilku
/// @return Vrati bool podle toho, jestli se podarilo zasilku do skladu vlozit
bool Skladiste::prijmoutZasilku(Zasilka *zasilka) {
    if (zasilky_ze_skladu.size() < kapacita) {
        zasilky_ze_skladu.push_back(zasilka);
        return true;
    }
    return false;
}

/// Ze skladiste odstrani zasilku na indexu
/// @return vrati pointer na odstranenou zasilku
Zasilka* Skladiste::vybratZasilku(uint8_t index) {
    if (index > this->kapacita) {
        return nullptr;
    }
    Zasilka *zasilka_na_odebrani =  zasilky_ze_skladu.at(index);
    if (zasilka_na_odebrani) {
        zasilky_ze_skladu.erase(zasilky_ze_skladu.begin() + index);
        return zasilka_na_odebrani;
    }
    return nullptr;
}

/// Ze skladiste odstrani zasilku poslanou jako pointer
/// @return Vrati bool zda se pointer na zasilku podarilo ve vectoru najit a smazat
bool Skladiste::vybratZasilku(Zasilka *zasilka) {
    auto zasilka_na_odebrani_iterator = find(zasilky_ze_skladu.begin(),zasilky_ze_skladu.end(),zasilka);
    if (zasilka_na_odebrani_iterator != zasilky_ze_skladu.end()) {
        zasilky_ze_skladu.erase(zasilka_na_odebrani_iterator);
        return true;
    }
    return false;
}

uint8_t Skladiste::naplnitProstredek(Prostredek *prostredek) {
    uint8_t maximalni_mozne_nalozeni = prostredek->get_celkova_kapacita() - prostredek->get_naklad().size();

    int limit = std::min((int)maximalni_mozne_nalozeni, (int)zasilky_ze_skladu.size());
    uint8_t pocitadlo = 0;

    for (int i = limit - 1; i >= 0; i--) {
        Zasilka* aktualniZasilka = this->get_zasilka(i);

        if (aktualniZasilka != nullptr) {
            if (prostredek->muzeNabratZasilku(aktualniZasilka)) {
                Zasilka* zasilka_ze_skladu = this->vybratZasilku(i);
                if (prostredek->nabratZasilku(zasilka_ze_skladu)) {
                    pocitadlo++;
                }
            } else {
                break;
            }
        }
    }
    return pocitadlo;

}

/// Posklada string o promennych v jednotlivych zasilkach. U zasilek se pozuiva metoda toString()
/// @return String, ktery obsahuje informace jednotlivych zasilek
string Skladiste::vypis(bool kratky){
    string str = "Skladiste id: "+ to_string(id) + '\n';
    if (kratky) {
        str += "\tpocet zasilek v skladisti je " + to_string(zasilky_ze_skladu.size());
    }
    else {
        for (auto zasilka : zasilky_ze_skladu) {
            str += '\t';
            str += zasilka->toString();
            str += '\n';
        }
    }
    return str;
}

Zasilka* Skladiste::get_zasilka(uint8_t index) {
    if (index < zasilky_ze_skladu.size()) {
        return zasilky_ze_skladu.at(index);
    }
    return nullptr;
}

uint8_t Skladiste::get_kapacita() {
    return  kapacita;
}

uint8_t Skladiste::get_pocetVeSkladu() {
    return zasilky_ze_skladu.size();
}
