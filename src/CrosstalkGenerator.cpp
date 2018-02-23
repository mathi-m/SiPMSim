#include "CrosstalkGenerator.h"

CrosstalkGenerator::CrosstalkGenerator(double pct, unsigned char maxIter):
    crosstalkProbability{pct}, maxIter{maxIter}
{
    //ctor
}

void CrosstalkGenerator::generateCrosstalk(Frame& frame){

    // At first the frame has to be checked if events are present.
    // Otherwise nothing has to be done.
    if(frame.hasEvents()){
        Frame tempFrame{frame}; //a copy of the frame for processing.
        int iterCnt; //the counter is a safety feature to stop a free running loop (e.g. because crosstalk probability is to high)
        //now process all channels
        for(int r=0; r<tempFrame.getRows(); r++){
            for(int c=0; c<tempFrame.getColumns(); c++){
                iterCnt = maxIter; //set iterCnt
                //now process events until channel is empty or iteration limit is reached
                while(tempFrame.getEventsInChannel(r,c)>0 && (iterCnt > 0)){
                    bool genCt = (uniformDistribution(numberGenerator) < crosstalkProbability); //generate a crosstalk?
                    //add result of crosstalk generation
                    tempFrame.setEventsInChannel(r,c, tempFrame.getEventsInChannel(r,c)+ genCt); //conversion of bool to int is implicit and defined by language reference
                    //decrement to indicate that an event was processed
                    tempFrame.setEventsInChannel(r,c, tempFrame.getEventsInChannel(r,c)-1);
                    //add result of crosstalk generation
                    frame.setEventsInChannel(r,c, frame.getEventsInChannel(r,c)+ genCt);
                    iterCnt--;// now decrement the iteration counter
                }
                if(iterCnt == 0){
                    //something went wrong. So the user has to be informed about it.
                    std::cout << "iterCnt reached 0!" << std::endl;
                }
            }
        }
    }
}


double CrosstalkGenerator::genRand(){
    return uniformDistribution(numberGenerator);
}


CrosstalkGenerator::~CrosstalkGenerator()
{
    //dtor
}
