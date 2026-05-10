//
// Created by ovast on 4/20/2026.
//

#include "Prostredek.h"

#include <algorithm>
#include <iostream>
#include <ostream>

using namespace std;

ID_Manager Prostredek::id_manager;


bool Prostredek::muzeNabratZasilku(Zasilka *zasilka) {
    auto size = naklad.size();
    if (size >= this->celkova_kapacita) {
        //std::cout << "Prostredek id: " + to_string(this->id) + " nemuze nabrat zaislku, protoze by predkrocil limit kapacity kusu"<<endl;
        return false;
    }
    return true;
}


bool Prostredek::nabratZasilku(Zasilka *zasilka) {
    if(!this->muzeNabratZasilku(zasilka)) {
        return false;
    }
    this->naklad.push_back(zasilka);
    return true;
}

Zasilka * Prostredek::vyndatZasilku(uint8_t index) {
    Zasilka *zasilka_na_odebrani =  naklad.at(index);
    if (zasilka_na_odebrani) {
        naklad.erase(naklad.begin() + index);
        return zasilka_na_odebrani;
    }
    return nullptr;

}

bool Prostredek::vyndatZasilku(Zasilka *zasilka) {
    auto zasilka_na_odebrani_iterator = find(naklad.begin(),naklad.end(),zasilka);
    if (zasilka_na_odebrani_iterator != naklad.end()) {
        naklad.erase(zasilka_na_odebrani_iterator);
        return true;
    }
    return false;
}

uint8_t Prostredek::get_naklad_vaha() {
    uint8_t vaha = 0;
    for (Zasilka *z: naklad) {
        vaha += z->get_vaha();
    }
    return vaha;
}

uint8_t Prostredek::get_naklad_objem() {
    uint8_t objem = 0;
    for (Zasilka *z: naklad) {
        objem += z->get_objem();
    }
    return objem;
}

uint8_t Prostredek::get_naklad_pocet() {
    return naklad.size();
}

string Prostredek::vypis(bool kratky) {
    string str = "Prostredek id: " + to_string(id) + "\n";
    if (kratky) {
        str += "\tpocet zasilek v nakladu je " + to_string(naklad.size());
    }
    else {
        for (auto zasilka : naklad) {
            str += '\t';
            str += zasilka->vypis(true);
            str += '\n';
        }
    }
    return str;
}
