#ifndef MENU_FIREWALL_H
#define MENU_FIREWALL_H

#include "menu.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>

inline void gestisciMenuFirewall(comandi_linux& CL, Firewall& FW) {
    std::vector<std::string> voci = {
        "Aggiungi un indirizzo ip / porta",
        "Visualizza le porte salvate",
        "Ritorna nel menu principale"
    };
    
    Menu menuFirewall("Menu Firewall", voci);
    bool inMenu = true;

    while (inMenu) {
        int scelta = menuFirewall.esegui();

        switch (scelta) {
        case 0: {
            std::cout << "Inserisci una porta: ";
            std::cin >> FW.PORT;
            std::cout << "Inserisci il tipo di protocollo (TCP/UDP): ";
            std::cin >> FW.PROTOCOLLO;

            if (FW.PROTOCOLLO == "TCP" || FW.PROTOCOLLO == "tcp") {
                CL.comandoSistema = "sudo ufw allow " + std::to_string(FW.PORT) + "/tcp";
            } else if (FW.PROTOCOLLO == "UDP" || FW.PROTOCOLLO == "udp") {
                CL.comandoSistema = "sudo ufw allow " + std::to_string(FW.PORT) + "/udp";
            } else {
                CL.comandoSistema = "";
            }

            if (CL.comandoSistema != "") {
                int risultato = system(CL.comandoSistema.c_str());
                if (risultato == 0) {
                    std::cout << "\nPorta aperta con successo nel firewall!\n";
                } else {
                    std::cout << "\nErrore durante l'impostazione della regola UFW.\n";
                }
            } else {
                std::cerr << "Protocollo errato! Usa TCP o UDP.\n";
            }

            std::cout << "\nPremi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 1: {
            std::cout << "\n--- Stato UFW e porte aperte ---\n";
            system("sudo ufw status");
            std::cout << "---------------------------------\n";

            std::cout << "\nPremi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 2: {
            inMenu = false;
            break;
        }
        }
    }
}

#endif
