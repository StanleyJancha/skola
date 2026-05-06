//
// Created by ovast on 4/20/2026.
//

#ifndef OOP_PROJEKT_VLAK_H
#define OOP_PROJEKT_VLAK_H
#include "Prostredek.h"


class Vlak : public Prostredek{
    uint8_t pocetVagonu;
    uint8_t kapacita_vagonu; // kapacita jednoho vagonu

public:
    Vlak(uint8_t rychlost, uint8_t pocet_vagonu,uint8_t kapacita_vagonu);
};


#endif //OOP_PROJEKT_VLAK_H