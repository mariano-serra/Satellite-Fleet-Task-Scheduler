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
    static int ipow(int base, int exp);
};

#ifdef DEBUG

// Extiendo la libreria ostream para para poder imprimir vectores
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
