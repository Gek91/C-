#include "SMatrix.h"

int main()
{
    Matrix<int>* m=new Matrix<int>(3,3);
    Matrix<int>* m2=new Matrix<int>(2,2);
    Matrix<int>* m3;
    try
    {
        vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);
        
        vector<int> v2;
        v2.push_back(4);
        v2.push_back(5);
        v2.push_back(6);
        
        vector<int> v3;
        v3.push_back(7);
        v3.push_back(8);
        v3.push_back(9);
        
        m->setRow(0,v1);
        m->setRow(1,v2);
        m->setRow(2,v3);
        
        m->printMatrix();
        
        SMatrix<int>* sm=new SMatrix<int>(3);
        sm->setRow(0,v1);
        sm->setRow(1,v1);
        sm->setRow(2,v1);
        sm->printMatrix();
        cout<<sm->trace()<<endl;

    }
    
    catch (const char* msg)
    {
        cerr<<msg<<endl;
    }
    catch(...)
    {
        cerr<<"Eccezzione non gestita"<<endl;
    }
    
    delete m;
    delete m2;
    delete m3;


    return 0;
}