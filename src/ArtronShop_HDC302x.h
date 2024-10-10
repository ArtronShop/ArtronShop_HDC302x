#ifndef __ARTRONSHOP_HDC302X_H__
#define __ARTRONSHOP_HDC302X_H__

#include <Arduino.h>
#include <Wire.h>

class ArtronShop_HDC302x {
    private:
        uint8_t _addr;
        TwoWire *_wire = NULL;
        float _t, _h;

    public:
        ArtronShop_HDC302x(TwoWire *wire = &Wire, uint8_t addr = 0x44) ;
        bool begin() ;
        bool measure() ;
        float temperature() ;
        float humidity() ;

};

#endif