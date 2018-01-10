#ifndef TILE_FIELD_H
#define TILE_FIELD_H

#include <map>
#include <memory>
#include "GameObjectM.h"


typedef size_t TileX;
typedef size_t TileY;
typedef size_t SizeTileX;
typedef size_t SizeTileY;

class Tile
{
public:
	Tile();

	void addObject(ObjectPtr _obj);
	void deleteObject(ObjectPtr _obj);

	bool isEmpty();
	std::vector<ObjectPtr> getObjects(ObjectType _type);
	std::vector<ObjectPtr> getObjects(ObjectType _type, ObjectID _id);

private:
	std::vector<ObjectPtr> objects_;
};

class TilePos
{
public:

	TilePos(TileX _column, TileY _row);
	TileX column;
	TileY row;
};

class TileRegionPos
{
public:
	TileRegionPos(SizeTileX _startColumn, SizeTileX _endColumn, SizeTileY _startRow, SizeTileY _endRow);
	bool operator==(const TileRegionPos& _that);

	SizeTileX startColumn;
	SizeTileX endColumn;
	SizeTileY startRow;
	SizeTileY endRow;
};


typedef Tile* TilePtr;

class TileField :public std::enable_shared_from_this<TileField>
{
public:
	TileField(SizeTileX _width, SizeTileY _height, SizeX _tileWidth, SizeY _tileHeight);
	~TileField();
	void addObject(StrongObjectPtr& _obj);
	void deleteObject(ObjectPtr _obj);

	void objectChangePosHandler(ChangePosArgs _arg);

	bool checkTilePos(TileX _column, TileY _row);
	std::vector<StrongObjectPtr> selectCrossedObj(ObjectType _type, ObjectRect _rect, ObjectID _id, std::vector<ObjectType> _typeList);

	SizeX getTileWidth();
	SizeY getTileHeight();
	SizeTileX getWidth();
	SizeTileY getHeight();

	std::map<ObjectID, StrongObjectPtr> gameObjectStore_;

private:

	SizeTileX width_;
	SizeTileY height_;
	SizeX tileWidth_;
	SizeY tileHeight_;
	std::vector<TilePtr> tileStore_;

	TileRegionPos getTileRegionPos(ObjectRect _rect);
	TilePtr getTile(TileX _column, TileY _row);

	std::vector<TilePtr> selectTileRegion(TileRegionPos _region);
};
#endif // TILE_FIELD_H
