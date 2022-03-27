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

AppConexionLayer::AppConexionLayer(Socket::SocketType sockeType, UniqueDeviceId_t serverId)
{
    m_frameLayer = new FrameLayer(sockeType, serverId);
}

AppConexionLayer::~AppConexionLayer()
{

}

void AppConexionLayer::sendTask(Task* task)
{
    FrameTask_t frameTask;
    Resources::ResourcesList_t resourcesList = task->getResourcesList();

    frameTask.taskId = task->getId();

    frameTask.payoff = task->getPayoff();

    frameTask.resourcesAmount = resourcesList.size();
    std::copy(resourcesList.begin(), resourcesList.end(), frameTask.resourcesList);

    frameTask.state = task->getState();

    m_frameLayer->sendFrameTask(&frameTask);
}

bool AppConexionLayer::receiveTask(Task* task)
{
    bool ret = false;
    FrameTask_t frameTask;

    ret = m_frameLayer->receiveFrameTask(&frameTask);

    if (ret)
    {
        Task::TaskId_t id = frameTask.taskId;
        std::string name = "task";  // No me importa, no lo recibo ni lo transmito

        Resources::ResourceAmount_t resourcesAmount = frameTask.resourcesAmount;
        Resources::ResourcesList_t resourcesList;
        std::copy(frameTask.resourcesList, frameTask.resourcesList + resourcesAmount, resourcesList.begin());
        
        Task::Payoff_t payoff = frameTask.payoff;

        task = new Task(id, name, resourcesList, payoff);
    }

    return ret;  
}



void AppConexionLayer::runnerTask(void)
{
    m_frameLayer->runnerTask();
}



/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/