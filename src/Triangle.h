#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "Shape2D.h"
#include "ShapeResultData.h"
#include <string>
#include <cmath>
#include "ShapeParam.h"
#include "ShapeParamIndex.h"
#include "ShapeResultIndex.h"

using namespace std;

template <class T> class Triangle : public Shape2D<T> {
public:
    inline virtual ShapeResult<T> compute();

    inline string print();

    inline Triangle(const ShapeParam<T>& param);
};

template <class T> inline ShapeResult<T> Triangle<T>::compute()
{
    ShapeResult<T> result;

    T base = this->m_param.get_attrib(PARAM_WIDTH);
    T height = this->m_param.get_attrib(PARAM_HEIGHT);

    if (base <= 0 || height <= 0)
    {
        return result;
    }

    T area = (base * height) / (T)2;

    result.set_attrib(ShapeResultIndex::RESULT_AREA, area);

    return result;
}

template <class T> inline string Triangle<T>::print() { return "Triangle"; }

template <class T>
inline Triangle<T>::Triangle(const ShapeParam<T>& param): Shape2D<T>(param)
{}

#endif