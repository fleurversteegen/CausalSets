# include <iostream>
# include <cstdlib>
# include <fstream>
# include "set.h"


using namespace std;

//CONSTRUCTOR
//Create a set based on the spacetime _st and with nr of elements _nrElem

Set :: Set(Spacetime _st) : st(_st)
{
    
    root = NULL;               //declare a root ("dummy") element and a tail element of the singly list of elements 
    tail = NULL;
    nrElem = new long int;         //allocate space for the pointer that holds the nr of elements
    *nrElem = 0;                   //initialize the nr of elemnts to 0
}


//DESTRUCTOR
Set :: ~Set()                      
{
    Element *tmp = root;
    while(tmp) 
    {
        root = tmp->next;
        delete tmp;              //delete the next node in the linked list of elements
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
    {   
        tail->next = tmp;    
        tmp->prev = tail;    
        tail = tail->next; 
    }
    
    *nrElem+=1;
    
}


//returns the nr of elements in the set
long int * Set :: GetNrElem(){ return nrElem; }


//returns the pointer to the root element of the set
Element * Set :: GetRoot(){ return root; } 
//returns the pointer to the tail element of the set
Element * Set :: GetTail(){ return tail; } 
//returns the pointer to the nth element of the set
Element * Set :: GetNode(int n)
{
    if (n > *nrElem/2)
    {
        Element * walker = tail;
        while ((*walker).id != n)
        {
            walker = walker->prev;
        }
    }
    
    else
    {
        Element * walker = root;
        while ((*walker).id != n)
        {
            walker = walker->next;
        }
    }
    return walker;
}
/*
//sets the ID's of the nearest neighbours of an element e
void Set :: NN(Element &e, ofstream &Output)
{
   double *pos = e.pos;                                           //points to the position of e  
   double * pos_n;
   Element * walker = root;                                       //walker points at the first element after the root element
   double ds;
   try
   {
       (e.near_neigh).reserve(*nrElem);
   }
   catch(const std::bad_alloc& ex)
   {
     cout<<"ERROR: NO MORE RAM!"<<endl;
     exit(0);
   }
   
    while (walker != NULL)
    {    pos_n = walker->pos;                            //pos_n will hold the position of a second element e_n which is a possible nearest neighbour. 
       
        if ((*walker).id != e.id )                        //continue if the possible neighbour is not e itself
        { 
            ds = st.MetDist(pos, pos_n);                      //calculate the metric distance between the two points
          
            if(ds>=0)                                              //if lightlike/timelike separated
            {	  
                (e.near_neigh).push_back(walker->id);              //add a new ID to the array of nearest neighbours
                e.nr_of_nn += 1;                                   // increase the nr of neighbours by 1
            }
        }
        walker = walker->next;                                    //go to the next element in the set
    } 
}
*/

//sets the ID's of the nearest neighbours of an element e
void Set :: NN(Element &e, ofstream &Output)
{
   double *pos = e.pos;                                           //points to the position of e  
   double * pos_n;
   Element * walker = root;                                       //walker points at the first element after the root element
   double ds;
   
   for (int i = 0; i<e.id-1; i++)
   {
       walker = walker->next;                                    //Only interested in the neighbours that lie in the future
   }
  
 
    while (walker != NULL)
    {    pos_n = walker->pos;                                    //pos_n will hold the position of a second element e_n which is a possible nearest neighbour. 
          
        if ((*walker).id != e.id )                               //continue if the possible neighbour is not e itself
        { 
           
            ds = st.MetDist(pos, pos_n);                         //calculate the metric distance between the two points
          
            if(ds>=0)                                              //if lightlike/timelike separated
            {	
                (e.near_neigh).push_back(walker->id);              //add a new ID to the array of nearest neighbours
                e.nr_of_nn += 1;                                   // increase the nr of neighbours by 1
            
            }
        }
        walker = walker->next;                                    //go to the next element in the set
    } 
}



//Causal matrix

vector<int>  Set :: M_Causal(ofstream &Output)
{  
   int size =((*nrElem - 1)*(*nrElem - 1) + (*nrElem - 1))/2; 
  
   C.resize(size); 
  
   Element * walker = root;                            
   int row = 0;
   int column;
   int counter = *nrElem;
  
    while (walker != NULL)                                                    //loop over the elements in the set
    {
        NN(*walker, Output);    
       
        for (int i = 0; i < (*walker).nr_of_nn; i++)                                      //matrix is represented as a 1 dim array. Only the bottom half is stored
        {
            column = ((*walker).near_neigh[i]-1) - (*nrElem - counter +1);                
            
            if( (*walker).near_neigh[i] > (*walker).id )                              //if the element is in the causal future               
            {  
                C[column + row ]=1;                                                  //for each nearest neighbour set the corresponding entry to 1
            }
        } 

        walker = walker->next;      
        counter += -1;                                                       //Only store the right upper triangle of the matrix
        row  += counter;
    }
     
    return C; 
}

//Link Matrix
vector<int> Set :: M_Link()
{     
    int size =((*nrElem - 1)*(*nrElem - 1) + (*nrElem - 1))/2; 
    L.resize(size); 
   
    int Csq, max;                                           
    int row=0;
    int column;
    int cnt = *nrElem - 1;

 
        for (int i = 0; i < size; i++)                    //loop over elements in Causal matrix
        {
            Csq = 0;
            max = row;
            column = i - 1 + cnt;
           
            if(i == row)
            {   
                max++;
                column += cnt - 1 - (max - row);
            }
            else
            {
                while(max < i)
                {
                    if(C[i]!=0)                             //if Element i is a neighbour
                    {
                        Csq += C[max] * C[column];          //calculate the square of the causal matrix
                    }
                    max++;
                    column += cnt - 1 - (max - row);        //update column
                }        
                 
            }  
        
            row += cnt*((column+1)/size);                   //update row
            cnt += -((column+1)/size);
           
            if (Csq > 0)                                 //if the square of the causal matrix > 0, then the neighbour is not a nearest neighbour
            {     
                 L[i] = 0;//C[i] - 1;
            }
            else                                        //the neighbour is a nearest neighbour
            {
                L[i] = C[i];
            }
      }
     
    return L;
}




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

}




