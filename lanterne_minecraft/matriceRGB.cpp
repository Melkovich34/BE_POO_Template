#include "matriceRGB.h"

matriceRGB::matriceRGB()
    : index(0), ledState(false) {}

void matriceRGB::begin() {
    Wire.begin();

    delay(1000);                                                        //Attend que matrice soit prête

    //Connexion I2C 
    matrix.scanGroveTwoRGBLedMatrixI2CAddress();                
    uint16_t VID = matrix.getDeviceVID();

    /*Test si connexion bien établis*/
    if (VID != 0x2886) {
        SERIAL.println("Can not detect led matrix!!!");
        while (1);
    }

    SERIAL.println("Matrix init success!!!");
    matrix.displayColorBlock(0x000000, 0, true);
}

void matriceRGB::start(uint32_t interval_ms) {
    timer.attach_ms(interval_ms, [this]() {                             
        this->changeColor();     
        //Serial.println("We are in the Matrix !");                                      
    });
}

void matriceRGB::stop() {
    timer.detach();                                                   
    matrix.stopDisplay();                                               
}

void matriceRGB::changeColor() {
    switch (index) {
        case 0:
            matrix.displayColorBlock(0xff0000, 0, true);
            break;
        case 1:
            matrix.displayColorBlock(0xffff00, 0, true);
            break;
        case 2:
            matrix.displayColorBlock(0x00ffff, 0, true);
            break;
        case 3:
            matrix.displayColorBlock(0x00fff0, 0, true);
            break;
        case 4:
            matrix.displayColorBlock(0x000fff, 0, true);
            break;
        case 5:
            matrix.displayColorBlock(0xff00ff, 0, true);
            break;
    }

    index++;
    if (index >= cpt_RGB)
        index = 0;
}
