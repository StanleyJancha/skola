//
// Created by ovast on 4/20/2026.
//

#ifndef OOP_PROJEKT_SKLADISTE_H
#define OOP_PROJEKT_SKLADISTE_H
#include <algorithm>
#include <vector>

#include "Zasilka.h"
#include "../Prostredek/Prostredek.h"

using namespace std;

class Skladiste :ToStringHelper{
    static ID_Manager id_manager;

    uint32_t id;

    vector<Zasilka*> zasilky_ze_skladu;
    uint8_t kapacita;

public:
    Skladiste(uint8_t kapacita);

    bool prijmoutZasilku(Zasilka *zasilka);

    Zasilka* vybratZasilku(uint8_t index);

    bool vybratZasilku(Zasilka *zasilka);

    uint8_t naplnitProstredek(Prostredek *prostredek);

    string vypis(bool kratky) override;

    Zasilka* get_zasilka(uint8_t index);

    uint8_t get_kapacita();
    uint8_t get_pocetVeSkladu();
};


#endif //OOP_PROJEKT_SKLADISTE_H