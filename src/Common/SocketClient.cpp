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


SocketClient::SocketClient(UniqueDeviceId_t server, ProcessReciveData_t processReciveData)
{
    /* Defino nombre de Server */
    char sat1ServerName[] = "../../Satelite/main/SAT1_SERVER";
    char sat2ServerName[] = "../../Satelite/main/SAT2_SERVER";
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

    DEBUG_MSG("Client: Connected" << std::endl);

    /* Handler de recepcion */
    m_processReciveData = processReciveData;
}

SocketClient::~SocketClient()
{

}

void SocketClient::runnerTask(void)
{
    bufferDataProcces();
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/