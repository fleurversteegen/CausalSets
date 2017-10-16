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
   double *pos = e.pos;           //points to the position of e
    Element * walker = root;                                       //walker points at the first element after the root element
  
    while (walker != NULL)
    {    double * pos_n = walker->pos;                            //pos_n will hold the position of a second element e_n which is a possible nearest neighbour. 
       
        if (walker->id != e.id )    //continue if the possible neighbour is not e
        {   
            
            int nrNN = e.nr_of_nn;                             //holds the nr of nearest neighbours of e
           
            int *near_neigh = e.near_neigh;                  //points to the nearest neighbours of e
           
            double ds = st.MetDist(pos, pos_n);                      //calculate the metric distance between the two points
          
            if(ds>=0)                                              //if lightlike/timelike separated
            {	         
                
              
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
    
  //  delete walker;
 
}



/*
vector<int>  Set :: M_Causal(ofstream &Output)
{  
   long int size = (*nrElem)*(*nrElem); 
   C.resize(size); 
   Element * walker = root;                            
    while (walker != NULL)                                 //loop over the elements in the set
    {
        NN(*walker, Output);    
        
        int row = (*nrElem) * ((*walker).id-1);                               //gives the position to look at given the row in the matrix 
       
        int column;
        for (int i = 0; i < ((*walker).nr_of_nn); i++)                         //as the matrix is represented as a 1dim array
        {
           // it = C.begin();
            column = (*walker).near_neigh[i]-1;             //for each nearest neighbour set the corresponding entry to 1   
            if(column + 1 > (*walker).id )                  //if the element is in the causal future               
            {
                C[column + row]=1;// = 1;
                     
            }
        } 
        walker = walker->next;
    }
 //   C = tmp;
    return C; 

}*/


vector<int>  Set :: M_Causal(ofstream &Output)
{  
   long int size =( (*nrElem)*(*nrElem) + (*nrElem))/2; 
   C.resize(size); 
   Element * walker = root;                            
  
  
   int row = 0;
   int column;
   int counter = *nrElem;
  
    while (walker != NULL)                                 //loop over the elements in the set
    {
        NN(*walker, Output);    
         
        for (int i = 0; i < (*walker).nr_of_nn; i++)                         //matrix is represented as a 1 dim array 
        {
          
            column = ((*walker).near_neigh[i]-1) - (*nrElem - counter +1);             //for each nearest neighbour set the corresponding entry to 1   
            
            if( (*walker).near_neigh[i] > (*walker).id )                  //if the element is in the causal future               
            {   
                C[column + row ]=1;
            }
        } 
    
        walker = walker->next;
        counter += -1;                                                       //Only store the right upper triangle of the matrix
        row  += counter;
        
    }

    return C; 

}




/*
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
                if(column + 1 > e.id )
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

*/


/*
vector<int> Set :: M_Link_2()
{   //long int size = (*nrElem)*(*nrElem);                           //set the size of the Causal and Link matrices
   // L.resize(size);                 
    
    int row;
    
        for (long int i = (*nrElem)*(*nrElem)-1; i >= 0; i--)  //loop over elements
         {  
             
             row = i/(*nrElem);
           
            if (C[i] == 1 and L[i]!=-1 and row!=0)                                  
            { 
                for(int k = 1; k <= row; k++)
                {
                    int diag = i - ( (i + *nrElem)%(*nrElem) - row );               // diagonal element at position [i,i]
                 
                    if (C[ diag - (*nrElem)*k ] == 1)                                //if element [i,j] is present at row i-k, s/t [i-k,i] = 1
                       {                                                             //then set [i-k,j] = 0
                           L[i  - (*nrElem)*k] = -1;                                 //set a flag for each element that needs to be set to 0 eventually
                       }
                           
                    else
                    {L[i - (*nrElem)*k] = C[i - (*nrElem)*k]; }    
                 }                          
              
            } 
            else if (L[i] == -1){L[i] = 0;}                                //set all the flags to 0 
            else {L[i] = C[i]; }
         }cout<<endl;
    

    return L;
}
*/

vector<int> Set :: M_Link()
{     
    long int size = (*nrElem)*(*nrElem); 
    L.resize(size); 
    
    int Csq;                                           //C^2 = Cl * Cr
    int row;
    int column;
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



/*
vector<int> Set :: M_Link()
{  // L = new int[(*nrElem)*(*nrElem)];
    //L = C
    //vector<int> tmp ((*nrElem)*(*nrElem),0);
    
    L.resize((*nrElem)*(*nrElem));
    int kmin;
    int kmax;
    
    for(int j = 0; j< (*nrElem); j++)                            //loop over rows
    {
        for (int i = j*(*nrElem); i < j*(*nrElem)+*nrElem; i++)  //loop over columns from right to left
         {//  L[i] = C[i];
            if (C[i] == 1 and L[i]!=-1)
            {    
                kmin=(*nrElem+1) * (i-j*(*nrElem));
                kmax=(*nrElem) * (i+1 -j*(*nrElem));
              //  cout<<*nrElem<<" "<<kmin<<" "<<kmax<<endl;
                for(int k = kmin; k < kmax; k++)                                 //check neighbours of element i
                {
                    if (C[k]  == 1)                                              //if element in between
                    {                                                            //set a flag at the neighbour of element i
                          L[i+(k -kmin)] = -1;                                   //if no flag then loop over i will set these 
                                                                                 //elements back to initial value
                                        
                    }      
                    else{L[i] = C[i]; }                                        //if no element in between                             
        
                }
              
            } else if (L[i] == -1){L[i] = 0;}                                //set all the flags to 0 
 
        }
    }
//    L = tmp;
    return L;
}
*/

//display the link and causal matrix
void Set :: display(vector <int> &Matrix)
{  

    int counter = 0;
    for(int j = 0; j< (*nrElem); j++)
    { 
        for(int i = j*(*nrElem); i < j*(*nrElem)+*nrElem; i++)
        { 
            if( i - j*( 1 + *nrElem ) <= 0)                     //print zeros for bottom half of matrix
                {cout<<0<<" ";}
            else
                {
                    cout<<Matrix[counter]<<" "; 
                    counter+=1;
                }
    
        }
        cout<<endl;
    }
  //  delete [] Matrix;
}




