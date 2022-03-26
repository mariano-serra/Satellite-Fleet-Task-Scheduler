/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "AppConexionLayer.h"
#include "SharedDeclarations.h"
#include <functional>
#include <string>

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

AppConexionLayer::AppConexionLayer(ReceiveTask_t receiveTaskHandler, Socket::SocketType sockeType, UniqueDeviceId_t serverId)
{
    m_receiveTaskHandler = receiveTaskHandler;
    m_frameLayer = new FrameLayer(receiveFrameTask, sockeType, serverId);
}

AppConexionLayer::~AppConexionLayer()
{

}

void AppConexionLayer::sendTask(Task& task)
{
    FrameTask_t frameTask;
    Resources::ResourcesList_t resourcesList = task.getResourcesList();

    frameTask.id = task.getId();
    frameTask.resourcesAmount = resourcesList.size();
    std::copy(resourcesList.begin(), resourcesList.end(), frameTask.resourcesList);
    frameTask.state = task.getState();

    m_frameLayer->sendFrameTask(frameTask);
}

void AppConexionLayer::receiveFrameTask(FrameTask_t& task)
{

}


/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/