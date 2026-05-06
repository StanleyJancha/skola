//
// Created by ovast on 4/21/2026.
//

#ifndef OOP_PROJEKT_NAKLADNIAUTO_H
#define OOP_PROJEKT_NAKLADNIAUTO_H
#include <cstdint>

#include "Prostredek.h"


class NakladniAuto :public Prostredek{
    uint8_t maximalni_objem;

public:
    NakladniAuto(uint8_t rychlost, uint8_t celkova_kapacita, uint8_t maximalni_objem)
        : Prostredek(rychlost, celkova_kapacita),
          maximalni_objem(maximalni_objem) {
    }

    bool muzeNabratZasilku(Zasilka* zasilka) override;
};


#endif //OOP_PROJEKT_NAKLADNIAUTO_H