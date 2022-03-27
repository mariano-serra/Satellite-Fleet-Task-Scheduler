/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef APP_CONEXION_LAYER_H
#define APP_CONEXION_LAYER_H

/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "FrameLayer.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos                                 */
/* ---------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas                               */
/*----------------------------------------------------------------------------*/

/**
 * @brief Capa de abstraccion entre la dispositivo y el FrameLayer.
 * @details Permite abstraerse al target (satelite, GroundControl, etc) del
 *          envio y recepcion de tarea, sin conocer del protocolo de comunicacion
 */
class AppConexionLayer
{
public:
    /**
     * @brief Constructor
     * @details
     *
     * @param sockeType Identificador de tipo de Socket a construir (server o cliente).
     * @param serverId Identificador unico de dispositivo.
     */
    AppConexionLayer(Socket::SocketType sockeType, UniqueDeviceId_t serverId);

    /**
     * @brief Destructor
     * @details
     */
    ~AppConexionLayer();

    /**
     * @brief Metodo de envio de tarea.
     * @details Encargado de convertir una tarea en un paquete (frame) que entiende el FrameLayer.
     *
     * @param task puntero a tarea a transmitir
     */
    void sendTask(Task* task);

    /**
     * @brief Metodo de recepcion de una tarea.
     * @details Encargado de traducir un paquete recibido (frame) por el FrameLayer y traducirlo a una nueva tarea
     *          a procesar por dispositivo.
     *          Este metodo es el encargado de alocar dinamicamente.
     *
     * @param task puntero soble a de tarea recibida (construida).
     * @return retorna true, si se recibio una nueva tarea.
     */
    bool receiveTask(Task** task);

    /**
     * @brief Metodo para la ejecucion de tareas asociadas a la recepcion y envio de datos por el protocolo.
     * @details Encargado de llamar al 'runnerTask' de las capas de abstracion inferiores.
     */
    void runnerTask(void);

private:
    /** Puntero a capa de abstraccion inferior */
    FrameLayer* m_frameLayer;
};

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // APP_CONEXION_LAYER_H
