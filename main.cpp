#include "Simulation.h"
#include "Date.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
int main(){
    string ch1;
    ch1="../prices_simple.csv";
    srand(time(NULL));
	vector<PrixJournalier> vPj;
    PersistancePrixJournaliers ppj;
	vPj=ppj.lirePrixJournaliersDUnFichier(ch1);
    map <string , long > statiktiks;
    int choix;
    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. \tDemarrer une simulation" << endl;
        cout << "2. \tLire les journaux des simulations precedentes a partir du logs.txt" << endl;
        cout << "3. \tExit" << endl;
        cin >> choix;
        
        switch (choix) {
            case 1: {
                Date dateDebut(1,1,2010), dateFin(31,12,2016);
                string strader="";
                Trader * trader=NULL;
                int choixTrader=0, choixBourse=0;
                do {
                    cout << "\n--- TRADERS ---" << endl;
                    cout << "1. \tTrader Aleatoire" << endl;
                    cout << "2. \tTrader Bollinger" << endl;
                    cout << "3. \tTrader Algorithmique" << endl;
                    cout << "4. \tTrader Reverse Mean" << endl;
                    cout << "5. \tTrader Manuel" << endl;
                    cin >> choixTrader;

                    switch (choixTrader) {
                        case 1:
                            trader= new TraderAlea;
                            strader="TraderAleatoire";
                            break;
                        case 2:
                            trader= new TraderBollin1;
                            strader="TraderBollinger";
                            break;
                        case 3:
                            trader= new TraderAlgo1;
                            strader="TraderAlgorithmique";
                            break;
                        case 4:
                            trader= new TraderReverseMean;
                            strader="TraderReverseMean";
                            break;
                        case 5:
                            trader= new TraderManuel;
                            strader="Trader Manuel";
                            break;
                        default:
                            cout << "Choix Invalide. Ressayer!" << endl;
                            break;
                    }
                } while (choixTrader < 1 || choixTrader > 5);
                Bourse * bourse=NULL;
                do{
                cout << "\n--- BOURSES ---" << endl;
                cout << "1. BourseDictNom" << endl;
                cout << "2. BourseDictDate" << endl;
                cout << "3. BourseVector" << endl;
                cout << "4. BourseVector2" << endl;
                cout << "5. BourseSet" << endl;
                cin >> choixBourse;
                
                switch (choixBourse) {
                    case 1:
                        bourse = new BourseDictNom(vPj);
                        break;
                    case 2:
                        bourse = new BourseDictDate(vPj);
                        break;
                    case 3:
                        bourse = new BourseVector(vPj);
                        break;
                    case 4:
                        bourse = new BourseVector2(vPj);
                        break;
                    case 5:
                        bourse = new BourseSet(vPj);
                        break;
                    default:
                        cout << "Choix Invalid . Ressayer" << endl;
                        continue;
                }
                } while (choixTrader < 1 || choixTrader > 5);
                
            cout << "\nEntrer date debut de simulation (DD/MM/YYYY): ";
            string dateDStr;
            do {
                cin >> dateDStr;
                dateDebut = Date(dateDStr);
                if (dateDebut.getJour()==-1 || dateDebut.getMois()==-1) {
                    cout << "Date Invalide. Ressayer: ";
                }
            } while (dateDebut.getJour()==-1 || dateDebut.getMois()==-1);

            cout << "Entrer date fin de simulation (DD/MM/YYYY): ";
            string dateFStr;
            do {
                cin >> dateFStr;
                dateFin = Date(dateFStr);
                if (dateFin.getJour()==-1 || dateFin.getMois()==-1) {
                    cout << "Date Invalide. Ressayer: ";
                }
            } while (dateFin.getJour()==-1 || dateFin.getMois()==-1);
            double soldeInit=0;
            cout << "Entrer Budget initial: ";
            cin >> soldeInit;
            while(soldeInit <= 0){
                cout << "Budget initial doit etre superieur a 0. Reessayer!: ";
                cin >> soldeInit;
            }
            Simulation Sim(soldeInit);
            statiktiks = Sim.executer(*bourse, *trader, dateDebut, dateFin, soldeInit);
            cout << "\nStats:" << endl;
            for (auto it = statiktiks.begin(); it != statiktiks.end(); ++it) {
                cout << it->first << ": " << it->second << endl;
            }
            //ecriture dans logs 
            string fileName="../status.txt";
            ofstream flot(fileName, ios::app); 
            if (!flot) {
                flot.open("status.txt");
            }
            flot<<strader<<":\t"<<dateDebut<<":\t"<<dateFin<<":\t"<<statiktiks["Nbr_de_Jours"]<<
            ":\t"<<statiktiks["Taux_du_gain_en_%"]<<":\t"<<(-soldeInit+statiktiks["soldeFinal"])<<
            ":\t"<<soldeInit<<":\t"<<statiktiks["soldeFinal"]<<":\t"<<statiktiks["NombreDeTransaction"]<<
            ":"<<statiktiks["nombreDAchat"]<<":"<<statiktiks["nombreDVente"]<<":"<<statiktiks["Nbr_fois_appelauPJA"]<<
            ":\t"<<statiktiks["Temps_ChoixTransaction_µs"]<<":\t"<<statiktiks["Temps_GetPrixJournalierAujourdhui_µs"]<<
            ":\t"<<statiktiks["Temps_getLPrixAction"]<<endl;
            flot.close(); 
            break;
        }
        case 2: {
            string ligne;
            char* fileName = "../status.txt";
            ifstream flot(fileName);
            while(getline(flot,ligne)){
                cout << ligne << endl;
            }
            break;
        }
        case 3:// Exit 
        {
            cout << "Fin de programme. Goodbye!" << endl;
            break;
        }
        default: {
            cout << "Choix Invalide. Reessayer!" << endl;
            break;
        }
    }
} while (choix != 3);

    return 0 ;
}