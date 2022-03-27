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
    DEBUG_MSG("sendTask()");
    FrameTask_t frameTask;
    Resources::ResourcesList_t resourcesList = task->getResourcesList();

    frameTask.taskId = task->getId();

    frameTask.payoff = task->getPayoff();

    frameTask.resourcesAmount = resourcesList.size();
    std::copy(resourcesList.begin(), resourcesList.end(), frameTask.resourcesList);

    frameTask.state = task->getState();

    m_frameLayer->sendFrameTask(&frameTask);
    DEBUG_MSG("sendTask()");
}

bool AppConexionLayer::receiveTask(Task** task)
{
    bool ret = false;
    FrameTask_t frameTask;

    DEBUG_MSG("receiveTask()");
    ret = m_frameLayer->receiveFrameTask(&frameTask);
    if (ret)
    {
        Task::TaskId_t id = frameTask.taskId;
        std::string name = "X";  // No me importa, no lo recibo ni lo transmito

        Task::Payoff_t payoff = frameTask.payoff;

        Resources::ResourceAmount_t resourcesAmount = frameTask.resourcesAmount;
        Resources::ResourcesList_t resourcesList;
        for (int i = 0; i < resourcesAmount; ++i)
        {
            resourcesList.push_back(frameTask.resourcesList[i]);
        }        

        Task::State_t state = frameTask.state;

        DEBUG_MSG("new Task()");
        (*task) = new Task(id, name, resourcesList, payoff, state);
    }
    DEBUG_MSG("receiveTask()");

    return ret;  
}



void AppConexionLayer::runnerTask(void)
{
    m_frameLayer->runnerTask();
}



/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/