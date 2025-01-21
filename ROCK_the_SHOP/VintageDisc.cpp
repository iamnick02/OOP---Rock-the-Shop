#include "VintageDisc.h"

VintageDisc::VintageDisc() : Disc(), isMintCondition(false), rarityCoefficient(0) {}

VintageDisc::VintageDisc(string name, int stock, float basePrice, string uniqueCode, string recordLabel, string releaseDate, string band, string albumName, bool isMintCondition, int rarityCoefficient)
    : Disc(name, stock, basePrice, uniqueCode, recordLabel, releaseDate, band, albumName), isMintCondition(isMintCondition), rarityCoefficient(rarityCoefficient) {}

float VintageDisc::calculateDeliveryPrice() const {
    return getBasePrice() + 5 + (15 * rarityCoefficient);
}

bool VintageDisc::getIsMintCondition() const {
    return isMintCondition;
}

int VintageDisc::getRarityCoefficient() const {
    return rarityCoefficient;
}

string VintageDisc::getType() const {
    return "VintageDisc";
}

void VintageDisc::displayProductDetails() const {
    cout << "Disc Vintage: " << getName() << " (Cod: " << getUniqueCode() << ")"
         << "\nStoc: " << getStock() << ", Pret de baza: " << getBasePrice() << " RON"
         << ", Pret final (cu livrare si raritate): " << calculateDeliveryPrice() << " RON"
         << "\nCasa de discuri: " << getRecordLabel() << ", Data lansarii: " << getReleaseDate()
         << "\nTrupa: " << getBand() << ", Nume album: " << getAlbumName()
         << "\nStare mint: " << (getIsMintCondition() ? "Da" : "Nu") << ", Coeficient raritate: " << getRarityCoefficient() << "\n";
}

