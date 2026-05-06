#include <iostream>

#include "Prostredek/Lod.h"
#include "Prostredek/Vlak.h"
#include "Zasilky/Skladiste.h"

int main() {

    Skladiste skladiste(100);
    Skladiste skladiste2(100);

    cout << skladiste.vypis(true) << endl;

    for (int i = 0; i < 50; ++i) {
        skladiste.prijmoutZasilku(new Zasilka("balicek" + to_string(i),1,1));
    }

    cout << skladiste.vypis(true) << endl;

    // Vlak *vlak = new Vlak(30,3,10);

    Lod *lod = new Lod(30,10,6);

    cout << "Prendalo se " + to_string(skladiste.naplnitProstredek(lod)) + " kusu zbozi" <<endl;
    cout << skladiste.vypis(true) << endl;

    cout << lod->vypis(true) << endl;




return 0;
}