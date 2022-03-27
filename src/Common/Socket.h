/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SOCKET_H
#define SOCKET_H

/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "SharedDeclarations.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos                                 */
/* ---------------------------------------------------------------------------*/
/** Timeout de operaciones de socket (canect, receive, send, etc.) */
#define SOCKET_TIMEOUT_S    (0)
#define SOCKET_TIMEOUT_uS   (100000)    /* 0.1s */

/** Buffer de transimision/recepcion  */
typedef char BufferData_t;

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas                               */
/*----------------------------------------------------------------------------*/
/**
 * @brief Clase Base para la construccion de socket
 * @details Contiene las funciones basicas para el envio y recepcion de datos.
 *
 */
class Socket
{
public:
    /** Tipo de socket */
    typedef enum SocketType
    {
        SERVER,
        CLIENT,
    } SocketType_t;

    /* Socket Vars */
    int m_socket = 0;

    /**
     * @brief Metodo para el envio de datos por socket
     * @details
     *
     * @param bufferData puntero a buffer de transmision
     * @param bufferSize tamaño del buffer de transmision
     */
    void sendData(BufferData_t* bufferData, size_t bufferSize);

    /**
     * @brief Metodo para la recepcion de datos por socket
     * @details
     *
     * @param bufferData puntero de buffer de recepcion
     * @param bufferSize tamaño de buffer decepcion / cantidad de datos recibir.
     *
     * @return [description]
     */
    bool receiveData(BufferData_t* bufferData, size_t bufferSize);
};

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // SOCKET_H
