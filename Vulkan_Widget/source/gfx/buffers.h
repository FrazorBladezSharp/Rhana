#ifndef BUFFERS_H
#define BUFFERS_H

#include <QList>
#include <QVector3D>
#include <QVector4D>

namespace Night
{
    typedef struct GFXmaterial
    {
        // various attributes
        // color, texture, bump maps, reflectivity and lots more !
        // develope as required ...

        // color
        QVector4D color;

    } GFXmaterial;

    typedef struct GFXvertex
    {
        // position
        QVector3D position;

        // normal - the direction in which a vertex faces
        QVector3D normal;

        // material
        GFXmaterial *material;

    } GFXvertex;

    typedef struct GFXvertexbuffer
    {
        QList<GFXvertex> *vertexData;

    } GFXvertexbuffer;

}
// A Dynamic system for loading 3D Models:

// we can decide upon a material design to use for this individual model
// this can be inserted into the vertex buffer
// data can be populated from a file for the 3D Model

#endif // BUFFERS_H
