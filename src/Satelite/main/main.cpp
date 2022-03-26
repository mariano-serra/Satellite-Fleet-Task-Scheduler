/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include <string>
#include <sstream>
#include "Satelite.h"
#include "SocketServer.h"

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
/* Argumentos de entrada */
static std::vector<std::string> arguments;

/* SATELITE */
static UniqueDeviceId_t sateliteId;
static Resources::ResourcesList_t sateliteResourcesList;

/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
    bool validArgument = false;

    std::cout << "Start Satelite" << std::endl;

    /* Parse main arguments */
    arguments = std::vector<std::string>(argv, argv + argc);
    if (arguments.size() == 2)
    {

        sateliteId = static_cast<UniqueDeviceId_t>(std::stoi(arguments[1]));

        if (sateliteId == SATELITE_1_ID)
        {
            sateliteResourcesList = SATELITE_1_RES;
            validArgument = true;
        }
        else if (sateliteId == SATELITE_2_ID)
        {
            sateliteResourcesList = SATELITE_2_RES;
            validArgument = true;
        }
    }

    if (validArgument)
    {
        Satelite* satelite = new Satelite(sateliteId, sateliteResourcesList);

        /* Create Meassege Broker (Observer Pattern!) */
        SocketServer* server = new SocketServer(sateliteId, NULL);

        /* SCHEDULER */
        while(true)
        {
            /* Socket Runner */
            server->runnerTask();

            /* Task  Runner */
            // satelite->runnerTask();

            // TODO: Add MessageBroker.runnerTask();
        }    
    }

    return 0;
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/
