#include <cstdlib>
#include <iostream>
#include <limits>
#include <menu.h>
#include <string>

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

using namespace std;

int main() {
  // ##########################################
  // #                  Menu App              #
  // ##########################################

  comandi_linux CL;
  Firewall FW;

  // Voci del menu principale
  vector<string> vociPrincipali = {"Tool utenti", "Impostazioni Firewall",
                                   "Esci"};
  Menu menuPrincipale("Tools utility", vociPrincipali);

  // Voci del sottomenu utenti
  vector<string> menu_utenti = {
      "Crea un nuovo utente",           // Indice 0
      "Modifica la password",           // Indice 1
      "Modifica i permessi di un file", // Indice 2
      "Imposta un gruppo per l'utente", // Indice 3
      "Visualizza gli utenti",          // Indice 4
      "Elimina un utente",              // Indice 5
      "Ritorna nel menu principale"     // Indice 6
  };
  Menu Menu_utenti("Menu Utente", menu_utenti);

  vector<string> menu_firewall = {
      "Aggiungi un indirizzo ip / porta",
      "Visualizza le porte salvate",
      "Ritorna nel menu principale",
  };
  Menu Menu_firewall("Menu Firewall", menu_firewall);

  bool inEsecuzione = true;

  while (inEsecuzione) {

    int scelta = menuPrincipale.esegui();

    switch (scelta) {
    case 0: {
      bool InMenuUtenti = true;

      while (InMenuUtenti) {
        int Scelta_utenti = Menu_utenti.esegui();

        switch (Scelta_utenti) {

        case 0: { // Crea un nuovo utente
          cout << "Inserisci un nome utente da creare: ";
          cin >> CL.nomeUtente;
          CL.comandoSistema = "sudo adduser " + CL.nomeUtente;
          system(CL.comandoSistema.c_str());

          // Pausa di sicurezza
          cout << "\nOperazione completata. Premi INVIO per continuare...";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cin.get();
          break;
        }

        case 1: { // Modifica la password
          cout << "Inserisci il nome utente di cui vuoi cambiare la password: ";
          cin >> CL.nomeUtente;
          CL.comandoSistema = "sudo passwd " + CL.nomeUtente;
          system(CL.comandoSistema.c_str());

          // Pausa di sicurezza
          cout << "\nOperazione completata. Premi INVIO per continuare...";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cin.get();
          break;
        }

        case 2: { // Modifica i permessi di un file (chmod)
          cout << "Inserisci il percorso del file o della cartella: ";
          cin >> CL.targetFile;

          string tipoPermesso;
          cout << "Inserisci il tipo di permesso (es. +x, 755, 644): ";
          cin >> tipoPermesso;

          CL.comandoSistema = "chmod " + tipoPermesso + " " + CL.targetFile;
          system(CL.comandoSistema.c_str());

          // Pausa di sicurezza
          cout << "\nOperazione completata. Premi INVIO per continuare...";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cin.get();
          break;
        }

        case 3: { // Imposta un gruppo per l'utente
          cout << "Inserisci il nome utente: ";
          cin >> CL.nomeUtente;
          cout << "Inserisci il nome del gruppo: ";
          cin >> CL.nomeGruppo;
          CL.comandoSistema =
              "sudo usermod -aG " + CL.nomeGruppo + " " + CL.nomeUtente;
          system(CL.comandoSistema.c_str());

          // Pausa di sicurezza
          cout << "\nOperazione completata. Premi INVIO per continuare...";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cin.get();
          break;
        }

        case 4: { // Visualizza gli utenti
          cout << "\n--- Elenco utenti registrati sul sistema ---\n";
          system("cut -d: -f1 /etc/passwd");
          cout << "-------------------------------------------\n";

          // Pausa di sicurezza
          cout << "\nPremi INVIO per continuare...";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cin.get();
          break;
        }

        case 5: { // Elimina un utente
          cout << "Inserisci il nome dell'utente da eliminare: ";
          cin >> CL.nomeUtente;

          char conferma;
          cout << "Sei sicuro di voler eliminare l'utente " << CL.nomeUtente
               << " e la sua home? (s/n): ";
          cin >> conferma;

          if (conferma == 's' || conferma == 'S') {
            CL.comandoSistema = "sudo userdel -r " + CL.nomeUtente;
            int risultato = system(CL.comandoSistema.c_str());

            if (risultato == 0) {
              cout << "Utente eliminato con successo!\n";
            } else {
              cout << "Errore durante l'eliminazione dell'utente.\n";
            }
          } else {
            cout << "Operazione annullata.\n";
          }

          // Pausa di sicurezza
          cout << "\nPremi INVIO per continuare...";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cin.get();
          break;
        }

        case 6: { // Ritorna al menu principale
          InMenuUtenti = false;
          break;
        }
        }
      }

      break;
    }

    case 1: { // Menu Firewall
      bool InMenuFirewall = true;

      while (InMenuFirewall) {
        int Scelta_firewall = Menu_firewall.esegui();

        switch (Scelta_firewall) {
        case 0: {
          cout << "Inserisci una porta: ";
          cin >> FW.PORT;
          cout << "Inserisci il tipo di protocollo (TCP/UDP): ";
          cin >> FW.PROTOCOLLO;

          if (FW.PROTOCOLLO == "TCP" || FW.PROTOCOLLO == "tcp") {
            CL.comandoSistema = "sudo ufw allow " + to_string(FW.PORT) + "/tcp";
          } else if (FW.PROTOCOLLO == "UDP" || FW.PROTOCOLLO == "udp") {
            CL.comandoSistema = "sudo ufw allow " + to_string(FW.PORT) + "/udp";
          } else {
            CL.comandoSistema = "";
          }

          if (CL.comandoSistema != "") {
            int risultato = system(CL.comandoSistema.c_str());
            if (risultato == 0) {
              cout << "\nPorta aperta con successo nel firewall!\n";
            } else {
              cout << "\nErrore durante l'impostazione della regola UFW.\n";
            }
          } else {
            cerr << "Protocollo errato! Usa TCP o UDP.\n";
          }

          cout << "\nPremi INVIO per continuare...";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cin.get();
          break;
        }

        case 1: {
          cout << "Le porte aperte sono:\n";
          system("sudo ufw status");

          cout << "\nPremi INVIO per continuare...";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cin.get();
          break;
        }

        case 2: {
          InMenuFirewall = false;
          break;
        }
        }
      }
      break;
    }

    case 2: { // Esci
      cout << "Uscita dal programma in corso...\n";
      inEsecuzione = false;
      break;
    }
      // Elimina una regola
    }
  }

  return 0;
}
