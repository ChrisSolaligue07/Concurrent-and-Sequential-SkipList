#include "./src/argsMain.h"


int main(int args, char **argv) {
    if (args == 1) {
        std::cout << "> Para el ingreso de argumentos: " << std::endl;
        std::cout << "> [help]   : Brinda todos los comandos para el testeo." << std::endl;
        std::cout << "> [helpC]  : Caracteristicas por defecto que lleva el testeo." << std::endl;
    }
    else if (args == 2) {
        if (std::string(argv[1]) == "helpC") helpC();
        else if (std::string(argv[1]) == "help") help();
        else if (std::string(argv[1]) == "--th") th();
        else if (std::string(argv[1]) == "--thU") thU();
        else if (std::string(argv[1]) == "--s") s();
    } else if (args == 3) {
        if (std::string(argv[1]) == "--th") {
            unsigned int threads = std::stoi(std::string(argv[2]));
            th(1000000,threads);
        }
        else if (std::string(argv[1]) == "--thU") {
            unsigned int threads = std::stoi(std::string(argv[2]));
            thU(1000000,threads);
        }
        else if (std::string(argv[1]) == "--s") {
            unsigned int elementos = std::stoi(std::string(argv[2]));
            s(elementos);
        }
    } else if (args == 4) {
        if (std::string(argv[1]) == "--th") {
            unsigned int threads = std::stoi(std::string(argv[2]));
            unsigned int elementos = std::stoi(std::string(argv[3]));
            th(elementos, threads);
        }
        else if (std::string(argv[1]) == "--thU") {
            unsigned int threads = std::stoi(std::string(argv[2]));
            unsigned int elementos = std::stoi(std::string(argv[3]));
            thU(elementos, threads);
        }
    } else if (args > 4) {
        if (std::string(argv[1]) == "--s") {
            std::vector<int> elementos;
            for (int i = 2; i < args; i++) {
                elementos.emplace_back(std::stoi(std::string(argv[i])));
            }
            sm(elementos);
        }
        else if (std::string(argv[1]) == "--th") {
            unsigned int threads = std::stoi(std::string(argv[2]));
            std::vector<int> elementos;
            for (int i = 3; i < args; i++) {
                elementos.emplace_back(std::stoi(std::string(argv[i])));
            }
            thm(elementos, threads);
        }
        else if (std::string(argv[1]) == "--thU") {
            unsigned int threads = std::stoi(std::string(argv[2]));
            std::vector<int> elementos;
            for (int i = 3; i < args; i++) {
                elementos.emplace_back(std::stoi(std::string(argv[i])));
            }
            thUm(elementos, threads);
        }
        else if (std::string(argv[1]) == "--thCsv") {
            unsigned int threads = std::stoi(std::string(argv[2]));
            unsigned int elementos = std::stoi(std::string(argv[3]));
            unsigned int casos = std::stoi(std::string(argv[4]));
            thCsv(elementos, threads, casos);
        }
    }
    return 0;
}
