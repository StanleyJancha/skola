//
// Created by ovast on 4/21/2026.
//

#ifndef OOP_PROJEKT_LOD_H
#define OOP_PROJEKT_LOD_H
#include <cstdint>

#include "Prostredek.h"


class Lod : public Prostredek{
    uint8_t nosnost;

public:
    Lod(uint8_t rychlost, uint8_t celkova_kapacita, uint8_t nosnost)
        : Prostredek(rychlost, celkova_kapacita),
          nosnost(nosnost) {
    }

private:
    bool muzeNabratZasilku(Zasilka *zasilka) override;
};


#endif //OOP_PROJEKT_LOD_H