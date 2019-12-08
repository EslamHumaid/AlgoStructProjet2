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


//------------------------------------------
int main(){
   p_data head;
   head = saisieNombre(10);
   affCh(head);
  
   int cpt = nbCroissance(head);

   cout << endl << "nbmonotonies = " << cpt <<endl;





}