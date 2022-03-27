/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "Socket.h"


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

Socket::Socket()
{
    memset(m_recv_buf, 0, BUFFER_SIZE * sizeof(BufferData_t));
    memset(m_send_buf, 0, BUFFER_SIZE * sizeof(BufferData_t));
}

void Socket::sendData(BufferData_t* bufferData, size_t bufferSize)
{
    /* Transimision */
    DEBUG_MSG("Socket::sendData() - size:" << bufferSize << std::endl);
    if (send(m_socket, bufferData, bufferSize*sizeof(BufferData_t), 0) == -1)
    {

    }
    DEBUG_MSG("Socket::sendData()" << std::endl);
}

void Socket::setChunkDataSize(size_t size)
{
    m_chunkSize = size;
}

void Socket::bufferDataProcces(void)
{
    /* Recepcion */
    int32_t data_recv = 0;
    memset(m_recv_buf, 0, BUFFER_SIZE * sizeof(BufferData_t));
    data_recv = recv(m_socket, m_recv_buf, m_chunkSize, 0);
    if (data_recv > 0)
    {
        if (m_processReciveData)
        {
            DEBUG_MSG("Socket::bufferDataProcces() - size:" << data_recv << std::endl);
            (*m_processReciveData)(m_recv_buf, data_recv);
            DEBUG_MSG("Socket::bufferDataProcces()" << std::endl);
        }
    }      
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/
