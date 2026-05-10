//
// Created by ovast on 4/21/2026.
//

#ifndef OOP_PROJEKT_TOSTRINGHELPER_H
#define OOP_PROJEKT_TOSTRINGHELPER_H
#include <string>


class ToStringHelper {
public:
    virtual ~ToStringHelper() = default;

private:
    virtual std::string vypis(bool kratky) = 0;
};


#endif //OOP_PROJEKT_TOSTRINGHELPER_H