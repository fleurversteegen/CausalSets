#ifndef SET_H
#define SET_H
# include "spacetime.h" 
# include "elements.h"
# include <vector>
using namespace std;

class Set 
{
private:    
       long int * nrElem;         //pointer to the nr of elements present in the set
       Element *root, *tail;
      
    
    int *near_neigh;       //points to the id's of the nearest neighbours of a set
    Spacetime st;         //spacetime the set is build from
  

vector <int> C;          //Causal matrix represented as 1dim array

vector <int> L;          //Link matrix represented as 1dim array

public:
                //array that holds the elements in the set
    Set(Spacetime);     //construct a set based on a spacetime with a fixed nr of elements --> this is where the sprinkling should go

    ~Set();

    long int *GetNrElem();           //get the nr of elements present in the set

    void AddElem(Element& );    // add a new element to the set
    
    void NN(Element&, ofstream& ); // finds the nearest neighbours of an element
    
    Element *GetRoot();
  //  static void display(Element *);
    
    vector<int> M_Link();
   // vector<int> M_Link_2();
    vector<int>  M_Causal(ofstream&);
    void display(vector<int>& );
    
};
#endif
