//
// Created by ovast on 4/20/2026.
//

#ifndef OOP_PROJEKT_ID_MANAGER_H
#define OOP_PROJEKT_ID_MANAGER_H
#include <cstdint>


class ID_Manager {
    uint32_t id = 0;

public:

    uint32_t get_id() {
        return id++;
    }


};


#endif //OOP_PROJEKT_ID_MANAGER_H