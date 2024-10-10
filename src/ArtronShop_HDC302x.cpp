#include "ArtronShop_HDC302x.h"

ArtronShop_HDC302x::ArtronShop_HDC302x(TwoWire *wire, uint8_t addr) {
    this->_wire = wire;
    this->_addr = addr;
}

bool ArtronShop_HDC302x::begin() {
    // Soft Reset
    this->_wire->beginTransmission(this->_addr);
    this->_wire->write(0x30);
    this->_wire->write(0xA2);
    if (this->_wire->endTransmission() != 0) {
        return false;
    }

    delay(5); // wait sensor ready after a reset
    
    return true;
}

bool ArtronShop_HDC302x::measure() {
    // Trigger on Demand, 12.5ms conversion time
    this->_wire->beginTransmission(this->_addr);
    this->_wire->write(0x24);
    this->_wire->write(0x00);
    if (this->_wire->endTransmission() != 0) {
        this->_t = -99;
        this->_h = -99;
        return false;
    }

    delay(15);  // wait measuring

    if (this->_wire->requestFrom(this->_addr, (uint8_t)6) != 6) {
        this->_t = -99;
        this->_h = -99;
        return false;
    }

    uint8_t rx_bytes[6];
    memset(rx_bytes, 0, 6);
    this->_wire->readBytes(rx_bytes, 6);

    uint16_t t_ticks = ((uint16_t)rx_bytes[0] << 8) | rx_bytes[1];
    // checksum_t = rx_bytes[2];
    uint16_t rh_ticks = ((uint16_t)rx_bytes[3] << 8) | rx_bytes[4];
    // checksum_rh = rx_bytes[5];
    this->_t = -45.0f + (175.0f * (t_ticks / 65535.0f));
    this->_t = constrain(this->_t, -45.0f, 125.0f);
    this->_h = 100.0f * (rh_ticks / 65535.0f);
    this->_h = constrain(this->_h, 0, 100.f);

    return true;
}

float ArtronShop_HDC302x::temperature() {
    return this->_t;
}

float ArtronShop_HDC302x::humidity() {
    return this->_h;
}
