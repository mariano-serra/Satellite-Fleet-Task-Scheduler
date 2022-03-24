/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <sstream>
#include "Satelite.h"

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
static SateliteId_t sateliteId;
static Resources::ResourcesList_t sateliteResourcesList;

/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/

bool parseArgument(std::vector<std::string> &arguments)
{
    bool ret = true;

    if (arguments.size() == 5)
    {
        uint16_t index = 0;
        for (std::vector<std::string>::iterator it = arguments.begin(); (it < arguments.end() && ret == true); ++it, ++index)
        {
            std::string argument = *it;
            std::stringstream resourceString(argument);

            switch(index)
            {
            case 0:
                break;

            case 1:
                if (argument.compare(std::string{"-id"}))
                {
                    ret = false;
                }
                break;

            case 2:
                sateliteId = static_cast<SateliteId_t>(std::stoi(argument));
                std::cout << "> Id = " << sateliteId << std::endl;
                break;

            case 3:
                if (argument.compare(std::string{"-res"}))
                {
                    ret = false;
                }
                break;

            case 4:
                std::cout << "> Resources = {";
                for (int i; resourceString >> i;)
                {
                    sateliteResourcesList.push_back(i);
                    std::cout << i << ",";
                    if (resourceString.peek() == ',')
                    {
                        resourceString.ignore();
                    }
                }
                std::cout << "}" << std::endl;
                break;

            default:
                break;
            }
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}


int main(int argc, char **argv)
{
    bool ret = false;

    std::cout << "Start Satelite" << std::endl;

    /* Parse main arguments */
    arguments = std::vector<std::string>(argv, argv + argc);
    ret = parseArgument(arguments);

    if (ret)
    {
        Satelite *satelite = new Satelite(sateliteId, sateliteResourcesList); 

        /* Create Meassege Broker (Observer Pattern!) */
        // saletelite se registra para recibir notidicaciones de protocolo 

        /* SCHEDULER */
        while(false)
        {
            satelite->runnerTask();

            // TODO: Add MessageBroker.runnerTask();
        }    
    }

    return 0;
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/
