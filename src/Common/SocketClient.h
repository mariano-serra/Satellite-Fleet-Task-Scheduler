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
#include "Socket.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/
class SocketClient : public Socket
{
public:
    SocketClient(UniqueDeviceId_t serverId, ProcessReciveData_t processReciveData);
    ~SocketClient();
    
    void runnerTask(void);

private:
    /* Socket Data */
    int m_socketClient = 0;
    int m_data_len = 0;
    struct sockaddr_un m_remote;
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // SOCKET_CLIENT_H