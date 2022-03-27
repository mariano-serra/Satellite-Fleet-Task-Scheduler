/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SOCKET_H
#define SOCKET_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "SharedDeclarations.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/
typedef void (*ProcessReciveData_t)(BufferData_t data);

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/
class Socket
{
public:
    typedef enum SocketType
    {
        SERVER,
        CLIENT,
    }SocketType_t;

    Socket();

    /* Socket Data */
    int m_socket = 0;

    /* Metodos de recepcion y */
    ProcessReciveData_t m_processReciveData;
    void sendData(CommunicationsBuffer_t& bufferData);

    /* Buffer de recepcion */
    BufferData_t m_recv_buf[2*BUFFER_SIZE];
    /* Buffers de transimision */
    BufferData_t m_send_buf[BUFFER_SIZE];
    CommunicationsBuffer_t m_DataToSend;

    /* runner */
    void bufferDataProcces(void);
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // SOCKET_H
