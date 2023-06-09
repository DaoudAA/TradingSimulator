#ifndef PERSISTANCEPRIXJOURNALIERS_H
#define PERSISTANCEPRIXJOURNALIERS_H

#include<vector>
#include<fstream>
#include "PrixJournalier.h"
using namespace std;

class PersistancePrixJournaliers
{
    public:
        static vector<PrixJournalier> lirePrixJournaliersDUnFichier(string chemin){
            vector<PrixJournalier> historique;
            ifstream f(chemin.c_str());
            int nbLignes= 0;
            string entete;
            if(f.is_open()){
                f>>entete;
                while(!f.eof()){
                    PrixJournalier pj(Date(-1,-1,-1),"-1",-1);
                    f>>(pj);
                    historique.push_back(pj);
                    nbLignes++;
                }
            }
            return historique;
        }
};

#endif // PERSISTANCEPRIXJOURNALIERS_H
