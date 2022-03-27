/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include <unistd.h>
#include "SocketServer.h"
#include "Utilities.h"

/* ---------------------------------------------------------------------------*/
/* Debug                                                                      */
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef                                             */
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Declaracion de funciones                                                   */
/* ---------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------*/
/* Variables externas y privadas                                              */
/* ---------------------------------------------------------------------------*/
static const uint32_t nIncomingConnections = 5;

/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/


SocketServer::SocketServer(UniqueDeviceId_t serverId)
{
    /* Defino nombre de Server */
    char sat1ServerName[] = "SAT1_SERVER";
    char sat2ServerName[] = "SAT2_SERVER";
    char* serverName;
    if (serverId == SATELITE_1_ID)
    {
        serverName = sat1ServerName;
    }
    else
    {
        serverName = sat2ServerName;
    }

    /* Inicializacion de Socket */
    m_socketServer = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == m_socketServer)
    {
        DEBUG_MSG("Error on socket() call" << std::endl);
        return;
    }

    m_local.sun_family = AF_UNIX;
    strcpy( m_local.sun_path, serverName );
    unlink(m_local.sun_path);
    m_len = strlen(m_local.sun_path) + sizeof(m_local.sun_family);
    if (bind(m_socketServer, (struct sockaddr*)&m_local, m_len) != 0)
    {
        DEBUG_MSG("Error on binding socket" << std::endl);
        return;
    }

    if (listen(m_socketServer, nIncomingConnections) != 0)
    {
        DEBUG_MSG("Error on listen call" << std::endl);
    }

    /* Set Timeout */
    struct timeval tv;
    tv.tv_sec = SOCKET_TIMEOUT_S;
    tv.tv_usec = 0;
    setsockopt(m_socketServer, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    /* Estado */
    m_state = WAITING_FOR_CLIENT;
    DEBUG_MSG("WAITING_FOR_CLIENT" << std::endl);
}

SocketServer::~SocketServer()
{
    close(m_socket);
}

void SocketServer::runnerTask(void)
{
    switch (m_state)
    {
    case CONNECTED:

        /* Do Nothing */

        break;

    case WAITING_FOR_CLIENT:

        DEBUG_MSG("Waiting for connection...." << std::endl);
        m_sock_len = 0;
        m_socket = accept(m_socketServer, (struct sockaddr*)&m_remote, &m_sock_len);
        if ( m_socket == -1 )
        {
            DEBUG_MSG("Error on accept() call" << std::endl);
            return;
        }

        /* Set Timeout */
        struct timeval tv;
        tv.tv_sec = SOCKET_TIMEOUT_S;
        tv.tv_usec = 0;
        setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

        DEBUG_MSG("Server connected" << std::endl);
        m_state = CONNECTED;

        break;
    default:
        break;
    }
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/