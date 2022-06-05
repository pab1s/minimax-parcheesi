#ifndef __AI_PLAYER_H__
#define __AI_PLAYER_H__

#include "Attributes.h"
#include "Player.h"

class AIPlayer : public Player {
   protected:
    // Id identificativo del jugador
    const int id;

   public:
    /**
     * @brief Constructor de un objeto AIPlayer
     *
     * @param name Nombre del jugador
     */
    inline AIPlayer(const string &name) : Player(name), id(0){};

    /**
     * @brief Constructor de un objeto AIPlayer
     *
     * @param name Nombre  del jugador
     * @param id Id del jugador
     */
    inline AIPlayer(const string &name, const int id) : Player(name), id(id){};

    /**
     * @brief Función que percibe el el parchís y al jugador actual.
     * Asigna el tablero en actual y el id del jugador.
     *
     * @param p Instancia Parchis que se quiere percibir
     */
    inline virtual void perceive(Parchis &p) { Player::perceive(p); }

    /**
     * @brief Función abstracta que define el movimiento devuelto por el
     * jugador. Llama a la función movePiece con el valor asignado a los
     * parámetros pasados por referencia.
     *
     * @return true
     * @return false
     */
    virtual bool move();

    /**
     * @brief Función que se encarga de decidir el mejor movimiento posible a
     * partir del estado actual del tablero. Asigna a las variables pasadas por
     * referencia el valor de color de ficha, id de ficha y dado del mejor
     * movimiento.
     *
     * @param c_piece Color de la ficha
     * @param id_piece Id de la ficha
     * @param dice Número de dado
     */
    virtual void thinkRandom(color &c_piece, int &id_piece, int &dice) const;
    virtual void think(color &c_piece, int &id_piece, int &dice) const;

    /**
     * @brief Método que determina si el player es inteligente (decide el mejor
     * movimiento) o no. True para AIPlayer.
     *
     * @return true
     * @return false
     */
    inline virtual bool canThink() const { return true; }

    /**
     * @brief Heurística de prueba para validar el algoritmo de búsqueda.
     *
     * @param estado Instancia de Parchis con el estado actual de la partida.
     * @param jugador Id del jugador actual (0 o 1)
     * @return double
     */
    static double ValoracionTest(const Parchis &estado, int jugador);

    /**
     * @brief Heurística implementada para derrotar a los 3 ninjas. 
     * 
     * @param estado Instancia de Parchis con el estado actual de la partida.
     * @param jugador Id del jugador actual (0 o 1)
     * @return double 
     */
    static double HeurCompleta(const Parchis &estado, int jugador);

    /**
     * @brief Heurística implementada para derrotar a los 3 ninjas teniendo en  
     * cuenta lo mínimo posible.
     * 
     * @param estado Instancia de Parchis con el estado actual de la partida.
     * @param jugador Id del jugador actual (0 o 1)
     * @return double 
     */
    static double HeurSimple(const Parchis &estado, int jugador);

    /**
     * @brief Implementación del algoritmo Minimax optimizado con la poda alfa-beta.
     * 
     * @return double valor minimax de la poda alfa-beta
     */
    double Poda_AlfaBeta(const Parchis &actual, int jugador, int profundidad,
                         int profundidad_max, color &c_piece, int &id_piece,
                         int &dice, double alpha, double beta,
                         double (*heuristic)(const Parchis &, int)) const;
};
#endif