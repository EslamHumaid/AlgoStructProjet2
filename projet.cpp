/**
 * @file projet.cpp
 * @author BAGHAWITAH Ahmed, HUMAID Eslam
 * @date 14/12/2019 Création
 * @brief un algorithme de tri par fusion multiple de monotonies
 * @b gitHub: https://github.com/EslamHumaid/AlgoStructProjet2.git
**/
#include<iostream> // cout, cin
using namespace std;


/******* constants & structs ******/


typedef char DATATYPE;

//Chaînage
typedef struct _datum{
    DATATYPE valeur; // valeur d'un element dans le chaînage
    _datum * suiv; // l'element suivant
} data ;

typedef data * p_data;



//lists of Monotonies
typedef struct _datallst {
    int capa ; // nombre de cases réservée en mémoire pour le tableau
    int nbmono ; // le nombre de cases effectivement utilisées 
    p_data * monotonies ; // tableau des monotonies

} datalistes ;

/*******************************/


/*** fonctions de Chaînage ***/

/**
 * @b Role : affiche (sur une même ligne) les valeurs stockées dans le chaînage chain
 * @param : la tete d'un chainage.
**/
void affCh(p_data chain){

    p_data tmp = chain; // l'element courant

    while(tmp != nullptr){  //parcours sur le chainage
        cout << tmp->valeur;
        tmp = tmp->suiv;
    }
    cout << "" << endl;
}


/**
 * @b Role : crée un nouveau maillon avec la valeur val et l'ajoute a la fin du chainage. 
 * @param : valeur a ajouter, la tete d'un chainage.
**/
void ajoutFin(DATATYPE val, p_data & head){

    p_data toAdd; // l'element a ajouter; 
    toAdd = (data*)malloc(sizeof(data));
    toAdd->valeur = val;
    toAdd->suiv = nullptr;



    if (head==nullptr) { // si la tete est null donc la nouvelle tete sera l'element a ajouter

        head = toAdd; 

    } else { 

        p_data tmp = head; // l'element courant

        while((tmp->suiv) != nullptr){  //parcourir jusqu'a le dernier element du chainage
            tmp = tmp->suiv;
        }

        tmp->suiv = toAdd; // ajouter l'element a la fin du chainage
        
        
    }   

}

/**
 * @b Role : crée un nouveau maillon avec la valeur uneval et retourne la tête d’un
 *           chaînage commençant par ce maillon et continuant avec chain.
 * @param : valeur a ajouter, la tete d'un chainage.
**/
p_data ajoutDevant(DATATYPE uneval, p_data chain){
    p_data nouveau; // l'element a ajouter; 

    nouveau = (data*)malloc(sizeof(data));
    nouveau->valeur = uneval;
    nouveau->suiv = chain;

    return nouveau;



}

/**
 * @b Role : lire (sur l’entrée standard) une succession de nb valeurs et les mémorise
 *  (dans le même ordre) dans un chaînage terminé par nullptr, dont la tête est renvoyée. 
 * @param : nombre des valeurs a ajouter. 
**/
p_data saisieNombre(int nb){

    DATATYPE val;
    cout << "Entrez la valeur?" << endl;
    cin >> val; // entrer premiere valeur qui represente la tete. 
    p_data head = (data*)malloc(sizeof(data)); 
    head->valeur = val;
    head->suiv = nullptr; 

    p_data tmp = head; // pour ne pas modifier le head

    for(int i=2 ; i<= nb ; i++){ // commence par la deuxieme valeur
        cout << "Entrez la valeur?" << endl;
        cin >> val; // l'element a ajouter

        tmp->suiv = (data*)malloc(sizeof(data)); 
        tmp->suiv->valeur = val; 
        tmp->suiv->suiv = nullptr;

        tmp = tmp->suiv; 

    }

    return head; 

}

/**
 * @b Role :lire (sur l’entrée standard) une succession de valeurs et les
 *           mémorise (dans le même ordre) dans un chaînage terminé par nullptr, 
 *           dont la tête est renvoyée. La saisie se termine 
 *          à la première occurrence d’une valeur égale à sentinelle 
 * @param : la valeur d'arret. 
**/
p_data saisieBorne(DATATYPE sentinelle){

    DATATYPE val;
    cout << "valeur de head ?" << endl;
    cin >> val; // entrer premiere valeur qui represente la tete. 
    p_data head = (data*)malloc(sizeof(data)); 
    head->valeur = val;

    p_data tmp = head; // pour ne pas modifier le head

    while(val != sentinelle){
        cout << "valeur?" << endl;
        cin >> val; // l'element a ajouter
        
        tmp->suiv = (data*)malloc(sizeof(data)); 
        tmp->suiv->valeur = val; 
        tmp->suiv->suiv = nullptr;

        tmp = tmp->suiv; 

    }

    return head;

}

/**
 * @b Role : qui compte le nombre de monotonies croissantes dans un chaînage terminé par nullptr
 * @param : la tete d'un chainage.
**/
int nbCroissance(p_data chain){

    p_data tmp = chain; //l'element courant
    int nbMonotonies = 1;  //car si toutes les lettres du mot sont en ordre croissante, on aura une seul grande monotonie ex: mot = abcd, monotonie croissante =  abcd = 1

    while(tmp->suiv != nullptr){ //parcourir le chainage

        if((tmp->valeur) >= (tmp->suiv)->valeur ){ // condition de teste de la monotonie (cf. rapport)

            nbMonotonies++;

        }

        tmp = tmp->suiv;

    }

    return nbMonotonies;

}

/**
 * @b Role : retirer la tete d'un chainage, le deuxieme element devient la nouvelle tete.
 * @param : la tete d'un chainage.
**/
void removeFirstEle(p_data & chain) { // remove first element of a chaine & return new head
    
    p_data exHead = chain; //sauvegarder la tete pour qu'elle soit desallouer apres. 
    chain = chain->suiv;
    free(exHead);

}

/**
 * @b Role : copier la tete d'un chainage
 * @param : la tete d'un chainage.
**/
p_data clone(p_data chain) { 

    p_data tmp = (data*)malloc(sizeof(data));
    tmp->valeur = chain->valeur; 
    tmp->suiv = chain->suiv; 

    return tmp;
}

/**
 * @brief: take an element from chain sec, then put it in the right place at chain pre.
 *         repreat the process for another element until chain sec's elements end. 
 * @b Role: fusionne deux chaînages terminés par nullptr, supposés triés par ordre croissant. 
 *          Le résultat obtenu est trié par ordre croissant.
 * @param: les tetes des deux chainages. 
**/
p_data fusion(p_data prem, p_data sec) { 

    p_data restChain=sec; // une variable pour sauvegarder la rest du chainage
    p_data tmpPrem = prem; // l'element courant de premier chainage
    p_data tmpSec = sec; // l'element courant de deuxieme chainage
   
    
    while (restChain != nullptr ) { 
            
        bool ok = true; // pour arreter la deuxieme boucle
        tmpPrem = prem;
        tmpSec = restChain;

       while (tmpPrem != nullptr && ok ) { 

            if (((tmpPrem->suiv)==nullptr))  { // ajouter a la fin du chainage

                tmpPrem->suiv = tmpSec; 
                restChain = tmpSec->suiv;
                tmpSec->suiv = nullptr;
                ok = false; 

              // ajouter au milieu du chainage  
            } else if ((tmpSec->valeur >= tmpPrem->valeur) && ((tmpSec->valeur <= (tmpPrem->suiv)->valeur))){ 

                restChain = tmpSec->suiv;
                tmpSec->suiv = tmpPrem->suiv;
                tmpPrem->suiv = tmpSec;
                ok = false; 

                // ajouter au debut
            } else if ((tmpSec->valeur <= tmpPrem->valeur)) { 

               restChain = tmpSec->suiv;
                tmpSec->suiv = tmpPrem;
                prem = tmpSec;
                ok = false;   
                
            } else { 
                
                tmpPrem = tmpPrem->suiv;

            }
            
        }
 
    }         
     
    return prem; 

}

/**
 * @b Role : place dans le chaînage mono la première monotonie croissante de chain et l’en retire
 * @param : les tetes des deux chainages. celui de mono et de chain.
**/
void extraireCroissance(p_data & chain, p_data & mono) {

    p_data tmp = clone(chain); // copier "valeur" and "suiv" de la tete
    
    ajoutFin((tmp->valeur),mono);  // premier element du chainage va toujours etre ajoute a mono.
    
    removeFirstEle(chain); // retirer la tete d'un chainage, le deuxieme element devient la nouvelle tete.

    while( ( (tmp->suiv) != nullptr) && ((tmp->valeur) < (chain->valeur) ) ) { // pour extraire la monotonie

       
        free(tmp);
        ajoutFin(chain->valeur,mono);
        tmp = clone(chain);
        removeFirstEle(chain);

        
    }

    free(tmp);  

}

//------------------- fin des fonction de chainage --------------
//--------------------------------------------------------------------

/*** fonctions des Monotonies ***/

/**
 * @b Role : crée et renvoie une structure (de type datalistes) initialisée avec un tableau de nb chaînages (non valués).
 * @param : nombre des cases réservées en mémoire pour le tableau
**/
datalistes initT(int nb) {

    datalistes newList;

    newList.capa = nb;

    newList.nbmono = 0; // nombre cases utilisee = zero; 

    newList.monotonies = (p_data*)malloc(nb*sizeof(p_data));

    //initialiser les cases du tableau     
    for(int j = 0 ; j < newList.capa ; j++ ){
        newList.monotonies[j] = nullptr;
    }
    
    return newList;

}

/**
* @brief: go to the last unused case whose indixe is nbmono (not (nbmono-1) cuz idixes here start with 0), then put chain in it.
* @b Role: ajoute dans le tableau mono le chaînage chain (dans la prochaine case non utilisée).
* @PRE: 
* @POST:
* @parem: la tete du chainage, tableau des monotonies
**/
void ajouterFin(p_data chain,datalistes & mono) {

    mono.monotonies[mono.nbmono] = chain; 

    mono.nbmono++; 

}

/**
 * @b Role : afficher (une ligne par case) les valeurs stockées dans le tableau mono.
 * @param : tableau des monotonies
**/
void affT(datalistes mono){

    for (int i=0;i<mono.nbmono;i++) { // parcourir les cases du tableau

        affCh(mono.monotonies[i]);
         

    }

}

/**
* @breif: delete has done by assigning to NULL (malloc intialise to NULL)
* @PRE: 
* @POST:
* @param : tableau des monotonies
**/
p_data suppressionFin(datalistes & mono) {

    int indexeLastEle = mono.nbmono-1; // l'indice de la derniere case
    p_data lastEle = mono.monotonies[indexeLastEle]; // la derniere case

    mono.monotonies[indexeLastEle] = nullptr; // malloc intialise a nullptr
    mono.nbmono--;

    return lastEle; 

}


/**
 * @b Role: renvoie un chaînage formé en mettant bout à bout (dans l’ordre) tous les chaînages stockés dans le tableau mono, en les y enlevant
 * @PRE:
 * @POST:
 * @param : tableau des monotonies
 * */
p_data suppressionTotale(datalistes & mono) { 

    p_data tmp; // l'element courant
    p_data chain; // la chain des monotonies

    for (int i=1;i<(mono.nbmono);i++) { //parcourir la liste

        tmp = mono.monotonies[0];
        while(tmp->suiv != nullptr){ //parcourir la monotonie
            tmp = tmp->suiv;
        }

        tmp->suiv = mono.monotonies[i];


    }

    chain = mono.monotonies[0];

    for(int i = 0 ; i < mono.nbmono; i++){       //enlever les elements du tableau
        mono.monotonies[i] = nullptr;
        mono.nbmono--;

    }

    return chain; 

}


/**
 * @brief: return a tableau with the cases filled with the monotonies of chain
 * @b Role: retournant un tableau dont les cases contiennent (dans l’ordre) les monotonies croissantes du chaînage contenu dans chain
 * @PRE:
 * @POST:
 * @param : la tete du chainage
 * */
datalistes separation(p_data & chain){

    int nbCases = nbCroissance(chain); //nombre des case du tableau
    datalistes tab = initT(nbCases); //initialiser le tableau 
    
    for(int i = 0 ; i < nbCases ; i++ ){ //mettre les monotonies dans le tableau
        
        extraireCroissance(chain, tab.monotonies[i]);
        tab.nbmono++;

    }

    return tab;

}


/**
 * @brief: put the fusion of all elements of a tab in the first case orderd by croissant order
 * @b Role: effectuer une fusion multiple des monotonies stockées dans le tableau, pour ne conserver à la fin qu’un seul chaînage trié dans la première case
 * @PRE:
 * @POST:
 * @param : tableau des monotonies
 * */
void trier(datalistes & tabmono){

    for(int i = 1 ; i < (tabmono.nbmono); i++){ //fusion multiple dans la premiere case du tableau

        tabmono.monotonies[0] = fusion(tabmono.monotonies[0], tabmono.monotonies[i]);

    }

    tabmono.nbmono = 1;

}


/**
 * @brief return the chain order by croissant order
 * @b Role: trier un chaînage en utilisant une fusion multiple.
 * @PRE:
 * @POST:
 * @param : la tete du chainage
 * */
void trierCh(p_data & chain){

    cout << "separating monotonies..." << endl;
    datalistes tab = separation(chain);

    cout << "arranging the tab..." << endl;
    trier(tab);
    chain = suppressionTotale(tab);

}

//------------------- fin des fonction de monotonie --------------
//--------------------------------------------------------------------

//--------------------tests----------------------

int main(){

            /* ---- test Chainage --- */

     /* ------test : saisieNombre(), affCh()------*/
/*
        cout << "test saisieNombre(), affCh() : " <<endl;
        p_data head;
        head = saisieNombre(10); //input: copacabana. 
        affCh(head); //output: copacabana.
*/
     /* ------test : affCh(), saisieBorne()-----*/
/*
        cout << "test saisieBorne(), affCh() : " <<endl;
        p_data head;
        head = saisieBorne('a'); //input: copa
        affCh(head); //output: copa
*/  
     /* ------test : saisieNombre(), affCh(), nbCroissance()------*/
/*
        cout << "test saisieNombre(), affCh() : " <<endl;
        p_data head;
        head = saisieNombre(10); //input: copacabana. 
        affCh(head); //output: copacabana.

        int cpt = nbCroissance(head); 
        cout << endl << "nbmonotonies = " << cpt <<endl; // output: 5

*/
    /*------test extraireCroissance() ----- */
/*    
       p_data mono = (data*)malloc(sizeof(data)); 
        
        p_data head;
        head = saisieNombre(10); //input: copacabana. 

        extraireCroissance(head,mono);
        affCh(mono); // output: acop
        cout << "..." << endl;
        affCh(head);
*/
    
    /*------test p_data fusion(p_data prem, p_data sec) -----*/
/*    
        p_data pre = saisieNombre(3); // first chain
        p_data sec = saisieNombre(3); // second one 

        cout << "first chain " << endl; 
        affCh(pre); 
        cout << " " << endl; 
        cout << "second chain " << endl; 
        affCh(sec);
        cout << " " << endl; 
        cout << "fusion is in process..." << endl; 

        pre = fusion(pre,sec); 

        cout << "fusion done ! " << endl; 
        affCh(pre); 
*/

            /* ---- test Monotonies --- */

   /*------test initT(), ajouterFin(), affT(), suppressionFin(), suppressionTotale() -----*/
/*
        datalistes t1 = initT(4); // new tableau mono
        p_data chn1 = saisieNombre(3); // first element of tableau
        p_data chn2 = saisieNombre(2); // second one 
        p_data chn3 = saisieNombre(2); // third one
        cout << "add first element to table..." << endl;
        ajouterFin(chn1,t1);
        cout << "add second element to table..." << endl;
        ajouterFin(chn2,t1);
        cout << "add third element to table..." << endl;
        ajouterFin(chn3,t1);

        cout << "display tableau mono" << endl; 
        affT(t1);

        cout << "delete last element..." << endl; 
        p_data lastEle =  suppressionFin(t1); 
        cout << "display without the last element:" << endl; 
        affT(t1);
        cout << "display the last element:" << endl;
        affCh(lastEle);
        cout << "form complet chain..." << endl;
        p_data total = suppressionTotale(t1); 

        cout << "done! the chain:" << endl;
        affCh(total); 

        cout << "display tableau mono" << endl; 
        affT(t1);

        
*/
    /*------test separation(), trier()-----*/
/*
        p_data chain = saisieNombre(10);
        cout << "chain : " << endl;
        affCh(chain);

        datalistes tab = separation(chain);
        cout << "monotonies : " << endl;
        affT(tab);

        trier(tab);
        cout << "chain orderd : " << endl;
        affT(tab);
*/
    /*------test trierCh(): fonction principale-----*/ 

        p_data chain = saisieNombre(10);
        cout << "chain : " << endl;
        affCh(chain);

        trierCh(chain);
        cout << "the orderd chain :" << endl;
        affCh(chain);


}