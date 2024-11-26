#ifndef CUBEGEOMETRY_H
#define CUBEGEOMETRY_H

#include "geometry.h"

class CubeGeometry : public Geometry
{
public:
    CubeGeometry();

    // Geometry interface
public:
    void construct() override;
};

#endif // CUBEGEOMETRY_H
