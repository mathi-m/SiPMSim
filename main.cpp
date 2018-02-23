#include <iostream>
#include "Frame.h"
#include "DarkCountGenerator.h"
#include "CrosstalkGenerator.h"

#include <array>
#include <random>
#include <fstream>

//test functions
void printFrame(Frame&);

//test rnd generation
void testRndGen(DarkCountGenerator&);
void testRndGen(void);

int main()
{
    //some preliminary test code.
    Frame aTestFrame{4, 4}; //a new frame of 16x16 channels (256 channels)
    Frame ctTester(4, 4);
    ctTester.setEventsInChannel(1,2,8);
    ctTester.setEventsInChannel(0,0,1);
    ctTester.setEventsInChannel(2,3,4);
    ctTester.setEventsInChannel(3,1,2);
    DarkCountGenerator aTestDarkCountGenerator(2e-9, 500000); //initialize DCR generator
    CrosstalkGenerator aCrosstalkGenerator{0.1, 20};
    std::cout << "A Frame of size "; //check frame size
    std::cout << aTestFrame.getRows() << " rows, " <<
    aTestFrame.getColumns() << " columns" << std::endl;
    std::cout << "Events: " << aTestFrame.hasEvents() << std::endl;
    std::cout << std::endl;
    testRndGen(aTestDarkCountGenerator); //test generator
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Test CT:" << std::endl;
    printFrame(ctTester);
    std::cout << std::endl;
    aCrosstalkGenerator.generateCrosstalk(ctTester);
    std::cout << std::endl;
    printFrame(ctTester);
    std::cout << std::endl;

    //doing a test run and write to file
    std::ofstream outputFile("TestDCR_500000.csv");
    int runs = 1000;
    for(int i=0; i < runs; i++){
        //generate some dark count
        aTestDarkCountGenerator.generateDarkCount(aTestFrame);
        aCrosstalkGenerator.generateCrosstalk(aTestFrame);
        if(aTestFrame.hasEvents()){
            printFrame(aTestFrame);
            std::cout << std::endl;
        }
        //simple csv-output
        for(unsigned short r=0; r<aTestFrame.getRows(); r++){
            for(unsigned short c=0; c<aTestFrame.getColumns(); c++){
                if(r==0 && c==0){
                    outputFile << aTestFrame.getEventsInChannel(r,c);
                }else{
                     outputFile << ',' << aTestFrame.getEventsInChannel(r,c);
                }
            }
        }
        outputFile << '\n';
    }
    outputFile.close();

    return 0;
}

/*
 * Prints the contents of the frame to command line.
 */
void printFrame(Frame& sensor){
    for(unsigned short r=0; r<sensor.getRows(); r++){
        for(unsigned short c=0; c<sensor.getColumns(); c++){
            //std::cout << "element at " << r << "," << c << " : " << sensor.getEventsInChannel(r,c) << std::endl;
            std::cout << sensor.getEventsInChannel(r,c) << '\t';
        }
        std::cout << std::endl;
    }
}


//for testing of random number generation.
void testRndGen(DarkCountGenerator& gen){
  const int nrolls = 10000; // number of experiments
  const int nstars = 100;   // maximum number of stars to distribute

  Frame tempFrame(2,2);
  int p[10]={};

  for (int i=0; i<nrolls/4; ++i) {
    gen.generateDarkCount(tempFrame);

    for(unsigned short r=0; r<tempFrame.getRows(); r++){
        for(unsigned short c=0; c<tempFrame.getColumns(); c++){
            unsigned short number = tempFrame.getEventsInChannel(r,c);
            if (number<10) ++p[number];
        }
    }
  }

  std::cout << "poisson_distribution from own class (mean=" << gen.getLambda() << "):" << std::endl;
  for (int i=0; i<10; ++i){
    std::cout << i << ": " << std::string(p[i]*nstars/nrolls,'*') << '\t' << p[i] << std::endl;
  }
}

//was used to compare random number implementations.
void testRndGen(){
  const int nrolls = 10000; // number of experiments
  const int nstars = 100;   // maximum number of stars to distribute

  std::default_random_engine generator;
  std::poisson_distribution<int> distribution(4.1);

  int p[10]={};

  for (int i=0; i<nrolls; ++i) {
    int number = distribution(generator);
    if (number<10) ++p[number];
  }

  std::cout << "poisson_distribution from example (mean=4.1):" << std::endl;
  for (int i=0; i<10; ++i){
    std::cout << i << ": " << std::string(p[i]*nstars/nrolls,'*') << '\t' << p[i] << std::endl;
  }
}
