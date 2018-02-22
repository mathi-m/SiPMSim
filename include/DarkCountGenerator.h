#ifndef DARKCOUNTGENERATOR_H
#define DARKCOUNTGENERATOR_H

#include <random>
#include "Frame.h"


class DarkCountGenerator
{
    public:
        /**
         * \brief Default constructor.
         */
        DarkCountGenerator():DarkCountGenerator(2e-9, 0){};

        /**
         * \brief Standard constructor with parameters.
         *
         * \param winLength The length of the time interval of the simulation.
         * \param rate The dark count rate of the SiPM.
         */
        DarkCountGenerator(double winLength, unsigned int rate);

        /**
         * \brief Set the window length to be used by the generator.
         *
         * \param windowLength in seconds.
         */
        void setWindowLength(double length);

        /**
         * \brief Query window length used by the generator.
         *
         * \return DarkCountGenerator::windowLength
         */
        double getWindowLength(void) const;

         /**
         * \brief Set the dark count rate to use by the generator.
         *
         * \param dark count rate [events per second].
         */
        void setDarkCountRate(unsigned int rate);

        /**
         * \brief Query dark count rate used by the generator.
         *
         * \return DarkCountGenerator::darkCountRate
         */
        unsigned int getDarkCountRate(void) const;

        /**
         * \brief Query the parameter of the Poisson distribution.
         */
        double getLambda(void) const;


        /**
         * \brief Generates dark count in the frame.
         *
         * \param frame A reference to the frame in which the dark count should be generated.
         */
        void generateDarkCount(Frame& frame);


        //only for testing the random number generator.
        unsigned short genRand(void);

        virtual ~DarkCountGenerator();

    protected:

    private:
        double windowLength{2e-9}; /**< Length of the time interval. */
        unsigned int darkCountRate{0}; /**< Dark count rate used by the generator. */
        double lambda; /**< Lambda of the Poisson distribution. */
        std::default_random_engine numberGenerator; /**< Random number generator. */
        std::poisson_distribution<unsigned short> distribution; /**< Transform rand values to Poisson distribution. */
};

#endif // DARKCOUNTGENERATOR_H
