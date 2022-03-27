/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

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
 * @brief Abstraccion para la contruccion de server
 * @details
 *
 */
class SocketServer : public Socket
{
public:
    /**
     * @brief Contructor
     * @details
     *
     * @param serverId Identificador unico para construccion de servidor
     */
    SocketServer(UniqueDeviceId_t serverId);

    /**
     * @brief Destructor
     * @details
     */
    ~SocketServer();

private:

    /* Socket Vars */
    int m_socketServer = 0;
    struct sockaddr_un m_local, m_remote;
    int m_len = 0;
    unsigned int m_sock_len = 0;
};

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // SOCKET_SERVER_H
