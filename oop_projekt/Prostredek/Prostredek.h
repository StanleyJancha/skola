//
// Created by ovast on 4/20/2026.
//

#ifndef OOP_PROJEKT_PROSTREDEK_H
#define OOP_PROJEKT_PROSTREDEK_H
#include "../Pomocne/ToStringHelper.h"
using namespace std;

#include <cstdint>
#include <vector>

#include "../Zasilky/Zasilka.h"


class Prostredek : public ToStringHelper{
    static ID_Manager id_manager;
protected:
    uint32_t id;

    uint8_t rychlost;
    vector<Zasilka*> naklad;
    uint8_t celkova_kapacita;

public:
    virtual ~Prostredek() = default;

    Prostredek(uint8_t rychlost,uint8_t celkova_kapacita)
        : rychlost(rychlost),
        celkova_kapacita(celkova_kapacita){
        this->id = id_manager.get_id();
    }

    virtual bool muzeNabratZasilku(Zasilka *zasilka);
    virtual bool nabratZasilku(Zasilka* zasilka);

    Zasilka* vyndatZasilku(uint8_t index_zasilky);
    bool vyndatZasilku(Zasilka* zasilka);


    uint8_t get_naklad_vaha();
    uint8_t get_naklad_objem();
    uint8_t get_naklad_pocet();


    string vypis(bool kratky) override;

    uint32_t get_id() const {
        return id;
    }

    void set_id(uint32_t id) {
        this->id = id;
    }

    [[nodiscard]] uint8_t get_rychlost() const {
        return rychlost;
    }

    void set_rychlost(uint8_t rychlost) {
        this->rychlost = rychlost;
    }

    [[nodiscard]] vector<Zasilka *> get_naklad() const {
        return naklad;
    }

    void set_naklad(const vector<Zasilka *> &naklad) {
        this->naklad = naklad;
    }

    [[nodiscard]] uint8_t get_celkova_kapacita() const {
        return celkova_kapacita;
    }

    void set_celkova_kapacita(uint8_t celkova_kapacita) {
        this->celkova_kapacita = celkova_kapacita;
    }
};


#endif //OOP_PROJEKT_PROSTREDEK_H