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
static const FrameId_t UnitqueTaskFrameId = 0x14F6FE0C; /* Hash */

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
    m_sockeType = sockeType;

    if (m_sockeType == Socket::SERVER)
    {
        m_socketServer = new SocketServer(serverId, processReciveData);
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        m_socketClient = new SocketClient(serverId, processReciveData);
    }
}

FrameLayer::~FrameLayer()
{

}

void FrameLayer::sendFrameTask(FrameTask_t& taskFrame)
{
    DEBUG_MSG("FrameLayer::sendFrameTask()" << std::endl);
    taskFrame.frameId = UnitqueTaskFrameId;

    auto const ptr = reinterpret_cast<BufferData_t*>(&taskFrame);
    CommunicationsBuffer_t data(ptr, ptr + sizeof(FrameTask_t));

    if (m_sockeType == Socket::SERVER)
    {
        DEBUG_MSG("m_socketServer->sendData()" << std::endl);
        m_socketServer->sendData(data);
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        DEBUG_MSG("m_socketClient->sendData()" << std::endl);
        m_socketClient->sendData(data);
    }
}

void FrameLayer::runnerTask(void)
{
    DEBUG_MSG("FrameLayer::runnerTask()" << std::endl);
    if (m_sockeType == Socket::SERVER)
    {
        DEBUG_MSG("m_socketServer->runnerTask()" << std::endl);
        m_socketServer->runnerTask();
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        DEBUG_MSG("m_socketClient->runnerTask()" << std::endl);
        m_socketClient->runnerTask();
    }
}

void FrameLayer::processReciveData(BufferData_t data)
{
    
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/