#include<iostream>
using namespace std;


typedef char DATATYPE;

typedef struct _datum{
    DATATYPE valeur;
    _datum * suiv;
} data ;

typedef data * p_data;

void affCh(p_data chain){
    p_data tmp = chain;
    while(tmp != nullptr){
        cout << tmp->valeur;
        tmp = tmp->suiv;
    }
}

p_data ajoutFin(DATATYPE val, p_data head){
    p_data toAdd;
    toAdd = (data*)malloc(sizeof(data));
    toAdd->valeur = val;
    toAdd->suiv = nullptr;


    p_data tmp = head;

    while((tmp->suiv) != nullptr){    //doesnt work without ()
        tmp = tmp->suiv;

    }

    tmp->suiv = toAdd;
    
    return head;
    

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
            } else if ((tmpSec->valeur <= tmpPrem->valeur) && ((tmpSec->valeur <= (tmpPrem->suiv)->valeur)) ) { 

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

//////////////TOFIX////////////////// does not work for string
void extraireCroissance(p_data & chain, p_data & mono) {

    p_data tmp = clone(chain); // copy "valeur" and "suiv" of the head
    ajoutFin((tmp->valeur),mono);  // first element of the chaine will always be added to mono
    removeFirstEle(chain); // remove the head, second element in the chaine becomes the new head

    while( ( (tmp->suiv) != nullptr) && ((tmp->valeur) < (chain->valeur) ) ) { // to extract the first monotonie

        cout << (tmp->valeur) << " <  " << chain->valeur << endl;
        
        ajoutFin(chain->valeur,mono); //TOFIX
        tmp = clone(chain); //TOFIX

        removeFirstEle(chain);

        (tmp->suiv) = nullptr;
        
    }


}


//------------------------------------------
int main(){
 /*  p_data head;
   head = saisieNombre(3);
   affCh(head);
  
   int cpt = nbCroissance(head);

   cout << endl << "nbmonotonies = " << cpt <<endl;


//------test extraireCroissance(p_data & chain, p_data & mono) ----- 

p_data mono = (data*)malloc(sizeof(data)); 
mono->valeur='a'; 
mono->suiv=nullptr; 

extraireCroissance(head,mono);
affCh(mono);
cout << "..." << endl;
affCh(head);
*/

//------test p_data fusion(p_data prem, p_data sec) -----

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


}