//
//  func_1_1.h
//  DataStructureByForrest
//
//  Created by 小小延 on 10/05/2018.
//  Copyright © 2018 Forrest. All rights reserved.
//

#ifndef func_1_1_h
#define func_1_1_h

#include <iostream>

template<typename T>
inline void visit(T &c)
{
    std::cout << c << " ";
}

template<typename T>
inline bool EQ(T t1,T t2)
{
    return t1 == t2;
}

#endif /* func_1_1_h */
