/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include <unistd.h>
#include "SocketClient.h"
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


/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/


SocketClient::SocketClient(UniqueDeviceId_t serverId)
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
    if ((m_socketClient = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        DEBUG_MSG("Client: Error on socket() call" << std::endl);
        return;
    }

    m_remote.sun_family = AF_UNIX;
    strcpy( m_remote.sun_path, serverName );
    m_data_len = strlen(m_remote.sun_path) + sizeof(m_remote.sun_family);

    DEBUG_MSG("Client: Trying to connect..." << std::endl);
    if (connect(m_socketClient, (struct sockaddr*)&m_remote, m_data_len) == -1)
    {
        DEBUG_MSG("Client: Error on connect call" << std::endl);
        return;
    }

    /* Set Timeout */
    struct timeval tv;
    tv.tv_sec = SOCKET_TIMEOUT_S;
    tv.tv_usec = SOCKET_TIMEOUT_uS;
    setsockopt(m_socketClient, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    /* socket base */
    m_socket = m_socketClient;

    DEBUG_MSG("Client: Connected" << std::endl);
}

SocketClient::~SocketClient()
{

}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/