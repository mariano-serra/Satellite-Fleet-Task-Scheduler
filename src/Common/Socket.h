/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SOCKET_H
#define SOCKET_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "SharedDeclarations.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/
#define BUFFER_SIZE         (5000)
#define SOCKET_TIMEOUT_S    (0)
#define SOCKET_TIMEOUT_uS   (100000)    // 0.1s


typedef char BufferData_t;

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/
class Socket
{
public:
    typedef enum SocketType
    {
        SERVER,
        CLIENT,
    }SocketType_t;

    /* Socket Data */
    int m_socket = 0;

    /* Metodos de recepcion y transmision */
    void sendData(BufferData_t* bufferData, size_t bufferSize);
    bool receiveData(BufferData_t* bufferData, size_t bufferSize);
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // SOCKET_H
