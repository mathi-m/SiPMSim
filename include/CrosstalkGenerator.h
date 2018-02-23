#ifndef CROSSTALKGENERATOR_H
#define CROSSTALKGENERATOR_H

#include <random>
#include "Frame.h"
#include <iostream>

class CrosstalkGenerator
{
    public:
        CrosstalkGenerator():CrosstalkGenerator(0.0, 10){};

        /**
         * \brief Standard constructor with parameters for crosstalk generation.
         *
         * \param pct probability that an event generates an crosstalk.
         * \param maxIter
         */
        CrosstalkGenerator(double pct, unsigned char maxIter);

        /**
         * \brief Determine which events produce a crosstalk.
         *
         * To determine if an event produce a crosstalk generate a random number and compare to
         * crosstalk probability.
         *
         * \param frame The frame to process.
         */
        void generateCrosstalk(Frame& frame);

        //only for testing the random number generator.
        double genRand(void);

        virtual ~CrosstalkGenerator();

    private:
        double crosstalkProbability{0.0};
        unsigned char maxIter{10};
        std::default_random_engine numberGenerator;
        std::uniform_real_distribution<double> uniformDistribution{0.0,1.0};
};

#endif // CROSSTALKGENERATOR_H
