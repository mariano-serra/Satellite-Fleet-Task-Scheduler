/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "FrameLayer.h"
#include "SharedDeclarations.h"
#include "SocketServer.h"
#include "SocketClient.h"

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

FrameLayer::FrameLayer(ReceiveFrameTask_t receiveFrameTaskHandler, Socket::SocketType sockeType, UniqueDeviceId_t serverId)
{
    m_receiveFrameTaskHandler = receiveFrameTaskHandler;

    if (sockeType == Socket::SERVER)
    {
        m_socket = new SocketServer(serverId, processReciveData);
    }
    else if (sockeType == Socket::CLIENT)
    {
        m_socket = new SocketClient(serverId, processReciveData);
    }
}

FrameLayer::~FrameLayer()
{

}

void FrameLayer::sendFrameTask(FrameTask_t& taskFrame)
{
    auto const ptr = reinterpret_cast<BufferData_t*>(&taskFrame);
    CommunicationsBuffer_t data(ptr, ptr + sizeof(FrameTask_t));

    m_socket->sendData(data);
}

void FrameLayer::processReciveData(BufferData_t data)
{

}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/