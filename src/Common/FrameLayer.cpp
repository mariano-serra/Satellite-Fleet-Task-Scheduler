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
    taskFrame.frameId = UnitqueTaskFrameId;

    BufferData_t* bufferData = reinterpret_cast<BufferData_t*>(&taskFrame);

    if (m_sockeType == Socket::SERVER)
    {
        m_socketServer->sendData(bufferData, sizeof(FrameTask_t));
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        m_socketClient->sendData(bufferData, sizeof(FrameTask_t));
    }
}

void FrameLayer::runnerTask(void)
{
    if (m_sockeType == Socket::SERVER)
    {
        m_socketServer->runnerTask();
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        m_socketClient->runnerTask();
    }
}

void FrameLayer::processReciveData(BufferData_t* bufferData, size_t bufferSize)
{
    FrameTask_t* taskFrame = reinterpret_cast<FrameTask_t*>(bufferData);

    DEBUG_MSG("FrameLayer::processReciveData() - frameId:");
    if (taskFrame->frameId == UnitqueTaskFrameId)
    {
        DEBUG_MSG("OK!" << std::endl);
        //if (this->m_receiveFrameTaskHandler)
        //{
        //    (*this->m_receiveFrameTaskHandler)((*taskFrame));
        //}
    }
    else
    {
        DEBUG_MSG("NOK!" << std::endl);
    }
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/