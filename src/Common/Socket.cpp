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

void Socket::sendData(CommunicationsBuffer_t& data)
{
    // TODO: Agregar guarda para que el vector de transmision no supere el tañano maximo */
    m_DataToSend.insert(m_DataToSend.end(), data.begin(), data.end());
}

void Socket::bufferDataProcces(void)
{
    /* Recepcion */
    int32_t data_recv = 0;
    memset(m_recv_buf, 0, BUFFER_SIZE * sizeof(BufferData_t));
    data_recv = recv(m_socket, m_recv_buf, BUFFER_SIZE, 0);
    for (int32_t i = 0; i < data_recv; ++i)
    {
        /* Proceso datos recibidos */
        if (m_processReciveData)
        {
            (*m_processReciveData)(m_recv_buf[i]);
        }
    }

    /* Transimision */
    std::copy(std::begin(m_DataToSend), std::end(m_DataToSend), m_send_buf);
    m_DataToSend.clear();
    if (strlen(m_send_buf))
    {
        if (send(m_socket, m_send_buf, strlen(m_send_buf)*sizeof(BufferData_t), 0) == -1)
        {
            DEBUG_MSG("Error on send() call" << std::endl);
        }
    }
}


/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/