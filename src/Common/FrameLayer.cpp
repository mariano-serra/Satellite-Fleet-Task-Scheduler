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

FrameLayer::FrameLayer(Socket::SocketType sockeType, UniqueDeviceId_t serverId)
{
    m_sockeType = sockeType;

    if (m_sockeType == Socket::SERVER)
    {
        m_socketServer = new SocketServer(serverId);
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        m_socketClient = new SocketClient(serverId);
    }
}

FrameLayer::~FrameLayer()
{

}

void FrameLayer::sendFrameTask(FrameTask_t* taskFrame)
{
    taskFrame->frameId = UnitqueTaskFrameId;

    BufferData_t* bufferData = reinterpret_cast<BufferData_t*>(taskFrame);

    if (m_sockeType == Socket::SERVER)
    {
        m_socketServer->sendData(bufferData, sizeof(FrameTask_t));
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        m_socketClient->sendData(bufferData, sizeof(FrameTask_t));
    }
}

bool FrameLayer::receiveFrameTask(FrameTask_t* taskFrame)
{
    bool ret;

    BufferData_t* bufferData = reinterpret_cast<BufferData_t*>(taskFrame);

    if (m_sockeType == Socket::SERVER)
    {
        ret = m_socketServer->receiveData(bufferData, sizeof(FrameTask_t));
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        ret = m_socketClient->receiveData(bufferData, sizeof(FrameTask_t));
    }

    if (ret)
    {   
        FrameId_t frameId = taskFrame->frameId;
        ret = (frameId == UnitqueTaskFrameId);
    }

    return ret;
}


void FrameLayer::runnerTask(void)
{
    if (m_sockeType == Socket::SERVER)
    {
        m_socketServer->runnerTask();
    }
}


/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/