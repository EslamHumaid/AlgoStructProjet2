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


p_data ajoutApres(DATATYPE uneval, p_data head){
    p_data nouveau;
    nouveau = (data*)malloc(sizeof(data));
    nouveau->valeur = uneval;
    nouveau->suiv = head->suiv;
    head->suiv = nouveau;

    return nouveau;



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

    for(int i=1 ; i< nb ; i++){
        cout << "valeur?" << endl;
        cin >> val;
       // head = ajoutApres(val,head);
        for (int j=1; j<i;i++) {

           head->suiv = 


        }

    }
    return head;
}



p_data saisieBorne(DATATYPE sentinelle){
    DATATYPE val;
    cout << "valeur de head ?" << endl;
    cin >> val;
    p_data head = (data*)malloc(sizeof(data)); 
    head->valeur = val;

    while(val != sentinelle){
        cout << "valeur?" << endl;
        cin >> val;
        ajoutApres(val,head);



    }
    return head;
}

int nbCroissance(p_data chain){
    p_data tmp = chain;
    int nbMonotonies = 0;

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
   cout << "test" <<endl;
   int cpt = nbCroissance(head);
   cout << "test" <<endl;
   cout << "nbmonotonies = " << cpt <<endl;





}