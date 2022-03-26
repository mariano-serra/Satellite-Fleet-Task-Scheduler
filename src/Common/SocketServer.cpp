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
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    /* Remover el nombre de archivo si existe */
    unlink(serverName);

    /* Bind */
    memset( &serv_addr, 0, sizeof(serv_addr) );
    serv_addr.sun_family = AF_UNIX;
    strcpy( serv_addr.sun_path, serverName);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

    bind(sockfd, (struct sockaddr *)&serv_addr, servlen);

    /* Listen */
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Handler de recepcion */
    m_processReciveData = processReciveData;

    /* Estado */
    m_state = WAITING_FOR_CLIENT;
    DEBUG_MSG("WAITING_FOR_CLIENT" << std::endl);
}

SocketServer::~SocketServer()
{
    close(newsockfd);
}

void SocketServer::sendData(CommunicationsBuffer_t* data)
{

}

void SocketServer::runnerTask(void)
{
    switch(m_state)
    {
    case CONNECTED:
        // memset( buffer, 0, MAX_BUFFER_SIZE );
        /* Leer y procesar buffer de recepcion */
        // n = read( newsockfd, buffer, MAX_BUFFER_SIZE - 1 );
        // processReciveData()

        /* Vaciar buffer de transmision*/
        // n = write( newsockfd, "Obtuve su mensaje", 18 );

        break;

    case WAITING_FOR_CLIENT:

        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);    
        pid = fork();

        if (pid == 0) 
        {
            close(sockfd);
        }
        else
        {
            DEBUG_MSG("CLIENT CONNECTED" << std::endl);

            close(newsockfd);
            m_state = CONNECTED;
            
            newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
            pid = fork();
            close(sockfd);
        }

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