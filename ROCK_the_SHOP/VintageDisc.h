#ifndef VINTAGE_DISC_H
#define VINTAGE_DISC_H

#include "Disc.h"

using namespace std;

class VintageDisc : public Disc {
private:
    bool isMintCondition;
    int rarityCoefficient;

public:
    VintageDisc();
    VintageDisc(string name, int stock, float basePrice, string uniqueCode, string recordLabel, string releaseDate, string band, string albumName, bool isMintCondition, int rarityCoefficient);
    float calculateDeliveryPrice() const override;

    bool getIsMintCondition() const;
    int getRarityCoefficient() const;
    string getType() const override;
    void displayProductDetails() const override;
};

#endif
