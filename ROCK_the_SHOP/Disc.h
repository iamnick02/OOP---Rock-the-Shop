#ifndef DISC_H
#define DISC_H

#include "Product.h"

using namespace std;

class Disc : public Product {
private:
    string recordLabel;
    string releaseDate;
    string band;
    string albumName;

public:
    Disc();
    Disc(string name, int stock, float basePrice, string uniqueCode, string recordLabel, string releaseDate, string band, string albumName);
    float calculateDeliveryPrice() const override;

    string getRecordLabel() const;
    string getReleaseDate() const;
    string getBand() const;
    string getAlbumName() const;
    string getType() const override;
    void displayProductDetails() const override;
};

#endif
