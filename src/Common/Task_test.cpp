/*!
 *  Unit test para <identificacion del modulo>
 */

/* ----------------------------------------------------------------------------- */
/* Includes */
/* ----------------------------------------------------------------------------- */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include "Task.h"

/* ----------------------------------------------------------------------------- */
/* Debug */
/* ----------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------- */
/* Defines, Estructuras y Typedef */
/* ----------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------- */
/* Variables externas y privadas */
/* ----------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------- */
/* Declaracion de funciones */
/* ----------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------- */
/* Implementacion de funciones */
/* ----------------------------------------------------------------------------- */

class Task_test  : public testing::Test
{
public:

    Task* m_task1;
    Task* m_task2;

    /* === TEST SETUP === */

    virtual void SetUp()
    {
        std::string task1Name = "task1";
        Resources::ResourcesList_t task1ResourcesList = {3,4,5};
        Task::Payoff_t task1Payoff = 1.0f;
        m_task1 = new Task(task1Name, task1ResourcesList, task1Payoff);

        std::string task2Name = "task2";
        Resources::ResourcesList_t task2ResourcesList = {1,5,5,7};
        float task2Payoff = 3.33f;
        m_task2 = new Task(task2Name, task2ResourcesList, task2Payoff);
    }

    virtual void TearDown()
    {
        delete(m_task1);
        delete(m_task2);
    }
};

/* === TEST CASES === */

TEST_F(Task_test, TaskInitTest)
{
    EXPECT_EQ(m_task1->getId(), 1);
    EXPECT_EQ(m_task1->getState(), Task::State_t::WAITING_TO_BE_EXECUTED);

    EXPECT_EQ(m_task2->getId(), 2);
    EXPECT_EQ(m_task2->getState(), Task::State_t::WAITING_TO_BE_EXECUTED);
}

TEST_F(Task_test, TaskSetStateTest)
{
    Task::State_t expectState = Task::State_t::IN_EXECUTION;
    m_task1->setState(expectState);
    EXPECT_EQ(m_task1->getState(), expectState);

    expectState = Task::State_t::EXECUTED;
    m_task2->setState(expectState);
    EXPECT_EQ(m_task2->getState(), expectState);
}

/* === FIN === */