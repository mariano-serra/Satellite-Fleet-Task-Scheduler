/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "Task.h"

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
Task::TaskId_t Task::idCount = 0;

/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/

Task::Task(Task::TaskId_t taskId, std::string name, Resources::ResourcesList_t resourcesList, Payoff_t payoff, State_t state)
{
    m_id = taskId;
    m_name = name;
    m_resourcesList = resourcesList;
    m_payoff = payoff;
    m_state = state;
}

Task::Task(std::string name, Resources::ResourcesList_t resourcesList, Payoff_t payoff)
{
    m_name = name;
    m_resourcesList = resourcesList;
    m_payoff = payoff;
    m_id = getNewId();
    m_state = WAITING_TO_BE_EXECUTED;
}

Task::~Task()
{

}

Task::TaskId_t Task::getNewId(void)
{
    /** Incrementa en uno el Id uniqo de tarea por cada vez que se llama al constructor de tarea */
    return ++idCount;
}

std::string Task::getName(void)
{
    return m_name;
}

Resources::ResourcesList_t Task::getResourcesList(void)
{
    return m_resourcesList;
}

Task::Payoff_t Task::getPayoff(void)
{
    return m_payoff;
}

Task::TaskId_t Task::getId(void)
{
    return m_id;
}

Task::State_t Task::getState(void)
{
    return m_state;
}

void Task::setState(Task::State_t state)
{
    m_state = state;
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/