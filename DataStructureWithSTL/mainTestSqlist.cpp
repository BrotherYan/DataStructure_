'æ//
//  main.cpp
//  DataStructureByForrest
//
//  Created by 小小延 on 10/05/2018.
//  Copyright © 2018 Forrest. All rights reserved.
//

#include <iostream>
#include "SqlList.h"
int main(int argc, const char * argv[]) {
    SqlList<int> a;
    int i ;
    for(  i = 1 ; i <= 20; i++)
        
        a.listInsert(i, i/4);
    a.listTraverse(visit);
    a.listDelete(10, i);
    std::cout<<"delete operation:"<<std::endl;
    a.listTraverse(visit);
    
    findX(a, 0);
    a.listTraverse(visit);
    std::cout<<"find a element "<<a.locateElem(2, EQ) << std::endl;
    
    std::cout<<"deleteRangeX "<<std::endl;
    ListDeleteRangeX<int>(a, 2, 3);
    a.listTraverse(visit);
    std::cout<<"listDelteDuplicate(a) "<<std::endl;
    listDelteDuplicate(a);
    a.listTraverse(visit);
    return 0;
}



