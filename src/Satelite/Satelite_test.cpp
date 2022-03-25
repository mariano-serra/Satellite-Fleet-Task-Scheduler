/*!
 *  Unit test para <identificacion del modulo>
 */

/* ----------------------------------------------------------------------------- */
/* Includes */
/* ----------------------------------------------------------------------------- */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include "Satelite.h"

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


class Satelite_Mock : public Satelite
{
public:
    using Satelite::Satelite;

    MOCK_METHOD0(FakeTaskSuccess, bool());
    MOCK_METHOD0(FakeTaskTime, Satelite::TaskTime_t());
};


class Satelite_test  : public testing::Test
{
public:

    Satelite_Mock* m_satelite;
    Task* m_task1;
    Task* m_task2;

    /* === TEST SETUP === */

    virtual void SetUp()
    {
        UniqueDeviceId_t sateliteId = SATELITE_1_ID;
        Resources::ResourcesList_t sateliteResourcesList = {1, 2, 3, 5, 5, 7};
        m_satelite = new Satelite_Mock(sateliteId, sateliteResourcesList);

        std::string task1Name = "fotos";
        Resources::ResourcesList_t task1ResourcesList = {3, 5, 5, 7};
        float task1Payoff = 10.0f;
        m_task1 = new Task(task1Name, task1ResourcesList, task1Payoff);

        std::string task2Name = "cpu";
        Resources::ResourcesList_t task2ResourcesList = {1, 2};
        float task2Payoff = 2.5f;
        m_task2 = new Task(task2Name, task2ResourcesList, task2Payoff);
    }

    virtual void TearDown()
    {
        delete(m_satelite);
    }
};

/* === TEST CASES === */

TEST_F(Satelite_test, AvailableResourcesTest)
{
    Resources::ResourcesList_t actualList = m_satelite->getAvailableResources();
    Resources::ResourcesList_t expectList = {1, 2, 3, 5, 5, 7};
    EXPECT_THAT(actualList, expectList);
}

TEST_F(Satelite_test, AddTask1ToDoTest_FAIL)
{
    Resources::ResourcesList_t actualList = m_satelite->getAvailableResources();
    Resources::ResourcesList_t expectList = {1, 2, 3, 5, 5, 7};
    EXPECT_THAT(actualList, expectList);

    EXPECT_EQ(m_task1->getState(), Task::State_t::WAITING_TO_BE_EXECUTED);

    EXPECT_CALL(*m_satelite, FakeTaskTime()).WillOnce(Return(3));

    EXPECT_TRUE(m_satelite->addTaskToDo(m_task1));
    actualList = m_satelite->getAvailableResources();
    expectList = {1, 2};
    EXPECT_THAT(actualList, expectList);

    EXPECT_EQ(m_task1->getState(), Task::State_t::IN_EXECUTION);

    for (int i = 0; i < 3; ++i)
    {
        m_satelite->runnerTask();
        actualList = m_satelite->getAvailableResources();
        expectList = {1, 2};
        EXPECT_THAT(actualList, expectList);

        EXPECT_EQ(m_task1->getState(), Task::State_t::IN_EXECUTION);
    }

    EXPECT_CALL(*m_satelite, FakeTaskSuccess()).WillOnce(Return(false));

    m_satelite->runnerTask();
    actualList = m_satelite->getAvailableResources();
    expectList = {1, 2, 3, 5, 5, 7};
    EXPECT_THAT(actualList, expectList);

    EXPECT_EQ(m_task1->getState(), Task::State_t::FAILURE_DURING_EXECUTION);
}

TEST_F(Satelite_test, AddTask2ToDoTest_SUCCESS)
{
    Resources::ResourcesList_t actualList = m_satelite->getAvailableResources();
    Resources::ResourcesList_t expectList = {1, 2, 3, 5, 5, 7};
    EXPECT_THAT(actualList, expectList);

    EXPECT_EQ(m_task2->getState(), Task::State_t::WAITING_TO_BE_EXECUTED);

    EXPECT_CALL(*m_satelite, FakeTaskTime()).WillOnce(Return(5));   // Time

    EXPECT_TRUE(m_satelite->addTaskToDo(m_task2));
    actualList = m_satelite->getAvailableResources();
    expectList = {3, 5, 5, 7};
    EXPECT_THAT(actualList, expectList);

    EXPECT_EQ(m_task2->getState(), Task::State_t::IN_EXECUTION);

    for (int i = 0; i < 5; ++i)
    {
        m_satelite->runnerTask();
        actualList = m_satelite->getAvailableResources();
        expectList = {3, 5, 5, 7};
        EXPECT_THAT(actualList, expectList);

        EXPECT_EQ(m_task2->getState(), Task::State_t::IN_EXECUTION);
    }

    EXPECT_CALL(*m_satelite, FakeTaskSuccess()).WillOnce(Return(true));

    m_satelite->runnerTask();
    actualList = m_satelite->getAvailableResources();
    expectList = {1, 2, 3, 5, 5, 7};
    EXPECT_THAT(actualList, expectList);

    EXPECT_EQ(m_task2->getState(), Task::State_t::EXECUTED);
}

TEST_F(Satelite_test, AddTask1And2ToDoTest)
{
    Resources::ResourcesList_t actualList = m_satelite->getAvailableResources();
    Resources::ResourcesList_t expectList = {1, 2, 3, 5, 5, 7};
    EXPECT_THAT(actualList, expectList);

    EXPECT_EQ(m_task1->getState(), Task::State_t::WAITING_TO_BE_EXECUTED);

    EXPECT_CALL(*m_satelite, FakeTaskTime()).Times(2).WillOnce(Return(3))
                                            .WillOnce(Return(5));

    EXPECT_CALL(*m_satelite, FakeTaskSuccess()).Times(2).WillOnce(Return(false))
                                                        .WillOnce(Return(true));

    EXPECT_TRUE(m_satelite->addTaskToDo(m_task1));
    EXPECT_TRUE(m_satelite->addTaskToDo(m_task2));
    actualList = m_satelite->getAvailableResources();
    expectList = {};
    EXPECT_THAT(actualList, expectList);

    EXPECT_EQ(m_task1->getState(), Task::State_t::IN_EXECUTION);

    for (int i = 0; i < 5; ++i)
    {
        m_satelite->runnerTask();
    }

    m_satelite->runnerTask();
    actualList = m_satelite->getAvailableResources();
    expectList = {1, 2, 3, 5, 5, 7};
    EXPECT_THAT(actualList, expectList);

    EXPECT_EQ(m_task1->getState(), Task::State_t::FAILURE_DURING_EXECUTION);
    EXPECT_EQ(m_task2->getState(), Task::State_t::EXECUTED);
}

/* === FIN === */

