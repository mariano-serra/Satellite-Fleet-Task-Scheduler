/*!
 *  Unit test para <identificacion del modulo>
 */

/* ----------- ------------------------------------------------------------------ */
/* Includes */
/* ----------------------------------------------------------------------------- */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include "PermutationTaskSolver.h"

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

class PermutationTaskSolver_test  : public testing::Test
{
public:

    Resources* m_satelite1Resources;
    Resources* m_satelite2Resources;

    Task* m_task1;
    Task* m_task2;

    Task::TaskList_t m_taskList;


    /* === TEST SETUP === */

    virtual void SetUp()
    {
        m_satelite1Resources = new Resources(SATELITE_1_RES);
        m_satelite2Resources = new Resources(SATELITE_2_RES);

        std::string task1Name = "fotos";
        Resources::ResourcesList_t task1ResourcesList = {3, 5, 7};
        Task::Payoff_t task1Payoff = 10.0f;
        m_task1 = new Task(task1Name, task1ResourcesList, task1Payoff);
        m_taskList.push_back(m_task1);

        std::string task2Name = "cpu";
        Resources::ResourcesList_t task2ResourcesList = {1, 2};
        Task::Payoff_t task2Payoff = 2.5f;
        m_task2 = new Task(task2Name, task2ResourcesList, task2Payoff);
        m_taskList.push_back(m_task2);
    }

    virtual void TearDown()
    {
        delete(m_task1);
        delete(m_task2);
        delete(m_satelite1Resources);
        delete(m_satelite2Resources);
    }
};

/* === TEST CASES === */

TEST_F(PermutationTaskSolver_test, PermutationMatrixTest)
{
    PermutationTaskSolver::initPermutatioMatrix();
    PermutationTaskSolver::makeTaskPermutatioMatrix(m_taskList);

    EXPECT_EQ(PermutationTaskSolver::m_permutationVector.size(),9); // NUM_DEVICES_ID ^ (TasksNumber) = 3^(2) = 9;

    Task::Payoff_t maxPayoff = m_task1->getPayoff() + m_task2->getPayoff();

    /* Primera permutacion, ninguna tarea asignada a los satelites, por lo que el payoff = 0.0f */
    EXPECT_EQ(PermutationTaskSolver::m_assignTaskPayoffVector[0], 0.0);
    /* Ultima permutacion, ambas tares asignadas al satelite 2, por lo que el payoff el maximo = 12.5f */
    EXPECT_EQ(PermutationTaskSolver::m_assignTaskPayoffVector[8], 12.5);
    EXPECT_EQ(PermutationTaskSolver::m_assignTaskPayoffVector[8], maxPayoff);
}

TEST_F(PermutationTaskSolver_test, SortTaskPermutatioMatrixByPayoffTest)
{
    /* Lista de permutacion inicial */
    PermutationTaskSolver::PermutationVector_t expectList = {0,1,2,3,4,5,6,7,8};
    EXPECT_THAT(PermutationTaskSolver::m_permutationVector, expectList);

    PermutationTaskSolver::sortTaskPermutatioMatrixByPayoff();

    /* Lista de permutacion ordenadas manualmente de mayo a menor  
       payoff  = {12.5, 12.5, 12.5, 12.5, 10.0, 10.0, 2.5, 2.5, 0.0} */
    expectList = {4,    5,    7,    8,    1,    2,    3,   6,   0  };
    EXPECT_THAT(PermutationTaskSolver::m_permutationVector, expectList);
}

TEST_F(PermutationTaskSolver_test, ValidateTaskPermutatioMatrixTest)
{
    Task::TaskList_t unassignedTaskList;
    Task::TaskList_t satelite1TaskList;
    Task::TaskList_t satelite2TaskList;

    EXPECT_TRUE(PermutationTaskSolver::validateTaskPermutatioMatrix(*m_satelite1Resources, *m_satelite2Resources,
                                                                    unassignedTaskList, satelite1TaskList, satelite2TaskList));

    Task::TaskList_t expectedUnassignedTaskList = {};
    EXPECT_THAT(unassignedTaskList, expectedUnassignedTaskList);

    Task::TaskList_t expectedSatelite1TaskList = {m_task1, m_task2};
    EXPECT_THAT(satelite1TaskList, expectedSatelite1TaskList);

    Task::TaskList_t expectedSatelite2TaskList = {};
    EXPECT_THAT(satelite2TaskList, expectedSatelite2TaskList);
}

/* Agregar mas test!!! */

/* === FIN === */