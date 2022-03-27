/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "Socket.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos                                 */
/* ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas                               */
/*----------------------------------------------------------------------------*/

/**
 * @brief Abstraccion para la contruccion de cliente
 * @details
 *
 */
class SocketClient : public Socket
{
public:
    /**
     * @brief Constructor
     * @details [long description]
     *
     * @param serverId Identificador unico para la conexion con servidor
     */
    SocketClient(UniqueDeviceId_t serverId);

    /**
     * @brief Destructor
     * @details
     */
    ~SocketClient();

private:
    /* Socket Vars */
    int m_socketClient = 0;
    int m_data_len = 0;
    struct sockaddr_un m_remote;
};

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // SOCKET_CLIENT_H