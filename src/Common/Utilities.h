/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef UTILITIESL_H
#define UTILITIESL_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include "Types.h"
#include <string>
#include <vector>

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/

// TODO: hacer Template
class Utilities
{
public:
    /**
     * @brief Calculo de potencia entera (base^(exp))
     * @details
     * 
     * @param base Base
     * @param exp Exponente
     * 
     * @return Resultado de base^(exp).
     */
    static int ipow(int base, int exp);
};

/** Solamente si DEBUG esta definido. */
#ifdef DEBUG

    /**
     *  Extiendo el operador '<<' para poder imprimir por el std::cout el contenido de un vector
     *  de un tipo <T> determinado.
     *  
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& output, std::vector<T> const& values)
    {
        output << "{";
        for (auto const& value : values)
        {
            output << value << ",";
        }
        output << "}";
        return output;
    }

#endif

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // UTILITIESL_H
