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
static const unsigned int nIncomingConnections = 5;

/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/


SocketServer::SocketServer(UniqueDeviceId_t server, ProcessReciveData_t processReciveData)
{
    /* Defino nombre de Server */
    char sat1ServerName[] = "SAT1_SERVER";
    char sat2ServerName[] = "SAT2_SERVER";
    char* serverName;
    if (server == SATELITE_1_ID)
    {
        serverName = sat1ServerName;
    }
    else
    {
        serverName = sat2ServerName;
    }

    /* Inicializacion de Socket */
    s = socket(AF_UNIX, SOCK_STREAM, 0);
    if ( -1 == s )
    {
        DEBUG_MSG("Error on socket() call" << std::endl);
        return;
    }

    local.sun_family = AF_UNIX;
    strcpy( local.sun_path, serverName );
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if ( bind(s, (struct sockaddr*)&local, len) != 0)
    {
        DEBUG_MSG("Error on binding socket" << std::endl);
        return;
    }

    if ( listen(s, nIncomingConnections) != 0 )
    {
        DEBUG_MSG("Error on listen call" << std::endl);
    }

    /* Handler de recepcion */
    m_processReciveData = processReciveData;

    /* Estado */
    m_state = WAITING_FOR_CLIENT;
    DEBUG_MSG("WAITING_FOR_CLIENT" << std::endl);
}

SocketServer::~SocketServer()
{
    close(s2);
}

void SocketServer::sendData(CommunicationsBuffer_t* data)
{

}

void SocketServer::runnerTask(void)
{
    switch (m_state)
    {
    case CONNECTED:

        /* TODO: Leer y escribir buffers de comunicacion */

        break;

    case WAITING_FOR_CLIENT:

        sock_len = 0;
        DEBUG_MSG("Waiting for connection...." << std::endl);
        if ( (s2 = accept(s, (struct sockaddr*)&remote, &sock_len)) == -1 )
        {
            DEBUG_MSG("Error on accept() call" << std::endl);
            return;
        }

        DEBUG_MSG("Server connected" << std::endl);
        m_state = CONNECTED;

        break;
    default:
        break;
    }
}

void SocketServer::processReciveData(CommunicationsBuffer_t* data)
{

}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/