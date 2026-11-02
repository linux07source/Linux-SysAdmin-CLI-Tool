#ifndef GENERATORE_PASSWORD_H
#define GENERATORE_PASSWORD_H

#include <string>
#include <random>
#include <iostream>
#include <limits>
#include <vector>

inline void GeneratorePassword(comandi_linux &CL)
{
    std::vector<std::string> voci = {
        "Genera una password casuale", // 0
        "Ritorna nel menu principale"  // 1
    };

    Menu menuGeneratorePassword("Menu Generatore Password", voci);
    bool inMenu = true;

    while (inMenu)
    {
        int scelta = menuGeneratorePassword.esegui();

        switch (scelta)
        {
        case 0:
        {
            const std::string caratteri = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";
            const size_t lunghezzaPassword = 12; // Lunghezza della password generata

            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_int_distribution<> distribuzione(0, caratteri.size() - 1);

            std::string passwordGenerata;
            for (size_t i = 0; i < lunghezzaPassword; ++i)
            {
                passwordGenerata += caratteri[distribuzione(generator)];
            }

            CL.passwordUtente = passwordGenerata;

            std::cout << "\nPassword generata: " << CL.passwordUtente << "\n";
            std::cout << "Premi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 1:
        {
            inMenu = false;
            break;
        }
        default:
        {
            std::cout << "\n[ERRORE]: Scelta non valida. Riprova.\n";
            std::cout << "Premi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        }
    }
}

#endif