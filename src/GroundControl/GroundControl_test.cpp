/*!
 *  Unit test para <identificacion del modulo>
 */

/* ----------------------------------------------------------------------------- */
/* Includes */
/* ----------------------------------------------------------------------------- */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include "GroundControl.h"

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


/* TODO: Debo sobrecargar los metodos Fake para poder mockeralos */

class GroundControl_test  : public testing::Test
{
public:

    GroundControl* m_groundControl;
    Task* m_task1;
    Task* m_task2;
    Task* m_task3;
    Task* m_task4;
    
    PermutationTaskSolver::TaskList_t m_taskList;

    /* === TEST SETUP === */

    virtual void SetUp()
    {
        UniqueDeviceId_t id = GROUND_CONTROL_ID;
        m_groundControl = new GroundControl(id);

        std::string task1Name = "task1";
        Resources::ResourcesList_t task1ResourcesList = {3,5,7};
        float task1Payoff = 10.0f;
        m_task1 = new Task(task1Name, task1ResourcesList, task1Payoff);
        m_taskList.push_back(m_task1);

        std::string task2Name = "task2";
        Resources::ResourcesList_t task2ResourcesList = {1,2};
        float task2Payoff = 2.5f;
        m_task2 = new Task(task2Name, task2ResourcesList, task2Payoff);
        m_taskList.push_back(m_task2);

        std::string task3Name = "task3";
        Resources::ResourcesList_t task3ResourcesList = {4,7,10};
        float task3Payoff = 2.5f;
        m_task3 = new Task(task3Name, task3ResourcesList, task3Payoff);
        m_taskList.push_back(m_task3);

        std::string task4Name = "task4";
        Resources::ResourcesList_t task4ResourcesList = {2,6,8};
        float task4Payoff = 5.0f;
        m_task4 = new Task(task4Name, task4ResourcesList, task4Payoff);
        m_taskList.push_back(m_task4);
    }

    virtual void TearDown()
    {
        delete(m_groundControl);
    }
};

/* === TEST CASES === */

TEST_F(GroundControl_test, AvailableResourcesTest)
{
    m_groundControl->addListTaskToDo(m_taskList);
    EXPECT_TRUE(false);
}


/* === FIN === */

