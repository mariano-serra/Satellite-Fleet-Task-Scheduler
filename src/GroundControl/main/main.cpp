/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <sstream>
#include "GroundControl.h"
#include "SocketClient.h"

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

int main(int argc, char **argv)
{
    std::cout << "Start Ground Control" << std::endl;

    GroundControl *groundControl = new GroundControl(GROUND_CONTROL_ID);

    /* Create Meassege Broker (Observer Pattern!) */
    SocketClient* clientSatelite1 = new SocketClient(SATELITE_1_ID, NULL);
    SocketClient* clientSatelite2 = new SocketClient(SATELITE_2_ID, NULL);

    /* SCHEDULER */
    while(true)
    {
        /* Socket Runner */
        clientSatelite1->runnerTask();
        clientSatelite2->runnerTask();

        /* Task  Runner */
        groundControl->runnerTask();

        // TODO: Add MessageBroker.runnerTask();
    }

    return 0;
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/
