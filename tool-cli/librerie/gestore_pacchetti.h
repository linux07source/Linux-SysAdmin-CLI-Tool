#ifndef GESTORE_PACCHETTI_H
#define GESTORE_PACCHETTI_H

#include "menu.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <vector>

class GestorePacchetti {
private:
    static std::string rilevaPackageManager() {
        if (system("command -v apt > /dev/null 2>&1") == 0) return "apt";
        if (system("command -v dnf > /dev/null 2>&1") == 0) return "dnf";
        if (system("command -v pacman > /dev/null 2>&1") == 0) return "pacman";
        if (system("command -v zypper > /dev/null 2>&1") == 0) return "zypper";
        return "sconosciuto";
    }

public:
    static void esegui() {
        std::string pm = rilevaPackageManager();
        
        if (pm == "sconosciuto") {
            std::cout << "[-] Nessun gestore di pacchetti supportato trovato!\n";
            std::cout << "\nPremi INVIO per continuare...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            return;
        }

        std::vector<std::string> voci = {
            "Installa un pacchetto",
            "Disinstalla un pacchetto",
            "Reinstalla un pacchetto",
            "Aggiorna sistema / pacchetti",
            "Ritorna al menu principale"
        };

        Menu menuPkg("--- GESTIONE PACCHETTI [" + pm + "] ---", voci);
        bool inMenu = true;

        while (inMenu) {
            int scelta = menuPkg.esegui();
            std::string pkgName = "";
            std::string cmd = "";

            switch (scelta) {
            case 0: {
                std::cout << "Inserisci il nome del pacchetto da installare: ";
                std::cin >> pkgName;
                if (pm == "apt")      cmd = "sudo apt install -y " + pkgName;
                else if (pm == "dnf") cmd = "sudo dnf install -y " + pkgName;
                else if (pm == "pacman") cmd = "sudo pacman -S --noconfirm " + pkgName;
                else if (pm == "zypper") cmd = "sudo zypper install -y " + pkgName;
                break;
            }
            case 1: {
                std::cout << "Inserisci il nome del pacchetto da disinstallare: ";
                std::cin >> pkgName;
                if (pm == "apt")      cmd = "sudo apt remove -y " + pkgName;
                else if (pm == "dnf") cmd = "sudo dnf remove -y " + pkgName;
                else if (pm == "pacman") cmd = "sudo pacman -R --noconfirm " + pkgName;
                else if (pm == "zypper") cmd = "sudo zypper remove -y " + pkgName;
                break;
            }
            case 2: {
                std::cout << "Inserisci il nome del pacchetto da reinstallare: ";
                std::cin >> pkgName;
                if (pm == "apt")      cmd = "sudo apt install --reinstall -y " + pkgName;
                else if (pm == "dnf") cmd = "sudo dnf reinstall -y " + pkgName;
                else if (pm == "pacman") cmd = "sudo pacman -S --noconfirm " + pkgName;
                else if (pm == "zypper") cmd = "sudo zypper install -f -y " + pkgName;
                break;
            }
            case 3: {
                if (pm == "apt")      cmd = "sudo apt update && sudo apt upgrade -y";
                else if (pm == "dnf") cmd = "sudo dnf upgrade -y";
                else if (pm == "pacman") cmd = "sudo pacman -Syu --noconfirm";
                else if (pm == "zypper") cmd = "sudo zypper update -y";
                break;
            }
            case 4: {
                inMenu = false;
                break;
            }
            }

            if (!cmd.empty()) {
                std::cout << "\n[Esecuzione] " << cmd << "\n";
                int risultato = system(cmd.c_str());
                
                if (risultato == 0) {
                    std::cout << "\n[+] Operazione completata con successo!\n";
                } else {
                    std::cout << "\n[-] Errore durante l'esecuzione del comando.\n";
                }

                std::cout << "\nPremi INVIO per continuare...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        }
    }
};

#endif
