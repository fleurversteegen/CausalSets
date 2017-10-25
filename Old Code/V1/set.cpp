# include <iostream>
# include <cstdlib>
# include <fstream>
# include "set.h"


using namespace std;

//Create a set based on the spacetime _st and with nr of elements _nrElem

Set :: Set(Spacetime _st) : st(_st)
{
    
    root = NULL;               //declare a root ("dummy") element and a tail element of the singly list of elements 
    tail = NULL;
    nrElem = new int;         //allocate space for the pointer that holds the nr of elem
    
}

Set :: ~Set()
{
    delete nrElem;
    Element *tmp = root;
    
    while(tmp) 
    {
        root = tmp->next;
        delete tmp;
        tmp = root;
    }
}




//Adds element to Set
void Set :: AddElem(Element &e)
{ 
  
   Element *tmp =new Element(e.id, e.pos, e.d);       //create a tmp element from the new element
    if (root == NULL)                                 //if list has not been created
    {                                                 //set the beginning and end to point at the new element
      root = tmp;
      tail = tmp; 
                        
    }
    
    else                                             //set the pointer of the next element equal to the new element
    {                                                //move the tail up by one element
        tail->next = tmp;        
        tail = tail->next; 
    }
    
    *nrElem+=1;
    
}


//returns the nr of elements in the set
int * Set :: GetNrElem(){ return nrElem; }


//returns the pointer to the root element of the set
Element * Set :: GetRoot(){ return root; } 


//sets the ID's of the nearest neighbours of an element e
void Set :: NN(Element &e, ofstream &Output)
{
    
    double *pos = e.pos;                                              //points to the position of e
    
    Output<<pos[1]<<" "<<pos[0]<<endl;
    Output<<endl;
    long int size = (*nrElem)*(*nrElem);                           //set the size of the Causal and Link matrices
    C.resize(size);                                                //resize the Causal matrix
    L.resize(size);                                                //resize the Link matrix
    Element * walker = root;                                       //walker points at the first element after the root element
    int row = (*nrElem) * (e.id-1);
    while (walker != NULL)
    {    double * pos_n = walker->pos;                            //pos_n will hold the position of a second element e_n which is a possible nearest neighbour. 
        int column = (*walker).id - 1;           
        if (walker->id != e.id )    //continue if the possible neighbour is not e
        {   
            
            int nrNN = e.nr_of_nn;                             //holds the nr of nearest neighbours of e
           
            int *near_neigh = e.near_neigh;                  //points to the nearest neighbours of e
           
            double ds = st.MetDist(pos, pos_n);                      //calculate the metric distance between the two points
          
            if(ds>=0)                                              //if lightlike/timelike separated
            {	
                Output<<pos_n[1]<<" "<<pos_n[0]<<endl;       
              //  cout<<(*walker).id<<endl;
                if(column + 1 > e.id )                             //fill the Causal matrix
                {C[column + row] = 1;}
              
                int *newNN = new int[nrNN+1];                                   //add a new ID to the array of nearest neighbours
                             
                for(int i = 0; i<e.nr_of_nn; i++)                  //copy the current array of nearest neighbours to a new array
                {newNN[i] = e.near_neigh[i] ;
                                            }                  //set the new array equal to the current array
               e.nr_of_nn += 1;
               newNN[nrNN] = walker->id;                        //add a new id to the new array of nearest neightbours
               delete [] e.near_neigh;                          //delete the old array
               e.near_neigh = newNN;                       
            }
        }
        walker = walker->next;                               //go to the next element in the set
               
    } 
    Output<<endl;
      
  //  delete walker;
 
}

vector<int>  Set :: M_Causal(ofstream &Output)
{
    
   
    Element * walker = root;                            
    while (walker != NULL)                                 //loop over the elements in the set
    {
        NN(*walker, Output);  
        walker = walker->next;
    }

    return C;
}



vector<int> Set :: M_Link()
{     
    int Csq;                                           //C^2 = Cl * Cr
    int row;
    int column;
    //cout<<*nrElem<<endl;
        for (int i = 0; i < (*nrElem)*(*nrElem); i++)  //loop over elements in Cl matrix
        {   
            row = i/ (*nrElem);                        //row in the Cl matrix to be multiplied by the column in the Cr matrix
            column = (i + *nrElem)%(*nrElem);          //column in the Cr matrix
            Csq = 0;
            if (C[i] !=0 )
            {
                for (int j = 0; j < (*nrElem); j++)        // loop over elements in the row and column of Cl and Cr respectively
                    {
                        Csq += C[row * (*nrElem) + j] * C[column +j * (*nrElem)];
                   
                    }
            }
            else
            {
                Csq = 0;
            }
            if (Csq > 0)
                {
                    L[i] = C[i] - 1;                         //L_ij = C_ij - (C^2)_ij where if (C^2)_ij > 0, the ij entry is set to 1 
                }
            else
                {
                    L[i] = C[i];
                }
        }
    return L;
}


//display the link and causal matrix
void Set :: display(vector <int> &Matrix)
{  
    for(int j = 0; j< (*nrElem); j++)
    { 
        for(int i = j*(*nrElem); i < j*(*nrElem)+*nrElem; i++)
        {
            cout<<Matrix[i]<<" ";
    
        }
        cout<<endl;
    }
  //  delete [] Matrix;
}




