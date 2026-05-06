//
// Created by ovast on 4/20/2026.
//

#include "Vlak.h"

#include <algorithm>

Vlak::Vlak(uint8_t rychlost, uint8_t pocet_vagonu,uint8_t kapacita_vagonu)
        : Prostredek(rychlost,pocet_vagonu*kapacita_vagonu),
          pocetVagonu(pocet_vagonu),
            kapacita_vagonu(kapacita_vagonu){
}


