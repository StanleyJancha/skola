//
// Created by ovast on 4/21/2026.
//

#include "Lod.h"

bool Lod::muzeNabratZasilku(Zasilka* zasilka){
    if (get_naklad_vaha() + zasilka->get_vaha() > this->nosnost) {
        //printf("Lod id:%d\tneprijala dalsi balik, protoze by hmotnost nakladu byla vetsi nez nosnost\n",this->get_id());
        return false;
    }
    return Prostredek::muzeNabratZasilku(zasilka);
}