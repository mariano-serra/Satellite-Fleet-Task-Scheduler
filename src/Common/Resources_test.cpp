/*!
 *  Unit test para <identificacion del modulo>
 */

/* ----------------------------------------------------------------------------- */
/* Includes */
/* ----------------------------------------------------------------------------- */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include "Resources.h"

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

class Resources_test  : public testing::Test
{
public:

    Resources* m_resources;

    /* === TEST SETUP === */

    virtual void SetUp()
    {
        m_resources = new Resources({1,2,2,3,4,5,6,7,9});
    }

    virtual void TearDown()
    {
    }
};

/* === TEST CASES === */

TEST_F(Resources_test, ContainsTest)
{
    EXPECT_TRUE(m_resources->contains({1,2,3}));
    EXPECT_TRUE(m_resources->contains({1,2,2,9}));
    EXPECT_FALSE(m_resources->contains({8}));
    EXPECT_FALSE(m_resources->contains({1,8}));
    EXPECT_FALSE(m_resources->contains({1,2,2,2}));
}

TEST_F(Resources_test, SubstracTest)
{
    Resources::ResourcesList_t actualList = m_resources->getResourcesList();
    Resources::ResourcesList_t expectList = {1,2,2,3,4,5,6,7,9};
    EXPECT_THAT(actualList, expectList);

    m_resources->substrac({1,2,3});
    actualList = m_resources->getResourcesList();
    expectList = {2,4,5,6,7,9};
    EXPECT_THAT(actualList, expectList);

    m_resources->substrac({4,5,6,7,9});
    actualList = m_resources->getResourcesList();
    expectList = {2};
    EXPECT_THAT(actualList, expectList);
}

TEST_F(Resources_test, AddTest)
{
    Resources::ResourcesList_t actualList = m_resources->getResourcesList();
    Resources::ResourcesList_t expectList = {1,2,2,3,4,5,6,7,9};
    EXPECT_THAT(actualList, expectList);

    m_resources->add({1,2,3});
    actualList = m_resources->getResourcesList();
    expectList = {1,1,2,2,2,3,3,4,5,6,7,9};
    EXPECT_THAT(actualList, expectList);
}

TEST_F(Resources_test, AddAndSubstracTest)
{
    Resources::ResourcesList_t actualList = m_resources->getResourcesList();
    Resources::ResourcesList_t expectList = {1,2,2,3,4,5,6,7,9};
    EXPECT_THAT(actualList, expectList);

    m_resources->add({1,2,3});
    actualList = m_resources->getResourcesList();
    expectList = {1,1,2,2,2,3,3,4,5,6,7,9};
    EXPECT_THAT(actualList, expectList);

    m_resources->substrac({4,5,6,7,9});
    actualList = m_resources->getResourcesList();
    expectList = {1,1,2,2,2,3,3};
    EXPECT_THAT(actualList, expectList);
}

/* === FIN === */

