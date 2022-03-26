/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

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
class SocketClient
{
public:
    SocketClient(UniqueDeviceId_t server, ProcessReciveData_t processReciveData);
    ~SocketClient();

    void sendData(CommunicationsBuffer_t* data);
    
    void runnerTask(void);

private:
    /* Socket Data */
    int sockfd, servlen, n;
    struct sockaddr_un serv_addr;
    char buffer[MAX_BUFFER_SIZE];

    /*  */
    ProcessReciveData_t m_processReciveData;
    void processReciveData(CommunicationsBuffer_t* data);
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // SOCKET_CLIENT_H