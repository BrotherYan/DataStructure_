//
//  SqlList.h
//  DataStructureByForrest
//
//  Created by 小小延 on 10/05/2018.
//  Copyright © 2018 Forrest. All rights reserved.
//

/**********************
 1.主要特点：随机访问。即，通过首地址和索引寻找，时间为 O(1)
 2.插入操作：平均 O(n)
 3.删除操作：平均 O(n)
 4.按值查找：平均 O(n)
 **********************/
#ifndef SqlList_h
#define SqlList_h
#define InitSize 100

#include "LinearList.h"
#include "func_1_1.h"
#include "C.h"

template <typename ElemType>
class SqlList:
public LinearList<ElemType> {
private:
    int maxSize;
    int length;
    ElemType *List;
public:
    SqlList()
    {
        List = new ElemType[InitSize];
        length = 0;
        maxSize = InitSize;
    }
    
    SqlList(const SqlList &L)
    {
        this-> length = L.length;
        this-> maxSize = L.maxSize;
        List = new ElemType[maxSize];
        assert(List != NULL);
        for (int j=0; j < maxSize; j++) {
            List[j] = L.List[j];
        }
    }
    
    SqlList& operator = (const SqlList &L)
    {
        if (this != &L)
        {
            length = L.length;
            maxSize = L.maxSize;
            if(List != NULL)
                delete [] List;
            List = new ElemType[maxSize];
            assert(List != NULL);
            for (int j=0; j < maxSize; j++) {
                List[j] = L.List[j];
            }
        }
        return *this;
    }
    
    ~SqlList()
    {
        delete [] List;
    }
    
    void initList()
    {
        length = 0;
    }
    
    void destroyList()
    {
        delete [] List;
    }
    
    bool listEmpty()
    {
        return length == 0;
    }
    
    void clearList()
    {
        length = 0;
    }
    
    int listLength() const
    {
        return length;
    }
    
    bool getElem(int i, ElemType &e) const
    {
        if ( i < 0 || i >= length ) return false;
        e = * (List + i);
        return true;
    }
    
    int locateElem(ElemType e,  bool( * EQ)(ElemType, ElemType))const
    {
        int i = 0;
        while ( i<length && !EQ(e,List[i])) i++;
        if ( i < length )
            return i+1;
        return -1;
    }
    
    bool priorElem(ElemType curr_e, bool( * EQ)(ElemType, ElemType), ElemType &pre_e)
    {
        int i = locateElem(curr_e,  EQ);
        if (i == -1)
            return false;
        else
        {
            pre_e = * (List+i-1);
            return true;
        }
    }
    
    bool nextElem(ElemType curr_e, bool( * EQ)(ElemType, ElemType), ElemType &next_e)
    {
        int i = locateElem(curr_e, EQ);
        if (i == -1 || i == length - 1)
            return false;
        else
        {
                next_e = *(List + i + 1);
                return true;
        }
    }
    
    bool listInsert(int i, ElemType e)
    {
        // 表元素序号从1开始，而在第n+1个位置插入相当于在表尾追加。
        i--;
        ElemType *newbase, *p, *q;
        if( i<0 || i>length) return false;
        if(length == maxSize)
        {
            newbase = new ElemType[maxSize * 2];
            assert (newbase != NULL);
            for (int j=0; j<length; j++)
            {
                newbase[j] = List[j];
            }
            delete [] List;
            List = newbase;
            maxSize *= 2;
        }
        
        p = List + i ;
        q = List + length - 1;
        for ( ; q >= p ; q-- )
        {
            // 插入后所有在第i个之后的元素往后移动一个位置。
            * (q+1) = * q;
        }
        *p = e;
        length ++;
        return true;
    }
    
    bool listDelete(int i, ElemType &e)
    {
        i--; //表元素序号从1开始，对应存储序号为 i-- 
        if ( i<0 || i>length) return false;
        ElemType *q, *p;
        p = List+i;
        e = *p;
        q = List + length - 1;
        for (p++; p<=q; p++) {
            *(p-1) = *p;
        }
        length --;
        return true;
    }
    
    void listTraverse(void (*visit)(ElemType &L));
    
    /************** EXCERCISES ****************/
    template <typename T>
    friend bool listDelete1 (SqlList<T> &L, T &e);
    template <typename T>
    friend bool ListDeleteRangeX(SqlList<T> &L, T s, T t);
    template <typename T>
    friend void ListReverse(SqlList<T>  &L);
    template <typename T>
    friend void ListDeleteAllX(SqlList<T> &L, T value);
    template <typename T>
    friend bool ListDeleteRangXfromSql(SqlList<T> &L, T s, T t);
    template <typename T>
    friend bool listDelteDuplicate(SqlList<T> &L);
    template <typename T>
    friend bool listMerge(SqlList<T> L1, SqlList<T> L2, SqlList<T> &L_merge);
    template <typename T>
    friend bool findX(SqlList<T> &L, T value);
};

template<typename ElemType>
void SqlList<ElemType>::listTraverse(void (*visit)(ElemType &L))
{
    for(int i=0; i<length; i++)
        visit(*(List+i));
    std::cout << std::endl;
}



/**************** EXCERCISES ******************/

/********************************/
// 一个整数序列 A 有n个元素, 所有元素a满足， 0<= a < n；
//  其中元素有 a(p1) = a(p2) = ... = a(pm)， 若m > n/2，则 a(p1) 为主元素
//  算法思想：
//  1.若m>n/2， 则m的个数至少占序列的一半，故可用一元计数器对 count 候选数计数，若一元计数器 count < 0，
//  则一定无主元素，若一元计数器 count>0， 则可能存在主元素。
//  2.判断 candidate 是否能成为主元素
int mojarity_Search(int a[], int n)
{   //
    int i, candidate, count;
    candidate = a[0];
    for (i=1; i<n; i++)
    {
        if (a[i] == candidate) count++;
        else
            if (count > 0) count--;
            else
            {
                candidate = a[i];
                count = 1;
            }
    }
    if(count > 0)
        for (count=0,i = 0; i<n; i++)
            if (a[i] == candidate) count++;
    if (count > n/2) return candidate;
    return -1;
}
/********************************/

/********************************/
//  描述：两个升序且数量相等的整型数组 A,B，中位数分别为a,b ，现在要求出含两个数组的所有元素的中位数 c。
//  算法思想：
//  1. if a=b, 则 c 是 a 或 b 中的一个。
//  2. if a>b, 则舍去 A 的大于中位数部分，保留小于中位数部分；同时舍去 B 的小于中位数部分，保留大于中位数部分
//  3. if a<b, 舍去 A 的小于中位数部分，保留大于中位数部分；同时舍去 B 的大于中位数部分，保留小于中位数部分；
//  4. 重复1-3，直到两个序列中均只有1个元素为止，较小者为中位数。

int median_Search(int A[], int B[], int n)
{
    int s1=0, d1=n-1, m1, s2=0, d2=n-1, m2;
    while (m1 != d1 || m2 != d2)
    {   m1 = (s1+d1) / 2;
        m2 = (s2+d2) / 2;
        if (A[m1] == B[m2]) return A[m1]; // 满足 step1
        if (A[m1] > B[m2])
        {   // 舍去 A 的大于中位数部分，保留小于中位数部分；同时舍去 B 的小于中位数部分，保留大于中位数部分
            if ((s1 + d1)%2 == 0)
            {   // 若元素个数为奇数，保留中间点。
                d1 = m1;
                s2 = m2;
            }
            else
            {   // 若元素个数为偶数，保留中间点。
                d1 = m1-1;
                d2 = m2+1;
            }
        }
        else
        {   // a<b, 舍去 A 的小于中位数部分，保留大于中位数部分；同时舍去 B 的大于中位数部分，保留小于中位数部分；
            if ((s1+d1)%2 == 0)
            {   // 元素个数为奇
                s1 = m1;
                d2 = m2;
            }
            else
            {
                s1 = m1+1;
                d2 = m2-1;
            }
        }
    }
    return A[m1] < B[m2] ? A[m1] : B[m2];
}

// T(f(n)) = O (log n) S = O(1)
/********************************/

/********************************/
void reverse_array(int L[], int from, int to)
{
    int i, temp;
    for (i=0; i<(to - from + 1)/2; i++)
    {
        temp = L[from+i];
        L[from+i] = L[to-i];
        L[to-i] = temp;
    }
}
void shiftP(int L[], int n, int p)
{
    reverse_array(L, 0, p-1);  // T = O (n)
    reverse_array(L, p, n-1);  // T = O (n)
    reverse_array(L, 0, n-1);  // T = O (n)
}
/********************************/

template<typename ElemType>
bool findX(SqlList<ElemType> &L, ElemType value)
{
    if (value < L.List[0])
    {
        L.listInsert(1, value);
        return true;
    }
    if (value > L.List[L.length - 1])
    {
        L.listInsert(L.length+1, value);
        return true;
    }
    int pos = 0;
    int right = 0;
    int left = L.length - 1;
    int mid = 0;
    while (right != left)
    {
        mid = (right + left) / 2;
        if (value < L.List[mid]) left = mid + 1;
        if (value > L.List[mid]) right = mid - 1;
        if (value == L.List[mid])
        {
            pos = mid;
            break;
        }
    }
    
    if (right == left)
    {
        L.listInsert(right, value);
        return false;
    }
    
    ElemType temp = L.List[pos];
    L.List[pos] = L.List[pos+1];
    L.List[pos+1] = temp;
    return true;
};

/********************/
typedef int dataType;
void reverse2Arrays(dataType A[], int left, int right, int arraySize)
{   // 逆转
    if (left >= right || right >= arraySize) return;
    int mid = (right+left) / 2;
    for (int i=0; i<mid - left; i++)
    {
        dataType temp = A[left+i];
        A[left+i] = A[right-i];
        A[right-i] = temp;
    }
}
void exchange2Arrays(dataType A[], int m, int n, int arraySize)
{   // 逆转 A[0...right-1] -> A[left...left+right-1] 同时, A[right...left-1] -> A[0...left-1]
    reverse2Arrays(A, 0, m+n-1, arraySize);
    reverse2Arrays(A, 0, n-1, arraySize);
    reverse2Arrays(A, n, m+n-1, arraySize);
}
/********************/

template <typename ElemType>
bool listMerge(SqlList<ElemType> L1, SqlList<ElemType> L2, SqlList<ElemType> &L_merge)
{   // 合并两个 “有序表”
    if ((L1.length == 0 && L2.length == 0) || L2.length+L1.length > L_merge.maxSize) return false;
    int i=0, j=0, k=0;
    while ( i<L1.length && j<L1.length)
        L_merge[k++] = L1.List[i] < L1.List[j] ? L1.List[i] : L1.List[j];
    while (i<L1.length)
        L_merge[k++] = L1.List[i];
    while (i<L2.length)
        L_merge[k++] = L2.List[i];
    L_merge.length = k+1;
    return true;
};

template <typename ElemType>
bool listDelteDuplicate(SqlList<ElemType> &L)
{   // 删除“有序表”中重复的数，每个重复的数只留下一个, 使表中每个数都不一样
    if (L.length == 0) return false;
    int i,j ;
    for (i=0,j=1; j<L.length; j++)
    {
        if(L.List[i] != L.List[j]) L.List[++i] = L.List[j];
    }
    L.length = i+1;
    return true;
};


template <typename ElemType>
bool ListDeleteRangXfromSql(SqlList<ElemType> &L, ElemType s, ElemType t)
{   // 删除 顺序表s-t 范围内的数
    if(L.length == 0 || s > t) return false;
    int count = 0;
    for (int i=0; i<L.length; i++)
    {
        if (L.List[i] >= s && L.list[i] <= t) count ++;
        else L.list[i-count] = L.list[i];
    }
    L.length -= count;
    return true;
};


template<typename ElemType>
bool ListDelete1 (SqlList<ElemType> &L, ElemType &e)
{   // 删除顺序表中的e， 并用最后一个数覆盖被删除的位置
    if (L.length == 0) return false;
    e = L.List[0];
    int pos = 0;
    for(int i=0; i<L.length; i++)
    {
        if (L.List[i] < e) {
            pos = i;
            e = L.List[i];
        }
    }
    L.List[pos] = L.List[L.length--];
    return true;
};

template <typename ElemType>
bool ListDeleteRangeX(SqlList<ElemType> &L, ElemType s, ElemType t)
{   // 删除有续表中 s-t 的数。
    if (s >= t || L.length == 0) return false;
    int count = 0;
    int p = 0;
    int q = L.length - 1;
    while ( s > L.List[p])
    {
        p++;
        if (p >= L.length) return false;
    }
    while ( t < L.List[q-1]) q--;
    if (q <= 0) return false;
    count = q - p;
    while ( q < L.length )
    {
        L.List[q-count] = L.List[q];
        q++;
    }
    L.length -= count;
    return true;
};

template<typename ElemType>
void ListReverse(SqlList<ElemType> &L)
{   // 空间O（1）倒置表。
    ElemType temp;
    for (int i= (L.length-1)/2; i>=0; i--) {
        temp = L.List[i];
        L.List[i] = L.List[L.length-1-i];
        L.List[L.length-1-i] = temp;
    }
};

template<typename ElemType>
void ListDeleteAllX (SqlList<ElemType> &L, ElemType value)
{   // O（1）删除所有值为value的元素
    int count = 0;
    for (int i=0; i<L.length; i++) {
        if ( L.List[i] == value)
            count++;
        else
        {
            L.List[i-count] = L.List[i];
        }
    }
    L.length -= count;
};


#endif /* SqlList_h */
