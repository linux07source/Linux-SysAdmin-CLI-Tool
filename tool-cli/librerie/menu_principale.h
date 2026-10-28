#ifndef MENU_PRINCIPALE_H
#define MENU_PRINCIPALE_H

#include "menu.h"
#include <vector>
#include <string>

inline Menu creaMenuPrincipale() {
    std::vector<std::string> voci = {
        "Tool utenti", 
        "Impostazioni Firewall", 
        "Gestione Pacchetti",
        "Esci"
    };
    return Menu("Tools utility", voci);
}

#endif
