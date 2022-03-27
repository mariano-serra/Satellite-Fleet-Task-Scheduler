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
    m_DataToSend.clear();
    memset(m_recv_buf, 0, BUFFER_SIZE * sizeof(BufferData_t));
    memset(m_send_buf, 0, BUFFER_SIZE * sizeof(BufferData_t));
}

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
    if (m_DataToSend.size())
    {
        memset(m_send_buf, 0, BUFFER_SIZE * sizeof(BufferData_t));
        for (int i = 0; i < m_DataToSend.size(); ++i)
        {
            m_send_buf[i] = m_DataToSend[i];
        }
        if (send(m_socket, m_send_buf, m_DataToSend.size()*sizeof(BufferData_t), 0) == -1)
        {
        }
        m_DataToSend.clear();
    }
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/
