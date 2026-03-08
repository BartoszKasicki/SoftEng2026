#ifndef _SHAPERESULTDATA_H
#define _SHAPERESULTDATA_H


#include <vector>
using namespace std;
#include "ShapeResultIndex.h"

template<class T>
class ShapeResultData {
  private:
    vector<T> attribs;


  public:
    inline T get(ShapeResultIndex ind);

    inline bool set(ShapeResultIndex ind, const T & val);

};
template<class T>
inline T ShapeResultData<T>::get(ShapeResultIndex ind) {
    if(ind<attribs.size()) return attribs[ind];
    return 0;
}

template<class T>
inline bool ShapeResultData<T>::set(ShapeResultIndex ind, const T & val) {
    if(ind>=attribs.size())attribs.resize(ind+1);
    attribs[ind]=val;
    return true;
}

#endif
