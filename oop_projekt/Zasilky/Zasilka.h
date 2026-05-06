//
// Created by ovast on 4/20/2026.
//

#ifndef OOP_PROJEKT_ZASILKA_H
#define OOP_PROJEKT_ZASILKA_H
#include <cstdint>
#include <string>

#include "../Pomocne/ID_Manager.h"
using namespace std;


class Zasilka {
    static ID_Manager id_manager;

    uint32_t id;
    string nazev;
    uint8_t vaha; // kg
    uint8_t objem; // m^3

    uint32_t id_ciloveho_skladu;

public:
    Zasilka(const string &nazev, uint8_t vaha, uint8_t objem);

    string toString();

    uint32_t get_id() const {
        return id;
    }

    void set_id(uint32_t id) {
        this->id = id;
    }

    string get_nazev() const {
        return nazev;
    }

    void set_nazev(const string &nazev) {
        this->nazev = nazev;
    }

    uint8_t get_vaha() const {
        return vaha;
    }

    void set_vaha(uint8_t vaha) {
        this->vaha = vaha;
    }

    uint8_t get_objem() const {
        return objem;
    }

    void set_objem(uint8_t objem) {
        this->objem = objem;
    }
};


#endif //OOP_PROJEKT_ZASILKA_H