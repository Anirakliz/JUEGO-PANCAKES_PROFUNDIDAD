#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Clase que representa el estado del juego
class State {
public:
    vector<int> stack;  // pila de panqueques

    // Constructor por defecto
    State() {}

    // Constructor que inicializa el estado con una pila de panqueques
    State(vector<int> s) {
        stack = s;
    }

    // Operador de igualdad para comparar dos estados
    bool operator==(const State& other) const {
        return stack == other.stack;
    }

    // Función para imprimir el estado
    void print() const {
        for (int i = 0; i < stack.size(); i++) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }

    // Función que devuelve los sucesores del estado actual
    vector<State> get_successors() const {
        vector<State> successors;
        for (int i = 2; i <= stack.size(); i++) {
            vector<int> new_stack(stack);
            reverse(new_stack.begin(), new_stack.begin() + i);
            successors.push_back(State(new_stack));
        }
        return successors;
    }
};

// Función que verifica si un estado es el estado objetivo
bool is_goal_state(const State& state) {
    for (int i = 0; i < state.stack.size(); i++) {
        if (state.stack[i] != i + 1) {
            return false;
        }
    }
    return true;
}

// Función que implementa la búsqueda de profundidad
bool depth_first_search(const State& start_state, int depth_limit, vector<State>& path) {
    // Si el estado actual es el estado objetivo, terminamos la búsqueda
    if (is_goal_state(start_state)) {
        path.push_back(start_state);
        return true;
    }
    // Si hemos alcanzado el límite de profundidad, terminamos la búsqueda
    if (depth_limit == 0) {
        return false;
    }
    // Generamos los sucesores del estado actual y los exploramos recursivamente
    vector<State> successors = start_state.get_successors();
    for (int i = 0; i < successors.size(); i++) {
        if (depth_first_search(successors[i], depth_limit - 1, path)) {
            path.push_back(start_state);
            return true;
        }
    }
    return false;
}

// Función que implementa la búsqueda iterativa de profundidad
vector<State> iterative_deepening_search(const State& start_state) {
    vector<State> path;
    int depth_limit = 0;
    while (true) {
        if (depth_first_search(start_state, depth_limit, path)) {
            reverse(path.begin(), path.end());
            return path;
        }
        depth_limit++;
    }
}

int main() {
    // Creamos un estado inicial con una pila de panqueques
    State start_state({5, 3, 4, 2, 1});

    // Realizamos la búsqueda iterativa de profundidad
    vector<State> path = iterative_deepening_search(start_state);

    // Imprimimos la secuencia de estados que lleva al estado objetivo
    for (int i = 0; i < path.size(); i++) {
        path[i].print();
    }

    return 0;
}
