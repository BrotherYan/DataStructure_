//
//  LinearList.h
//  DataStructureByForrest
//
//  Created by 小小延 on 10/05/2018.
//  Copyright © 2018 Forrest. All rights reserved.
//

#ifndef LinearList_h
#define LinearList_h

template <typename ElemType>
class LinearList {
private:
    int length;
    int maxSize;
    ElemType *list;
public:
    virtual void initList() = 0;
    virtual void destroyList() = 0;
    virtual bool listEmpty() = 0;
    virtual void clearList() = 0;
    virtual int listLength()const = 0;
    virtual bool getElem(int i, ElemType &e) const = 0;
    virtual int locateElem(ElemType e,  bool( * compare)(ElemType, ElemType))const = 0;
    virtual bool priorElem(ElemType curr_e, bool( * EQ)(ElemType, ElemType), ElemType &pre_e)  = 0;
    virtual bool nextElem(ElemType curr_e,bool( * EQ)(ElemType, ElemType), ElemType &next_e)  = 0;
    virtual bool listInsert(int i, ElemType e)  = 0;
    virtual bool listDelete(int i, ElemType &e)  = 0;
    virtual void listTraverse(void (*visit)(ElemType &L)) = 0;
};

#endif /* LinearList_h */
