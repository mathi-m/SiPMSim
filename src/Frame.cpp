#include "Frame.h"
#include <iostream>

Frame::Frame(unsigned short nrow, unsigned short ncol)
    :rows{nrow},columns{ncol},sensor(rows, std::vector<unsigned short>(columns)){
    //nothing else to do now...
}

//TODO: error handling.
unsigned short Frame::getEventsInChannel(unsigned short row, unsigned short col) const{
    return sensor.at(row).at(col);
}

//TODO: error handling.
void Frame::setEventsInChannel(unsigned short row, unsigned short col, unsigned short nbEvents){
    sensor.at(row).at(col) = nbEvents;
}

unsigned short Frame::getRows() const{
    return this->rows;
}

unsigned short Frame::getColumns() const{
    return this->columns;
}

bool Frame::hasEvents() const{
    //check all channels
    for(unsigned short r=0; r<rows; r++){
        for(unsigned short c=0; c<columns; c++){
            //an event is present, if value not 0
            if(sensor.at(r).at(c) != 0)
                return true;
        }
    }
    return false;
}

Frame::~Frame(){
    //dtor
}
