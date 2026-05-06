//
// Created by ovast on 4/20/2026.
//

#include "Zasilka.h"

ID_Manager Zasilka::id_manager;

Zasilka::Zasilka(const string &nazev, uint8_t vaha, uint8_t objem)
        : nazev(nazev),
          vaha(vaha),
          objem(objem) {
    this->id = id_manager.get_id();
}

string Zasilka::toString() {
    return "Zasilka id:"+ to_string(id) + "\tnazev: " + nazev;
}
