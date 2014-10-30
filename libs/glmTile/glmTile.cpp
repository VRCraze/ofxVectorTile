//
//  glmTile.cpp
//
//  Created by Patricio Gonzalez Vivo on 8/27/14.
//
//

#include "glmTile.h"

#include "glmGeometryBuilder.h"

glmTile::glmTile():tileX(-1), tileY(-1), zoom(-1){
}

glmTile::~glmTile(){
    byLayers.clear();
    labeledFeatures.clear();
    labeledLines.clear();
    labeledPoints.clear();
}

bool glmTile::load(int _tileX, int _tileY, int _zoom){
    tileX = _tileX;
    tileY = _tileY;
    zoom = _zoom;
    
    glmGeometryBuilder builder;
    builder.setOffset(_tileX,_tileY,_zoom);
    builder.load(tileX, tileY, zoom, *this);
}

bool glmTile::load(double _lat, double _lon, int _zoom){
    int tileX = long2tilex(_lon, _zoom);
    int tileY = lat2tiley(_lat, _zoom);
    
    return load(tileX,tileY,_zoom);
}

glmMesh glmTile::getMeshFor(const std::string &_layerName){
    glmMesh mesh;
    for (auto &it : byLayers[_layerName]){
        mesh.add( *it );
    }
    return mesh;
}

glmMesh glmTile::getMeshFor(const std::vector< std::string > &_layersNames){
    glmMesh mesh;
    for (auto &it : _layersNames ) {
        mesh.add(getMeshFor(it));
    }
    return mesh;
}

glmMesh glmTile::getMesh(){
    glmMesh mesh;
    for (auto &it : byLayers ){
        mesh.add( getMeshFor(it.first) );
    }
    return mesh;
}