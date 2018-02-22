#include "DarkCountGenerator.h"

DarkCountGenerator::DarkCountGenerator(double winLength, unsigned int rate):
    windowLength{winLength}, darkCountRate{rate}
{
    lambda = windowLength * darkCountRate;
    distribution = std::poisson_distribution<unsigned short>(lambda);
}

void DarkCountGenerator::setWindowLength(double length){
    windowLength = length;
}

double DarkCountGenerator::getWindowLength() const{
    return windowLength;
};

void DarkCountGenerator::setDarkCountRate(unsigned int rate){
    darkCountRate = rate;
}

unsigned int DarkCountGenerator::getDarkCountRate(void) const{
    return darkCountRate;
}

unsigned short DarkCountGenerator::genRand(){
    return distribution(numberGenerator);
}

double DarkCountGenerator::getLambda() const {
    return lambda;
}


void DarkCountGenerator::generateDarkCount(Frame& frame){
    //iterate through all channels and call the random number generator.
    for(unsigned short r=0; r<frame.getRows(); r++){
        for(unsigned short c=0; c<frame.getColumns(); c++){
            frame.setEventsInChannel(r,c, distribution(numberGenerator));
        }
    }
};

DarkCountGenerator::~DarkCountGenerator()
{
    //dtor
}
