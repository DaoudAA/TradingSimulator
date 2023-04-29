#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include "Bourse.h"
#include "portefeuille.h"
#include"trader.h"
#include<vector>
#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;
class Simulation{
private:
//	const Date debut;
//	const Date fin;
	double budget;
	void modifierSoldePortefeuille(Portefeuille& portefeuille, double nouveauSolde) {}
public:
	//Simulation(const Date d1, const Date d2, double b):debut(d1),fin(d2),budget(b){}
	Simulation( double b):budget(b){}
	static map <string , long > executer(Bourse& bourse, Trader& trader, Date dateDebut, Date dateFin, double soldeInit);
	//map <string,long>
	
};

 map <string , long > Simulation::executer(Bourse& bourse, Trader& trader, Date dateDebut, Date dateFin, double soldeInit)
{
	Portefeuille portefeuille(soldeInit);
	bourse.dateAujourdhui=dateDebut;
	string action;
	int qte;
	double prix;
	//map<string, long> stats;
	//stats["MON_COMPTEUR"]++;
	while(bourse.dateAujourdhui<dateFin)
	{
		vector<PrixJournalier> Pj=bourse.getPrixJournaliersAujourdhui();
		vector<string> Actions=bourse.getActionDisponibleAujourdhui();
		while(1)
		{	
			Transaction T=trader.choisirTransaction(bourse,portefeuille);
			const string& actionNom = T.getnomdAction();
			string actionNomCopy = actionNom;
				if(T.getTypeTx()==rienAFaire)
					break;
				else if ((T.getTypeTx()==achat)&&(T.getqtedAction()>0))
				{	bool found = false;
					for (auto action : Actions) {
						if (action == T.getnomdAction()) {
    						found = true;
   							 break;
    					}
					}
				if (found) {
				action=T.getnomdAction();
					qte=T.getqtedAction();
					prix=bourse.getPrixAujourdhui(action);
					portefeuille.achatTitre(action,qte,prix);}
				}
				else if ((T.getTypeTx()==vente)&&(T.getqtedAction()>0))
				for (auto titre : portefeuille.titres){
					if (titre.getNomAction() == actionNom){
						action=T.getnomdAction();
						qte=T.getqtedAction();
						prix=bourse.getLastPrixAction(action);
						portefeuille.venteTitre(action,qte,prix);
					}
					//else
				}
		}
		(bourse.dateAujourdhui).incrementerDate();
	}
}
#endif 
