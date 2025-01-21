#include "Disc.h"

Disc::Disc() : Product(), recordLabel(""), releaseDate(""), band(""), albumName("") {}

Disc::Disc(string name, int stock, float basePrice, string uniqueCode, string recordLabel, string releaseDate, string band, string albumName)
    : Product(name, stock, basePrice, uniqueCode), recordLabel(recordLabel), releaseDate(releaseDate), band(band), albumName(albumName) {}

float Disc::calculateDeliveryPrice() const {
    return getBasePrice() + 5;
}

string Disc::getRecordLabel() const {
    return recordLabel;
}

string Disc::getReleaseDate() const {
    return releaseDate;
}

string Disc::getBand() const {
    return band;
}

string Disc::getAlbumName() const {
    return albumName;
}

string Disc::getType() const {
    return "Disc";
}

void Disc::displayProductDetails() const {
    cout << "Disc: " << getName() << " (Cod: " << getUniqueCode() << ")"
         << "\nStoc: " << getStock() << ", Pret de baza: " << getBasePrice() << " RON"
         << ", Pret final (cu livrare): " << calculateDeliveryPrice() << " RON"
         << "\nCasa de discuri: " << getRecordLabel() << ", Data lansarii: " << getReleaseDate()
         << "\nTrupa: " << getBand() << ", Nume album: " << getAlbumName() << "\n";
}
