#ifndef STATO_RETE_H
#define STATO_RETE_H

#include <iostream>
#include <vector>
#include <menu.h>
#include <limits>
#include <string>
#include <cstdlib>

inline void GestisciMenuStatoRete(comandi_linux &CL)
{
    std::vector<std::string> voci = {
        "Visualizza lo stato della rete",   // 0
        "Visualizza le interfacce di rete", // 1
        "Ritorna nel menu principale"       // 2
    };

    Menu menuStatoRete("Menu Stato Rete", voci);
    bool inMenu = true;

    while (inMenu)
    {
        int scelta = menuStatoRete.esegui();

        switch (scelta)
        {
        case 0:
        {
            CL.comandoSistema = "hostname -I";
            system(CL.comandoSistema.c_str());

            std::cout << "\nPremi INVIO per continuare...";
            // Pulisce eventuali residui nel buffer prima di metterlo in attesa dell'INVIO
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 1:
        {
            CL.comandoSistema = "ip addr show";
            system(CL.comandoSistema.c_str());

            std::cout << "\nPremi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 2:
        {
            inMenu = false;
            break;
        }
        default:
        {
            // Gestione opzione non valida per evitare loop infiniti o comportamenti imprevisti
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