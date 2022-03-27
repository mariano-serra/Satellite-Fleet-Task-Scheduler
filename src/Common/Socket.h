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
#define BUFFER_SIZE (5000)
#define SOCKET_TIMEOUT_S (1)

typedef char BufferData_t;
typedef void (*ProcessReciveData_t)(BufferData_t* bufferData, size_t bufferSize);

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
    void sendData(BufferData_t* bufferData, size_t bufferSize);

    /* Buffer de recepcion */
    BufferData_t m_recv_buf[BUFFER_SIZE];
    /* Buffers de transimision */
    BufferData_t m_send_buf[BUFFER_SIZE];

    /* Data Receive config*/
    size_t m_chunkSize;
    void setChunkDataSize(size_t size);

    /* runner */
    void bufferDataProcces(void);
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // SOCKET_H
