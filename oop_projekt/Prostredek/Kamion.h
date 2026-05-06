//
// Created by ovast on 4/21/2026.
//

#ifndef OOP_PROJEKT_KAMION_H
#define OOP_PROJEKT_KAMION_H
#include "NakladniAuto.h"


class Kamion : public NakladniAuto{

    uint8_t pocetNavesu;
    uint8_t kapacita_navesu;

public:
    Kamion(uint8_t rychlost,uint8_t maximalni_objem_navesu, uint8_t pocet_navesu,uint8_t kapacita_navesu)
        : NakladniAuto(rychlost, pocet_navesu*kapacita_navesu, maximalni_objem_navesu * pocet_navesu),
          pocetNavesu(pocet_navesu),
          kapacita_navesu(kapacita_navesu) {
    }
};


#endif //OOP_PROJEKT_KAMION_H