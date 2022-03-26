/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "SharedDeclarations.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/
#define MAX_BUFFER_SIZE (80)

typedef void (*ProcessReciveData_t)(CommunicationsBuffer_t* data);

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/
class SocketServer
{
public:
    SocketServer(UniqueDeviceId_t server, ProcessReciveData_t processReciveData);
    ~SocketServer();

    void sendData(CommunicationsBuffer_t* data);
    
    void runnerTask(void);

private:
    /* Socket Data */
    int sockfd, newsockfd, servlen, n, buf, pid;
    unsigned int clilen;
    struct sockaddr_un  cli_addr, serv_addr;
    char buffer[MAX_BUFFER_SIZE];

    typedef enum State
    {
        WAITING_FOR_CLIENT,
        CONNECTED
    } State_t;
    State_t m_state;

    /*  */
    ProcessReciveData_t m_processReciveData;
    void processReciveData(CommunicationsBuffer_t* data);
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // SOCKET_SERVER_H
