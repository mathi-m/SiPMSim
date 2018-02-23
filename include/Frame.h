#ifndef FRAME_H
#define FRAME_H

//needed for creating the base two-dimensional array.
#include <vector>

/**
 * \brief Realisation of the SiPM's activity in a time interval ti.
 *
 * The class Frame represents the activity in a time interval ti.
 * The configuration of the SiPM is represented by a two dimensional array with the dimensions of the SiPM (n x m channels).
 * Contents of the array is the response of a channel in p.e. (photon equivalents), thus reflecting the discrete behaviour of the SiPM.
 *
 */
class Frame
{
    public:
        /**
         * \brief The constructor for a Frame object.
         *
         * The only constructor for a Frame object expects the size of the SiPM as parameters.
         * After construction of the frame it is not possible (and meaningful) to change the size of the SiPM.
         * A SiPM has Frame::rows * Frame::columns -channels.
         *
         * \param nrow specifies the number of rows of the SiPM.
         * \param ncol specifies the number of columns of the SiPM.
         */
        Frame(unsigned short nrow, unsigned short ncol);

        /**
         * \brief Query number of rows.
         */
        unsigned short getRows(void) const;
        /**
         * \brief Query number of columns.
         */
        unsigned short getColumns(void) const;

        /**
         * \brief Read the number of events in channel.
         *
         * \param row row index
         * \param col column index
         * \return number of events in channel
         */
        unsigned short getEventsInChannel(unsigned short row, unsigned short col) const;

        /**
         * \brief Sets the number of events in channel.
         *
         * \param row row index
         * \param col column index
         * \param number of events in channel
         */
        void setEventsInChannel(unsigned short row, unsigned short col, unsigned short nbEvents);

        /**
         * \brief Determine if the Frame contains events.
         *
         * \return true if events are present, false otherwise (all channels = 0).
         */
        bool hasEvents(void) const;

        /**
         * \brief Standard Destructor.
         */
        virtual ~Frame();

    protected:

    private:
        const unsigned short rows;      /**< Number of rows. Sensor size is rows * Frame::columns -channels.*/
        const unsigned short columns;   /**< Number of columns. Sensor size is Frame::rows * columns-channels.*/
        std::vector<std::vector<unsigned short>> sensor;    /**< Internal vector of vectors (Frame::rows * Frame::columns -channels) of unsigned short that represent the sensor.*/
};

#endif // FRAME_H
