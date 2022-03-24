/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "Satelite.h"

/* ---------------------------------------------------------------------------*/
/* Debug                                                                      */
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef                                             */
/* ---------------------------------------------------------------------------*/

/* Porcenta Fake de falla en ejecucion de tarea */
static const uint16_t FailPercent = 10;

/* Tiempos maximos y minimos Fake en ejecucion de tarea */
static const uint16_t MinTaskTime = 5;
static const uint16_t MaxTaskTime = 100;

/* ---------------------------------------------------------------------------*/
/* Declaracion de funciones                                                   */
/* ---------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------*/
/* Variables externas y privadas                                              */
/* ---------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/

/*!
 * \\brief Constructor
 **/

Satelite::Satelite(UniqueDeviceId_t id, Resources::ResourcesList_t resourcesList)
{
    m_sateliteId = id;
    m_hardwareResources = new Resources(resourcesList);
    m_availableResources = new Resources(resourcesList);
}

Satelite::~Satelite()
{

}

Resources::ResourcesList_t Satelite::getAvailableResources(void)
{
    return m_availableResources->getResourcesList();
}

bool Satelite::addTaskToDo(Task* task)
{
    /* Verifica si la terea puede ser ejecutada con los recursos actuales */
    bool ret = m_availableResources->contains(task->getResourcesList());

    if (ret)
    {
        /* Asigna la tarea a la lista de pendientes */
        m_ongoingTasks[task] = FakeTaskTime();
        setTaskState(task, Task::IN_EXECUTION);

        /* Reserva los recursos necesarios */
        m_availableResources->substrac(task->getResourcesList());
    }

    return ret;
}

void Satelite::setTaskState(Task* task, Task::State_t state)
{
    task->setState(state);
    /* Enviar estado a estacion terrena */
    // TODO
}

void Satelite::runnerTask(void)
{

    for (TaskMap_t::iterator ongoingTask = m_ongoingTasks.begin(); ongoingTask != m_ongoingTasks.end(); ++ongoingTask)
    {

        Task* task = ongoingTask->first;
        TaskTime_t* time = &(ongoingTask->second);
        (*time) = (*time) - 1;

        if (*time < 0)
        {
            if (FakeTaskSuccess())
            {
                setTaskState(task, Task::EXECUTED);
            }
            else
            {
                setTaskState(task, Task::FAILURE_DURING_EXECUTION);   
            }

            /* Libera los recursos */
            m_availableResources->add(task->getResourcesList());

            /* Borra tarea a la lista de pendientes */
            /* FIXME: ver si la puede borrar dentro del iterador */
            m_ongoingTasks.erase(task);  //sino generar lista de tasks a borrar
        }
    }
}

bool Satelite::FakeTaskSuccess(void)
{
    bool success = (rand() % (100 / FailPercent)) != 0;

    return success;
}

Satelite::TaskTime_t Satelite::FakeTaskTime(void)
{
    TaskTime_t time = (rand() % (MaxTaskTime - MinTaskTime)) + MinTaskTime;

    return time;
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/