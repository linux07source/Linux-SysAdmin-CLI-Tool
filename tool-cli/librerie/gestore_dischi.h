#ifndef GESTORE_DISCHI_H
#define GESTORE_DISCHI_H

#include "menu.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <vector>

class GestoreDischi {
public:
    static void esegui() {
        std::vector<std::string> voci = {
            "Visualizza dischi e partizioni (lsblk)",
            "Formatta una partizione",
            "Ritorna al menu principale"
        };

        Menu menuDischi("--- GESTIONE DISCHI ---", voci);
        bool inMenu = true;

        while (inMenu) {
            int scelta = menuDischi.esegui();

            switch (scelta) {
            case 0: { // VISUALIZZA DISCHI
                std::cout << "\n--- DISCHI E PARTIZIONI COLLEGATE ---\n";
                system("lsblk");
                std::cout << "-------------------------------------\n";

                std::cout << "\nPremi INVIO per continuare...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 1: { // FORMATTA PARTIZIONE
                std::string partizione, filesystem, etichetta;

                std::cout << "\n--- ELENCO ATTUALE DEI DISCHI ---\n";
                system("lsblk");
                std::cout << "------------------------------------\n";

                std::cout << "Inserisci la partizione da formattare (es. /dev/sdb1): ";
                std::cin >> partizione;

                std::cout << "Scegli il filesystem (ext4, ntfs, vfat, exfat): ";
                std::cin >> filesystem;

                std::cout << "Inserisci un'etichetta (nome) per il disco: ";
                std::cin >> etichetta;

                // Conferma di sicurezza per evitare disastri
                char conferma;
                std::cout << "\nATTENZIONE: Tutti i dati su " << partizione << " saranno PERSI!\n";
                std::cout << "Sei sicuro di voler procedere? (s/n): ";
                std::cin >> conferma;

                if (conferma == 's' || conferma == 'S') {
                    // 1. Smonta la partizione se è montata
                    std::string cmdSmonta = "sudo umount " + partizione + " 2>/dev/null";
                    system(cmdSmonta.c_str());

                    // 2. Genera il comando di formattazione in base al filesystem
                    std::string cmdFormatta = "";
                    if (filesystem == "ext4") {
                        cmdFormatta = "sudo mkfs.ext4 -L \"" + etichetta + "\" " + partizione;
                    } else if (filesystem == "ntfs") {
                        cmdFormatta = "sudo mkfs.ntfs -f -L \"" + etichetta + "\" " + partizione;
                    } else if (filesystem == "vfat") {
                        cmdFormatta = "sudo mkfs.vfat -n \"" + etichetta + "\" " + partizione;
                    } else if (filesystem == "exfat") {
                        cmdFormatta = "sudo mkfs.exfat -n \"" + etichetta + "\" " + partizione;
                    } else {
                        std::cout << "[-] Filesystem non valido! Usa: ext4, ntfs, vfat o exfat.\n";
                    }

                    if (!cmdFormatta.empty()) {
                        std::cout << "\n[Esecuzione] " << cmdFormatta << "\n";
                        int ris = system(cmdFormatta.c_str());

                        if (ris == 0) {
                            std::cout << "\n[+] Disco formattato con successo in " << filesystem << "!\n";
                        } else {
                            std::cout << "\n[-] Errore durante la formattazione del disco.\n";
                        }
                    }
                } else {
                    std::cout << "Operazione di formattazione annullata.\n";
                }

                std::cout << "\nPremi INVIO per continuare...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
            }
            case 2: { // ESCI DAL SOTTOMENU
                inMenu = false;
                break;
            }
            }
        }
    }
};

#endif
