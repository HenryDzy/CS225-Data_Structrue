/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

/** * This function can map Tiles to the source Image**/
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* newCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    map<Point<3>, int> tile_avg_map;
    vector<Point<3>> points;
    for(unsigned int i=0; i<theTiles.size(); i++){          //calculatethe average color
        HSLAPixel tilePixel = theTiles[i].getAverageColor();  
        Point<3> tilePoint = convertToLAB(tilePixel);   //and transform the pixel into point
        points.push_back(tilePoint); //adding points
        tile_avg_map[tilePoint] = i; //adding map
    }
    KDTree<3>* tree = new KDTree<3>(points);
    for(int i=0; i<theSource.getRows(); i++){   //tranverse every row
        for(int j=0; j<theSource.getColumns(); j++){ //tranverse every column
            HSLAPixel sourcePixel = theSource.getRegionColor(i, j);
            TileImage* nearestTile = get_match_at_idx(*tree, tile_avg_map,      //find the nearest Tile
                                                        theTiles, theSource, i, j);
            newCanvas->setTile(i, j, nearestTile); //set the tile
        }
    }
    delete tree;
    return newCanvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
