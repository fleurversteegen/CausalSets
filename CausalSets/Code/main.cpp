# include <iostream>
# include <cstdlib>
# include <fstream>
# include "spacetime.h" //Contains declarations of the spacetime
# include "elements.h" //Contains declaration of an element
# include "set.h"
# include <ctime>
# include <math.h>
using namespace std;
int dt, dx, dy, dz;

/*
int recurse(int *p, int current, int d) { 
  if (current==d) { 
    cout << "Current value: "; 
    
    for (int i=0;i<d;i++) 
    {cout << p[i] << " ";} 
    cout <<endl; 
  } 
  else { 
    for (p[current]=0; p[current]<d; p[current]++) { 
      p[current]++;
      recurse(p, current+1,d); 
    } 
  } 
} 
*/


//TODO:in the if statement, -0.5 * L_pl ???


//recursively loop over the spatial coordinates and select elements according to the Poisson distr.
void SprinkleRec(int * p, int d, int dim, int max, float prob, Set& set, ofstream& Output )
{  
    
    double r;
    if(dim == d)
    { //  cout<<p[0]<<" "<<p[1]<<endl;
        r = ((double) rand() / (RAND_MAX));              //create random nr
        
        if(r < prob)                                     //if smaller than prob of finding an element, then add an element
           {                 
               double *pos = new double[d];
               for (int j = 0; j < d; j++)
                    {
                        *(pos + j) = (*(p + j) - 0.5)+((double) rand() / (RAND_MAX));      //randomly place the element in the region assigned to point p
                    }              
               Element e(*set.GetNrElem()+1, pos, d); 
               set.AddElem(e);
               
               //cout<< r<<endl;
               Output <<pos[0]<<" "<<pos[1]<<endl;
               
               delete pos;
              
                              
                  
                }  
             
    }
   else
   { 
       for(p[dim] = -max; p[dim]<=abs(max); p[dim]+=2)       //loop over values x,y,z,... that are allowed by the diamont shape patch        
       {
           SprinkleRec(p, d, dim+1, max, prob, set, Output); 
           
       }
   }
 }




//Builds a Set 'set' by sprinkling a diamont type patch of the Spacetime 'mink'
void Sprinkle(Spacetime mink, Set &set, ofstream& Output)
{ 
    
    
    int d = mink.d;
    int N = mink.N;
    int t;
    int * point = new int [d];
    float prob = mink.Prob();                         //the probability of finding one element in a fixed volume element (poisson distr.)
    cout<<prob<<endl;
    for (t = -N ; t <= N; t++)                        //N is scaled up by a factor 2L_pl wrt its physical size for convenience
    {        
        *point = t;                                 //1st coord of a spacetime point
    
         SprinkleRec(point, d,1, -abs(t)+ N, prob, set, Output);   //recursively loop over the spatial dimensions, given the maximum value of -abs(t)+N 
                                                    //for the spatial dimensions. (due to the diamont shape)
    }
    delete [] point;
}





int main()
{
  
    int metric[] = {1,-1,-1,-1};
    int L = 4;
    int d = 2;
    float rho = 1;
  
    //Element *temp = new Element(e);
    //temp->next = e2;
    //cout<<e->id<<endl;
    Spacetime st(L, rho, metric, d);
    Set S(st);
    
   // test(S);
    //cout<<S.GetRoot()->id<<endl;
    //S.AddElem(e);
    //cout<<(*(S.GetRoot())).id<<endl;
    //cout<<S.GetRoot().id<<endl;
   // cout<<S.GetRoot()<<endl;
    //S.AddElem(e2);
   // S.AddElem(e3);
   // S.AddElem(e4);
   // cout<<S.GetRoot()->next->id<<endl;
    
    ofstream Output;
//    Output.open("data2.dat");
    ofstream Output2;
//    Output2.open("neighbours.dat");
    clock_t begin = clock();
    Sprinkle(st, S, Output);
//    cout<<(L-1)*(L-1)<<" - " << sqrt((L-1)*(L-1))<<" = "<<(L-1)*(L-1) - sqrt((L-1)*(L-1))<<" and 0.37x(L-1)*(L-1) = "<<0.37*(L-1)*(L-1) <<" vs "<<*S.GetNrElem();
    vector <int> C = S.M_Causal(Output2);
    
    
    //vector <int> Link = S.M_Link();
  
    S.display(C);
   // cout<<endl;
    //S.display(Link);  
   // cout<<endl; 
   
   
   
   
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"elapsed time: "<<elapsed_secs;
//    Output.close();
//    Output2.close();
   // long int nrElem = *S.GetNrElem();
  //  cout<<(nrElem)*(nrElem)<<endl;
  //  S.NN(*S.GetRoot());
    //cout<<S.GetRoot()->next->pos[1];
       //int p[4] = {0,0,0,0};
   //  SprinkleRec(p, 4, 1, 5, 0.1, S );
   
    //test(4,2,p,0);
   // recurse(p,0,3);
    //cout<<S.GetRoot()->id<<endl;
    cout<<*S.GetNrElem()<<endl;
    
//    cout<<S.GetRoot()->next->id<<endl;
   // cout<<*S.GetNrElem()<<endl;
   // Element *w =S.GetRoot();
   // Element *u =S.GetRoot()->next;
    //cout<<w->next->next->id<<endl;
   
  //  S.NN(*w);
   // S.NN(*u);
    //cout<<(*u).nr_of_nn;
   // cout<<u->next->id;
   // S.NN(*w->next->next);
   // cout<<*S.GetNrElem();
  //  cout<<(*w->next).nr_of_nn<<endl;
  //  int * c = w->near_neigh;
  //  int * f = u->near_neigh;
   // int * e = w->next->next->near_neigh;
   // cout<<(*w->next).nr_of_nn;
    /*for(int i =0; i<(*w).nr_of_nn; i++)
    {
        cout<<*(c + i)<<endl;
    }*/
 
   //delete [] C;
   //delete [] Link;

  
   //cout<<w->id<<endl;
   // while (w != NULL)
   // {
   //   cout<<w->id<<endl;
   //   w = w->next;
   // }
    //cout<<*S.GetNrElem()<<"bla";
    //st.Prob();
    //
    //Element *w = S.GetWalker();
    //cout<<w->id<<endl;
    //cout<<"bla"<<*S.GetNrElem()<<endl;
    
    
    //S.NN(e);
    
   // cout<<w->next->id<<endl;
    
   // cout<<*S.GetNrElem();
   /* //Element *p = &e;
    
    
   
    S.NN(e);
    //cout<<walker->id<<endl;
    
     
 //   cout<<w;
    

    
    
    Element *root, *walker;
    root = new Element;
    root->next = 0;
    root->prev = 0;
    root->id = 0;
    walker = root;
    
    walker->next = new Element(1,coord,4);
    walker = walker->next;
    walker->next= new Element(2,coord2,4);
    walker = walker->next;
    walker->next= walker->next= new Element(3,coord3,4);
    walker = walker->next;
    walker->next= new Element(4,coord4,4);
    
    walker = walker->next;
    walker->next = 0;
    cout<<walker->prev;*/
    
    
    //int ids[] = {1,2,3,4};
    //int ids2[] = {1,2,3,4,5};
    //e->SetNr_of_nn(4);
    //cout<<e->GetNr_of_nn()<<endl;   
    //e->SetNearNeigh(ids);
    //e->SetNr_of_nn(5);
    //cout<<e->GetNr_of_nn()<<endl; 
    //e->SetNearNeigh(ids2);
    //
    //int * nn = e.near_neigh;//GetNearNeigh();
    //cout<<nn[0]<<endl;
    //int * a = S.NN(e);
    /*cout<<"nearest neighbours of "<<e->GetId()<<" are "<<endl;
    for(int i =0; i<(e->GetNr_of_nn()); i++){
    cout<<*(nn+i)<<" ";
    }*/
    
    //int metric[4] = {1,-1,-1,-1};
   // cout<<sizeof(metric)<<endl;
    //int length = 20;
    //Spacetime M(length, metric, 4);
   // M.MetDist(coord);
}
