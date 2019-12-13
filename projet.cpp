#include<iostream>
using namespace std;

/******* constants & structs ******/


typedef char DATATYPE;

//Chaînage
typedef struct _datum{
    DATATYPE valeur;
    _datum * suiv;
} data ;

typedef data * p_data;



//Monotonies
typedef struct _datallst {
    int capa ;
    int nbmono ;
    p_data * monotonies ;

} datalistes ;

/*******************************/


/*** function belong to Chaînage ***/

void affCh(p_data chain){
    p_data tmp = chain;
    while(tmp != nullptr){
        cout << tmp->valeur;
        tmp = tmp->suiv;
    }
    cout << "" << endl;
}

void ajoutFin(DATATYPE val, p_data & head){

    
  
    p_data toAdd;
    toAdd = (data*)malloc(sizeof(data));
    toAdd->valeur = val;
    toAdd->suiv = nullptr;



    if (head==nullptr) {

        head = toAdd; 

    } else { 

        p_data tmp = head;

        while((tmp->suiv) != nullptr){    //doesnt work without ()
            tmp = tmp->suiv;
        }

        tmp->suiv = toAdd;
        
        
    }   

}

void ajoutFinV2(DATATYPE val, p_data head){
    p_data toAdd;
    toAdd = (data*)malloc(sizeof(data));
    toAdd->valeur = val;
    toAdd->suiv = nullptr;


    p_data tmp = head;

    while((tmp->suiv) != nullptr){    //doesnt work without ()
        tmp = tmp->suiv;

    }

    tmp->suiv = toAdd;
    
    
    

}


p_data ajoutDevant(DATATYPE uneval, p_data chain){
    p_data nouveau;
    nouveau = (data*)malloc(sizeof(data));
    nouveau->valeur = uneval;
    nouveau->suiv = chain;

    return nouveau;



}

p_data saisieNombre(int nb){
    DATATYPE val;
    cout << "valeur de head ?" << endl;
    cin >> val;
    p_data head = (data*)malloc(sizeof(data)); 
    head->valeur = val;
    head->suiv = nullptr; 

    p_data tmp = head; // pour ne pas modifier le head

    for(int i=2 ; i<= nb ; i++){ // commence par la deuxieme valeur
        cout << "valeur?" << endl;
        cin >> val;

        tmp->suiv = (data*)malloc(sizeof(data)); 
        tmp->suiv->valeur = val; 
        tmp->suiv->suiv = nullptr;

        tmp = tmp->suiv; 

    }
    return head;
}



p_data saisieBorne(DATATYPE sentinelle){
    DATATYPE val;
    cout << "valeur de head ?" << endl;
    cin >> val;
    p_data head = (data*)malloc(sizeof(data)); 
    head->valeur = val;

    p_data tmp = head; // pour ne pas modifier le head

    while(val != sentinelle){
        cout << "valeur?" << endl;
        cin >> val;
        
        tmp->suiv = (data*)malloc(sizeof(data)); 
        tmp->suiv->valeur = val; 
        tmp->suiv->suiv = nullptr;

        tmp = tmp->suiv; 

    }
    return head;
}

int nbCroissance(p_data chain){
    p_data tmp = chain;
    int nbMonotonies = 1;  //car si toutes les lettres du mot sont en ordre croissante, on aura une seul grande monotonie ex: mot = abcd, monotonie croissante =  abcd = 1

    while(tmp->suiv != nullptr){

        if((tmp->valeur) >= (tmp->suiv)->valeur ){
            nbMonotonies++;

        }
        tmp = tmp->suiv;
    }

    return nbMonotonies;


}

void removeFirstEle(p_data & chain) { // remove first element of a chaine & return new head
    
    p_data exHead = chain; 
    chain = chain->suiv;
    free(exHead);

    }

p_data clone(p_data chain) { 

    p_data tmp = (data*)malloc(sizeof(data));
    tmp->valeur = chain->valeur; 
    tmp->suiv = chain->suiv; 

    return tmp;
}
/**
 * @algo: take an element from chain sec, then put it in the right place at chain pre.
 *        repreat the process for another element until chain sec's elements end. 
 * 
**/

p_data fusion(p_data prem, p_data sec) { 

    p_data restChain=sec; // variable conserve the chain after links are moved
    p_data tmpPrem = prem;
    p_data tmpSec = sec; 
   
    
    while (restChain != nullptr ) { 
            
        bool ok = true;
        tmpPrem = prem;
        tmpSec = restChain;

       while (tmpPrem != nullptr && ok ) { 

            if (((tmpPrem->suiv)==nullptr))  { // add to the end

                tmpPrem->suiv = tmpSec; 
                restChain = tmpSec->suiv;
                tmpSec->suiv = nullptr;
                ok = false; 

              // add in between  
            } else if ((tmpSec->valeur >= tmpPrem->valeur) && ((tmpSec->valeur <= (tmpPrem->suiv)->valeur))){ 

                restChain = tmpSec->suiv;
                tmpSec->suiv = tmpPrem->suiv;
                tmpPrem->suiv = tmpSec;
                ok = false; 
                // add at the beggining 
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

//////////////TOFIX////////////////// does not work for string//
//mono should have a value
void extraireCroissance(p_data & chain, p_data & mono) {

    p_data tmp = clone(chain); // copy "valeur" and "suiv" of the head
    
    ajoutFin((tmp->valeur),mono);  // first element of the chaine will always be added to mono
    
    removeFirstEle(chain); // remove the head, second element in the chaine becomes the new head

    while( ( (tmp->suiv) != nullptr) && ((tmp->valeur) < (chain->valeur) ) ) { // to extract the first monotonie

       
        
        ajoutFin(chain->valeur,mono); //TOFIX
        tmp = clone(chain); //TOFIX

        removeFirstEle(chain);

        

        

        
        
    }


}

/*** function belong to Monotonies ***/

datalistes initT(int nb) {

    datalistes newList;

    newList.capa = nb; // nb cases of tableau(used or no) = capa

    newList.nbmono = 0; // nb used cases is zero; 

    newList.monotonies = (p_data*)malloc(nb*sizeof(p_data)); // table contains pointers, so it's pointer toward pointers, (cf.exo3 tableaux dynamique)

    //initialising the tab cases     
    for(int j = 0 ; j < newList.capa ; j++ ){
        newList.monotonies[j] = nullptr;
    }
    
    
    return newList;
}
/**
* @algo: go to the last unused case whose indixe is nbmono (not (nbmono-1) cuz idixes here start with 0), then put chain in it.
* @PRE:
* @POST:
**/
void ajouterFin(p_data chain,datalistes & mono) {

    mono.monotonies[mono.nbmono] = chain; 

    mono.nbmono++; 


}

// each line represent a case
void affT(datalistes mono){

    for (int i=0;i<mono.nbmono;i++) {

        affCh(mono.monotonies[i]);
         

    }

}

/**
* @algo: delete has done by assigning to NULL (malloc intialise to NULL)
* @PRE: 
*  @POST:
**/
p_data suppressionFin(datalistes & mono) {
    int indexeLastEle = mono.nbmono-1;
    p_data lastEle = mono.monotonies[indexeLastEle]; 

    mono.monotonies[indexeLastEle] = NULL; // malloc intialise to NULL
    mono.nbmono--;

    return lastEle; 

}
// misleading name of a function, it's forming a chain not deleting them from the tableau 

/**
 * @algo: associate first elem with the second one then second with third...n with n+1, so it's nbmono-2 turns
 * @PRE:
 * @POST:
 * */
p_data suppressionTotaleV2(datalistes & mono) {

p_data Head = mono.monotonies[0]; // first element

    for (int i=0;i<(mono.nbmono-1);i++) { 

        mono.monotonies[i]->suiv = mono.monotonies[i+1];

    }

    return Head; 

}
p_data suppressionTotale(datalistes & mono) {   //working as intended

    p_data tmp;
    p_data chain;
    for (int i=1;i<(mono.nbmono);i++) { 

        tmp = mono.monotonies[0];
        while(tmp->suiv != nullptr){
            tmp = tmp->suiv;
        }

        tmp->suiv = mono.monotonies[i];


    }

    chain = mono.monotonies[0];

    for(int i = 0 ; i < mono.nbmono; i++){       //remove the elements from mono
        mono.monotonies[i] = nullptr;
        mono.nbmono--;

    }

    return chain; 

}


//fonctions belonging to Fusion multiple part


/**
 * @algo: return a tableau with the cases filled with the monotonies of chain
 * @PRE:
 * @POST:
 * */
datalistes separation(p_data & chain){
    int nbCases = nbCroissance(chain);
    datalistes tab = initT(nbCases);
    



    for(int i = 0 ; i < nbCases ; i++ ){
        
        extraireCroissance(chain, tab.monotonies[i]);
        tab.nbmono++;
    }

    return tab;

}


/**
 * @algo: put the fusion of all elements of a tab in the first case orderd by croissant order
 * @PRE:
 * @POST:
 * */
void trier(datalistes & tabmono){

    for(int i = 1 ; i < (tabmono.nbmono); i++){
        tabmono.monotonies[0] = fusion(tabmono.monotonies[0], tabmono.monotonies[i]);

    }

    tabmono.nbmono = 1;
}


/**
 * @algo: return the chain order by croissant order
 * @PRE:
 * @POST:
 * */
void trierCh(p_data & chain){
    cout << "separating monotonies..." << endl;
    datalistes tab = separation(chain);
    cout << "arranging the tab..." << endl;
    trier(tab);
    chain = suppressionTotale(tab);

}


//------------------------------------------
int main(){
 /*  p_data head;
   head = saisieNombre(5);
   affCh(head);

   p_data mono = new data; 
   mono->valeur = "a";
   mono->suiv = nullptr;

   extraireCroissance(head, mono);
   
   affCh(mono);
   affCh(head);
  
int cpt = nbCroissance(head);

cout << endl << "nbmonotonies = " << cpt <<endl;
*/

//------test extraireCroissance(p_data & chain, p_data & mono) ----- 
/*
p_data mono = (data*)malloc(sizeof(data)); 
mono->valeur='a'; 
mono->suiv=nullptr; 

extraireCroissance(head,mono);
affCh(mono);
cout << "..." << endl;
affCh(head);

*/
//------test p_data fusion(p_data prem, p_data sec) -----
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
//---- test Monotonies --- 
// datalistes t1 = initT(4); // new tableau mono
// p_data chn1 = saisieNombre(3); // first element of tableau
// p_data chn2 = saisieNombre(2); // second one 
// p_data chn3 = saisieNombre(2); // third one
// cout << "add first element to table..." << endl;
// ajouterFin(chn1,t1);
// cout << "add second element to table..." << endl;
// ajouterFin(chn2,t1);
// cout << "add third element to table..." << endl;
// ajouterFin(chn3,t1);

// cout << "display tableau mono" << endl; 
// affT(t1);

// cout << "delete last element..." << endl; 
// p_data lastEle =  suppressionFin(t1); 
// cout << "display without the last element:" << endl; 
// affT(t1);
// cout << "display the last element:" << endl;
// affCh(lastEle);
// cout << "form complet chain..." << endl;
// p_data total = suppressionTotale(t1); 

// cout << "done! the chain:" << endl;
// affCh(total); 

// cout << "display tableau mono" << endl; 
// affT(t1);

p_data chain = saisieNombre(10);
cout << "chain : " << endl;
affCh(chain);
// datalistes tab = separation(chain);
// cout << "monotonies : " << endl;
// affT(tab);
// trier(tab);
// cout << "chain orderd : " << endl;
// affT(tab);
trierCh(chain);
cout << "the orderd chain :" << endl;
affCh(chain);

// p_data head = nullptr;

// head = ajoutFin('a',head);

// affCh(head); 
}