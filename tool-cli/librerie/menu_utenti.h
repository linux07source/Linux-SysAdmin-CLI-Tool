#ifndef MENU_UTENTI_H
#define MENU_UTENTI_H

#include "menu.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>

inline void gestisciMenuUtenti(comandi_linux& CL) {
    std::vector<std::string> voci = {
        "Crea un nuovo utente",            // 0
        "Modifica la password",            // 1
        "Modifica i permessi di un file",  // 2
        "Imposta un gruppo per l'utente",  // 3
        "Visualizza gli utenti",           // 4
        "Elimina un utente",               // 5
        "Ritorna nel menu principale"      // 6
    };
    
    Menu menuUtenti("Menu Utente", voci);
    bool inMenu = true;

    while (inMenu) {
        int scelta = menuUtenti.esegui();

        switch (scelta) {
        case 0: {
            std::cout << "Inserisci un nome utente da creare: ";
            std::cin >> CL.nomeUtente;
            CL.comandoSistema = "sudo adduser " + CL.nomeUtente;
            system(CL.comandoSistema.c_str());

            std::cout << "\nOperazione completata. Premi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 1: {
            std::cout << "Inserisci il nome utente di cui vuoi cambiare la password: ";
            std::cin >> CL.nomeUtente;
            CL.comandoSistema = "sudo passwd " + CL.nomeUtente;
            system(CL.comandoSistema.c_str());

            std::cout << "\nOperazione completata. Premi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 2: {
            std::cout << "Inserisci il percorso del file o della cartella: ";
            std::cin >> CL.targetFile;
            std::string tipoPermesso;
            std::cout << "Inserisci il tipo di permesso (es. +x, 755, 644): ";
            std::cin >> tipoPermesso;

            CL.comandoSistema = "chmod " + tipoPermesso + " " + CL.targetFile;
            system(CL.comandoSistema.c_str());

            std::cout << "\nOperazione completata. Premi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 3: {
            std::cout << "Inserisci il nome utente: ";
            std::cin >> CL.nomeUtente;
            std::cout << "Inserisci il nome del gruppo: ";
            std::cin >> CL.nomeGruppo;
            CL.comandoSistema = "sudo usermod -aG " + CL.nomeGruppo + " " + CL.nomeUtente;
            system(CL.comandoSistema.c_str());

            std::cout << "\nOperazione completata. Premi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 4: {
            std::cout << "\n--- Elenco utenti registrati sul sistema ---\n";
            system("cut -d: -f1 /etc/passwd");
            std::cout << "-------------------------------------------\n";

            std::cout << "\nPremi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 5: {
            std::cout << "Inserisci il nome dell'utente da eliminare: ";
            std::cin >> CL.nomeUtente;
            char conferma;
            std::cout << "Sei sicuro di voler eliminare l'utente " << CL.nomeUtente
                      << " e la sua home? (s/n): ";
            std::cin >> conferma;

            if (conferma == 's' || conferma == 'S') {
                CL.comandoSistema = "sudo userdel -r " + CL.nomeUtente;
                int risultato = system(CL.comandoSistema.c_str());
                if (risultato == 0) {
                    std::cout << "Utente eliminato con successo!\n";
                } else {
                    std::cout << "Errore durante l'eliminazione dell'utente.\n";
                }
            } else {
                std::cout << "Operazione annullata.\n";
            }

            std::cout << "\nPremi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 6: {
            inMenu = false;
            break;
        }
        }
    }
}

#endif
