#ifndef ELEMENT_H
#define ELEMENT_H

using namespace std;

struct Element
{   

    double * pos;    // holds the position of the element in the grid
    int * near_neigh;  // holds an array of nearest neighbours
    int  nr_of_nn;
    int id,d, vol;
    Element *next;
    


    Element():id(0),next(0),pos(0),d(0)
    {    
      //  nr_of_nn=new int;
        vol = 0;
        nr_of_nn = 0;
        near_neigh = new int[nr_of_nn+1];
    }

 //Element constructor. Constructs an element and gives it an id, position and dimension

     Element(int _id, double *_pos, int _d) : id(_id), d(_d), next(NULL)
    {   
        pos = new double[d];
        for(int i = 0; i<d; i++)
        {
            pos[i] = _pos[i];
            
        }
        
        nr_of_nn = 0;
        near_neigh = new int[nr_of_nn+1];
        vol = 0;
       // cout<<id<<endl;
    }
    
    Element (Element *e)
    {
        Element(e->id, e->pos, e->d );
        
    }
    
    ~Element()
    {
       delete near_neigh, pos;
    }
    
   // Element *Next(){return next;}
   // Element *Prev(){return prev;}

 
/*

//sets the nr of nearest neighbours to newnr
    void SetNr_of_nn(int newnr)
    {
        nr_of_nn = newnr;
    }
    
//updates the ids of nearest neighbours
    void SetNearNeigh(int * ids)
    {
        delete[] near_neigh;
       
        int *near_neigh = new int[nr_of_nn];
        
        for(int i =0; i<nr_of_nn; i++)
        {
            *(near_neigh +i) = ids[i];
        }
    }    
    
    
        
//return the nr of nearest neighbours    
    int GetNrNN()
    {
        return nr_of_nn;
    }
    
    


//Return the element's position in spacetime
    int* GetPos()
    {   
       return position;        
    }
    

//Return the element's id
    int GetId()
    {
        return id;
    }

//return the element's dimension
    int GetDim()
    {
        return d;
    }

//return the volume of the element. ie a planck volume    
    int GetVol()
    {
        return vol;
    }        

//return a pointer to the ids of the nearest neighbours    
    int * GetNearNeigh()
    {
        
        return near_neigh;
    }
    
//sets the volume of an element. ie a planck volume
    void SetVol(int _vol)
    {
        vol = _vol;
    }
    */


};
#endif
