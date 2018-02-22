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

Frame::~Frame(){
    //dtor
}
