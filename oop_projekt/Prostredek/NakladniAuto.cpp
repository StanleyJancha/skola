//
// Created by ovast on 4/21/2026.
//

#include "NakladniAuto.h"

bool NakladniAuto::muzeNabratZasilku(Zasilka* zasilka){
    if (get_naklad_objem() + zasilka->get_objem() > this->maximalni_objem) {
        //printf("NakladniAuto id:%d\tneprijalo dalsi balik, protoze by objem nakladu byl vetsi nez maximalni mozny objem\n",this->get_id());
        return false;
    }
    return Prostredek::muzeNabratZasilku(zasilka);
}