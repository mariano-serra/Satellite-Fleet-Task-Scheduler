/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef FRAME_LAYER_H
#define FRAME_LAYER_H

/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "Task.h"
#include "SocketServer.h"
#include "SocketClient.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos                                 */
/* ---------------------------------------------------------------------------*/

/**
 *  Identificador unico de paquete (frame).
 *  Sirve como cabecera, para identificar el tipo de paquete enviado/recibido.
 *  Equivalente a SOF (Start of Frame).
 *  */
typedef uint32_t FrameId_t;

/** Estructura de datos para el envio/recepcion de tareas */
typedef struct FrameTask
{
    FrameId_t frameId;
    Task::TaskId_t taskId;
    Task::Payoff_t payoff;
    Resources::ResourceAmount_t resourcesAmount;
    Resources::ResourceElement_t resourcesList[256];
    Task::State_t state;
} FrameTask_t;

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas                               */
/*----------------------------------------------------------------------------*/

/**
 * @brief Capa de abstraccion entre la AppConexionLayer y el socket (capa fisica).
 * @details Permite abstraerse al FrameLayer de la capa fisica para el
 *          envio y recepcion de tarea.
 */
class FrameLayer
{
public:

    /**
     * @brief Contructor
     * @details
     *
     * @param sockeType Identificador de tipo de Socket a construir (server o cliente).
     * @param serverId Identificador unico de dispositivo.
     */
    FrameLayer(Socket::SocketType sockeType, UniqueDeviceId_t serverId);

    /**
     * @brief Destructor
     * @details
     */
    ~FrameLayer();

    /**
     * @brief Metodo de envio de estructura de datos de tarea.
     * @details Encargado de convertir una estructura de tarea en un buffer de datos que entiende el Socket.
     *
     * @param taskFrame puntero a estructura de tarea a transmitir
     */
    void sendFrameTask(FrameTask_t* taskFrame);

    /**
     * @brief Metodo de recepcion de una tarea.
     * @details Encargado de traducir un buffer de datos recibidos por el Socket y traducirlo
     *          a una nueva estructura de tarea a procesar por la AppConexionLayer.
     *
     * @param taskFrame puntero a estructura de tarea recibida
     * @return retorna true, si se recibio una nueva estructura de tarea.
     */
    bool receiveFrameTask(FrameTask_t* taskFrame);

    /**
     * @brief Metodo para la ejecucion de tareas asociadas a la recepcion y envio de datos por el protocolo.
     * @details Encargado de llamar al 'runnerTask' de las capas de abstracion inferiores.
     */
    void runnerTask(void);

private:
    /** Punteros necesarios para la construccion de capa de abstraccion inferior */
    Socket::SocketType m_sockeType;
    SocketServer* m_socketServer;
    SocketClient* m_socketClient;
};

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // FRAME_LAYER_H
