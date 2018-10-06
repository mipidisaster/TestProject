/**************************************************************************************************
 * @file        GenBuffer.h
 * @author      Thomas
 * @version     V1.1
 * @date        06 Oct 2018
 * @brief       Header file for the Generic GenBuffer Class handle (template)
 **************************************************************************************************
 @ attention

 << To be Introduced >>

 *************************************************************************************************/
/**************************************************************************************************
 * How to use
 * ----------
 * Class will create a circular buffer (queue) to store data from sources to be read at a later
 * time.
 * Use of class
 *      Initial call can either be empty or be setup with the desired size of the buffer.
 *          If it is constructed without any parameters, then the default size of the buffer will
 *          be set to 32 entries deep
 *
 *      Then data can be added to the buffer via ".InputWrite".
 *      ***NOTE***
 *          If the input pointer of data catches up to the output pointer (therefore buffer is
 *          full), the write will force the output pointer to increment by 1, to ensure that the
 *          data within the buffer is limited to only be the defined length old.
 *
 *      Read data from buffer via ".OutputRead(<pointer>)", the read will only update the pointed
 *      data if there is new data within the buffer (i.e. not empty). If empty then it will not
 *      update pointer, and return the state "GenBuffer_Empty"
 *
 *      ".Flush" can be used to clear the entire contents of the buffer, and return all pointers
 *      back to the start of the buffer.
 *
 *      ".State" can be used to determine what the current state of the buffer is, returning a
 *      enumerate type of "_GenBufState" defined below.
 *
 *      ".ReadBuffer(<position>)" Return specified position within buffer.
 *
 *  This class has been defined within a template format (which is why the include at the end for
 *  the source file has been added - template call needs to include declaration and definition)
 *  So to use this class, it needs to be called like this:
 *      GenBuffer<--type--> testme(<option>);
 *
 *      --type-- can be changed for any type of variable uint8_t, uint16_t, etc. think this also
 *      include structures.
 *
 *  If "__LiteImplement__" has been defined, then the class will not use "use" or "delete" to
 *  minimise the size impact. However a fully defined array will need to be provided to the
 *  constructor call of this.
 *************************************************************************************************/
#ifndef GENBUFFER_H_
#define GENBUFFER_H_

#include "FileIndex.h"
#include <stdint.h>         // Include standard integer entries
#if ( defined(zz__MiSTM32Fx__zz) || defined(zz__MiSTM32Lx__zz)  )
// If the target device is either STM32Fxx or STM32Lxx from cubeMX then ...
//==================================================================================================
// None

#elif defined(zz__MiRaspbPi__zz)        // If the target device is an Raspberry Pi then
//==================================================================================================
// None

#else
//==================================================================================================
// None

#endif

// Defines specific within this class
typedef enum {
    GenBuffer_Empty = 0,        // Indicates that the buffer is empty of any new data
    GenBuffer_NewData = 1,      // Indicates that the buffer contains new data to be read
    GenBuffer_FULL = 2          // Indicates that the buffer is full, and no new data can be added
} _GenBufState;

// Types used within this class
// None

template <typename Typ>
class GenBuffer {
    // Declarations which are generic, and will be used in ALL devices
    public:
        uint32_t        input_pointer;      // Pointer to where the current input point is
        uint32_t        output_pointer;     // Pointer to where the current output point is

        uint32_t        length;             // Size of the buffer

        Typ             *pa;                // Points to the array (Buffer)

    public:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifdef __LiteImplement__        // If "__LiteImplement__" has been defined, then need to have array
                                // fully defined, and provided to the "GenBuffer"
                                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        GenBuffer(Typ *arrayloc, uint32_t size);
        // As have defined that the "GenBuffer" needs to be "Lite", then use of "new" and "delete"
        // is not required, therefore a fully defined array is to be provided, and used within
        // the class.
#else                           // If "__LiteImplement__" has not been defined, then allow use of
                                // "new" and "delete" for defining internal arrays
                                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        GenBuffer();                        // Constructor of the buffer class
        GenBuffer(uint32_t size);           // Overloaded Constructor of the buffer class, where
                                            // the size of the buffer is defined

        void SizeUpdate(uint32_t size);     // Update the size of the buffer
#endif                          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        void Flush(void);                   // Clear the data within the buffer
        void QFlush(void);                  // Clear buffer, by setting pointers to 0

        _GenBufState State(void);           // Function to determine state of buffer:
                                            // Full/NewData/Empty

        void InputWrite(Typ newdata);       // Add data onto the buffer (if at size of buffer, will
                                            // override oldest points (maintaining defined size)
        _GenBufState OutputRead(Typ *readdata); // Read next data entry in buffer (if data is
                                                // present)
        Typ ReadBuffer(uint32_t position);      // Read specific entry from buffer

        virtual ~GenBuffer();               // Destructor of class

// Device specific entries
// None
};

#include FilInd_GENBUF_Cp
// As this is a template format, cannot just include the declarations of the class, need to also
// provide the definitions of the functions for the compiler to work.

#endif /* GENBUFFER_GENBUFFER_H_ */