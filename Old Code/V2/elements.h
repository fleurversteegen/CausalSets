#ifndef ELEMENT_H
#define ELEMENT_H
# include <vector>

using namespace std;



struct Element
{   

    double * pos;             // holds the position of the element in the spacetime
    vector <int> near_neigh;  // holds a vector of 
    int  nr_of_nn;
    int id,d;
    Element *next, *prev;
    

//CONSTRUCTOR
//Constructs a element and sets it's default values to 0
    Element():id(0),pos(0),d(0), next(NULL),prev(NULL), nr_of_nn(0)
    {         
          
    }

 //CONSTRUCTOR
 //Constructs an element give an id, position and spacetime dimension

    Element(int _id, double *_pos, int _d) : id(_id), d(_d), next(NULL), prev(NULL), nr_of_nn(0)    
    {   
        pos = new double[d];
        for(int i = 0; i<d; i++)
        {
            pos[i] = _pos[i];
            
        }                  
        
    }
//COPY CONSTRUCTOR
//Copies an element 
    
    Element (Element *e)
    {
        Element(e->id, e->pos, e->d );
      //  next = NULL;
    }


//DESTRUCTOR    
    ~Element()
    {
       delete [] pos;    
    }
    



};
#endif
