#include "AIPlayer.h"

#include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6;  // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move() {
    cout << "Realizo un movimiento automatico" << endl;

    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " "
         << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color &c_piece, int &id_piece, int &dice) const {
    c_piece = actual->getCurrentColor();
    vector<int> current_dices;
    vector<int> current_pieces;
    current_dices = actual->getAvailableDices(c_piece);
    dice = current_dices[rand() % current_dices.size()];
    current_pieces = actual->getAvailablePieces(c_piece, dice);
    if (current_pieces.size() > 0) {
        id_piece = current_pieces[rand() % current_pieces.size()];
    } else {
        id_piece = SKIP_TURN;
    }

    double valor;  // Almacena el valor con el que se etiqueta el estado tras el
                   // proceso de busqueda.
    double alpha = menosinf,
           beta = masinf;  // Cotas iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una
    // sugerencia, se pueden modificar).
    /*
    valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece,
                          id_piece, dice, alpha, beta, ValoracionTest);
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " "
         << id_piece << " " << dice << endl;
    */

    // ----------------------------------------------------------------- //

    // Si quiero poder manejar varias heurísticas, puedo usar la variable id del
    // agente para usar una u otra.
    
    switch (id) {
        case 0:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA,
                                  c_piece, id_piece, dice, alpha, beta,
                                  ValoracionTest);
            break;
        case 1:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA,
                                  c_piece, id_piece, dice, alpha, beta,
                                  MiHeur);
            break;
    }
    
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " "
         << id_piece << " " << dice << endl;
    
}

void AIPlayer::thinkRandom(color &c_piece, int &id_piece, int &dice) const {
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un
    // movimiento inteligente
    // como lo que se muestran al final de la función.

    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por
    // referencia) los valores,
    // respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el
    // dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);
    // Elijo un dado de forma aleatoria.
    dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    current_pieces = actual->getAvailablePieces(c_piece, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    if (current_pieces.size() > 0) {
        id_piece = current_pieces[rand() % current_pieces.size()];
    } else {
        // Si no tengo fichas para el dado elegido, pasa turno (la macro
        // SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
    }

    /*
    // El siguiente código se proporciona como sugerencia para iniciar la
    implementación del agente.

    double valor; // Almacena el valor con el que se etiqueta el estado tras el
    proceso de busqueda. double alpha = menosinf, beta = masinf; // Cotas
    iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una
    sugerencia, se pueden modificar). valor = Poda_AlfaBeta(*actual, jugador, 0,
    PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " <<
    id_piece << " " << dice << endl;

    // ----------------------------------------------------------------- //

    // Si quiero poder manejar varias heurísticas, puedo usar la variable id del
    agente para usar una u otra. switch(id){ case 0: valor =
    Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece,
    dice, alpha, beta, ValoracionTest); break; case 1: valor =
    Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece,
    dice, alpha, beta, MiValoracion1); break; case 2: valor =
    Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece,
    dice, alpha, beta, MiValoracion2); break;
    }
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " <<
    id_piece << " " << dice << endl;

    */
}

double AIPlayer::ValoracionTest(const Parchis &estado, int jugador) {
    // Heurística de prueba proporcionada para validar el funcionamiento del
    // algoritmo de búsqueda.

    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o
    // el oponente.
    if (ganador == jugador) {
        return gana;
    } else if (ganador == oponente) {
        return pierde;
    } else {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++) {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++) {
                // Valoro positivamente que la ficha esté en casilla segura o
                // meta.
                if (estado.isSafePiece(c, j)) {
                    puntuacion_jugador++;
                } else if (estado.getBoard().getPiece(c, j).type == goal) {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++) {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++) {
                if (estado.isSafePiece(c, j)) {
                    // Valoro negativamente que la ficha esté en casilla segura
                    // o meta.
                    puntuacion_oponente++;
                } else if (estado.getBoard().getPiece(c, j).type == goal) {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del
        // oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

double AIPlayer::MiHeur(const Parchis &estado, int jugador) {
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;
    const double BOARD_SIZE = 68;

    if (ganador == jugador) {
        return gana;
    } else if (ganador == oponente) {
        return pierde;
    } else {
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);
        double dist = 0;
        int puntuacion_jugador = 0;

        for (int i = 0; i < my_colors.size(); i++) {
            color c = my_colors[i];
            for (int j = 0; j < num_pieces; j++) {

                if (estado.isSafePiece(c, j)) {
                    puntuacion_jugador+= 0.05;
                } else if (estado.getBoard().getPiece(c, j).type == goal) {
                    puntuacion_jugador += 1;
                }

                puntuacion_jugador+= (BOARD_SIZE - estado.distanceToGoal(c,j))/(4*BOARD_SIZE);

                for (auto &c_op: op_colors) {
                    dist = estado.distanceBoxtoBox(c, estado.getBoard().getPiece(c, i), estado.getBoard().getPiece(c_op, j));
                    if (dist != -1) {
                        puntuacion_jugador += (BOARD_SIZE-dist)/(2*8*BOARD_SIZE);
                    }
                }
            }
            puntuacion_jugador -= estado.piecesAtHome(c);
        }

        int puntuacion_oponente = 0;
        for (int i = 0; i < op_colors.size(); i++) {
            color c_op = op_colors[i];
            for (int j = 0; j < num_pieces; j++) {
                
                if (estado.isSafePiece(c_op, j)) {
                    puntuacion_oponente+= 0.05;
                } else if (estado.getBoard().getPiece(c_op, j).type == goal) {
                    puntuacion_oponente += 1;
                }

                puntuacion_oponente+= (BOARD_SIZE - estado.distanceToGoal(c_op,j))/(4*BOARD_SIZE);

                for (auto &c: my_colors) {
                    dist = estado.distanceBoxtoBox(c_op, estado.getBoard().getPiece(c, i), estado.getBoard().getPiece(c, j));
                    if (dist != -1) {
                        puntuacion_oponente += (BOARD_SIZE-dist)/(2*8*BOARD_SIZE);
                    }
                }
            }
            puntuacion_oponente -= estado.piecesAtHome(c_op);
        }

        return puntuacion_jugador - puntuacion_oponente;
    }
}

double AIPlayer::Poda_AlfaBeta(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, double alpha, double beta, double (*heuristic)(const Parchis &, int)) const {
    int last_dice = -1;
    int last_id_piece = -1;
    color last_c_piece = none;
    int jugador_actual = actual.getCurrentPlayerId();
    Parchis sucesor = actual.generateNextMoveDescending(last_c_piece, last_id_piece, last_dice);

    if (profundidad == profundidad_max or actual.gameOver()) {
        return heuristic(actual, jugador);
    } else {
        while (!(actual == sucesor)) {
            if (jugador == jugador_actual) {
                double prev_alpha = alpha;

                alpha = max(alpha, Poda_AlfaBeta(sucesor, jugador, profundidad + 1, profundidad_max, last_c_piece, last_id_piece, last_dice, alpha, beta, heuristic));
                
                if ((alpha != prev_alpha and profundidad == 0)) {
                    /*c_piece = get<0>(sucesor.getLastAction());
                    id_piece = get<1>(sucesor.getLastAction());
                    dice = get<2>(sucesor.getLastAction());*/
                    c_piece = last_c_piece;
                    id_piece = last_id_piece;
                    dice = last_dice;
                }

                if (alpha >= beta) {
                    return beta;
                }

            } else {
                beta = min(beta, Poda_AlfaBeta(sucesor, jugador, profundidad + 1, profundidad_max, last_c_piece, last_id_piece, last_dice, alpha, beta, heuristic));
                
                if (beta <= alpha) {
                    return alpha;
                }
            }
            sucesor = actual.generateNextMoveDescending(last_c_piece, last_id_piece, last_dice);
        }
        
        if (jugador == jugador_actual) {
            return alpha;
        } else {
            return beta;
        }
    }

   return EXIT_FAILURE;
}