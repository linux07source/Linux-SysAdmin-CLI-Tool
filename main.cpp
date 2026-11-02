#include <iostream>
#include <string>

using namespace std;

// 1. Strutture dati
struct comandi_linux {
  std::string nomeUtente = "";
  std::string passwordUtente = "";
  std::string nomeGruppo = "";
  std::string targetFile = "";
  std::string comandoSistema = "";
};

struct Firewall {
  int PORT = 0;
  std::string PROTOCOLLO = "";
};

// 2. Inclusione dei moduli
#include "./librerie/gestore_dischi.h"
#include "./librerie/gestore_pacchetti.h"
#include "./librerie/menu_firewall.h"
#include "./librerie/menu_principale.h"
#include "./librerie/menu_utenti.h"

int main() {
  comandi_linux CL;
  Firewall FW;

  Menu menuPrincipale = creaMenuPrincipale();
  bool inEsecuzione = true;

  while (inEsecuzione) {
    int scelta = menuPrincipale.esegui();

    switch (scelta) {
    case 0: {
      gestisciMenuUtenti(CL);
      break;
    }
    case 1: {
      gestisciMenuFirewall(CL, FW);
      break;
    }
    case 2: {
      GestorePacchetti::esegui();
      break;
    }
    case 3: {
      GestoreDischi::esegui();
      break;
    }
    case 4: {
      cout << "Uscita dal programma in corso...\n";
      inEsecuzione = false;
      break;
    }
    }
  }

  return 0;
}
