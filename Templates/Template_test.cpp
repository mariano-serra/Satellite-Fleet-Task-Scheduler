/*!
 *  Unit test para <identificacion del modulo>
 */

/* ----------------------------------------------------------------------------- */
/* Includes */
/* ----------------------------------------------------------------------------- */

#include <gtest/gtest.h>

using namespace testing;

#include "Template.h"

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

class Template_test  : public testing::Test
{
public:

    /* === TEST SETUP === */

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
        mocko.destroy();
    }
};

/* === TEST CASES === */

TEST_F(Template_test, tc_name)
{
}

/* === FIN === */