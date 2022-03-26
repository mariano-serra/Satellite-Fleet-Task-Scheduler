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
    if ( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1  )
    {
        DEBUG_MSG("Client: Error on socket() call" << std::endl);
        return;
    }

    remote.sun_family = AF_UNIX;
    strcpy( remote.sun_path, serverName );
    data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

    DEBUG_MSG("Client: Trying to connect..." << std::endl);
    if ( connect(sock, (struct sockaddr*)&remote, data_len) == -1 )
    {
        DEBUG_MSG("Client: Error on connect call" << std::endl);
        return;
    }

    DEBUG_MSG("Client: Connected" << std::endl);

}

SocketClient::~SocketClient()
{

}

void SocketClient::sendData(CommunicationsBuffer_t* data)
{

}

void SocketClient::runnerTask(void)
{
    /* Vaciar buffer de transmision*/
    // n = write( newsockfd, "Obtuve su mensaje", 18 );

    // memset( buffer, '\0', MAX_BUFFER_SIZE );
    /* Leer y procesar buffer de recepcion */
    // n = read( sockfd, buffer, MAX_BUFFER_SIZE - 1 );
    // processReciveData()
}

void SocketClient::processReciveData(CommunicationsBuffer_t* data)
{

}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/