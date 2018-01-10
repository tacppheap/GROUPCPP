#include <stdexcept>
#include "stdafx.h"
#include "TileField.h"

////////////////////////////////////Tile Implementation///////////////////////////////////////

Tile::Tile()
{
}


bool Tile::isEmpty()
{
	return objects_.empty();
}

void Tile::addObject(ObjectPtr _obj)
{
	objects_.push_back(_obj);
}

void Tile::deleteObject(ObjectPtr _obj)
{
	for (std::vector<ObjectPtr>::iterator it = objects_.begin(); it != objects_.end(); it++)
	{
		if ((*it)->getId() == _obj->getId())
		{
			objects_.erase(it);
			break;
		}
	}
}

std::vector<ObjectPtr> Tile::getObjects(ObjectType _type)
{
	std::vector<ObjectPtr> tempObjects;

	for (ObjectPtr obj : objects_)
	{
		if (obj->getType() == _type)
		{
			tempObjects.push_back(obj);
		}
	}
	return tempObjects;
}

std::vector<ObjectPtr> Tile::getObjects(ObjectType _type, ObjectID _id)
{
	std::vector<ObjectPtr> tempObjects;

	for (ObjectPtr obj : objects_)
	{
		if (obj->getType() == _type && obj->getId() != _id)
		{
			tempObjects.push_back(obj);
		}
	}
	return tempObjects;
}

TilePos::TilePos(TileX _column, TileY _row) : row(_row), column(_column)
{
}

TileRegionPos::TileRegionPos(SizeTileX _startColumn,
	SizeTileX _endColumn,
	SizeTileY _startRow,
	SizeTileY _endRow) : startRow(_startRow),
	endColumn(_endColumn),
	startColumn(_startColumn),
	endRow(_endRow)
{
}

bool TileRegionPos::operator==(const TileRegionPos& _that)
{
	if (startColumn == _that.startColumn &&
		endColumn == _that.endColumn &&
		startRow == _that.startRow &&
		endRow == _that.endRow)
	{
		return true;
	}
	return false;
}


////////////////////////////////////TileField Implementation///////////////////////////////////////

TileField::TileField(SizeTileX _width, SizeTileY _height, SizeX _tileWidth, SizeY _tileHeight) : tileWidth_(_tileWidth),
tileHeight_(_tileHeight),
width_(_width),
height_(_height)
{
	for (int i = 0; i < width_ * height_; i++)
	{
		tileStore_.push_back(new Tile());
	}
}

SizeX TileField::getTileWidth()
{
	return tileWidth_;
}

SizeY TileField::getTileHeight()
{
	return tileHeight_;
}

SizeTileX TileField::getWidth()
{
	return width_;
}

SizeTileY TileField::getHeight()
{
	return height_;
}




TileRegionPos TileField::getTileRegionPos(ObjectRect _rect)
{
	X x;
	Y y;
	SizeX width;
	SizeY height;

	x = _rect.pos.x;
	y = _rect.pos.y;
	width = _rect.width;
	height = _rect.height;

	if (x > width_ * tileWidth_)
	{
		x = width_;
		width = 0;
	}

	if (y > height_ * tileHeight_)
	{
		y = height_;
		height = 0;
	}

	if (x < 0)
	{
		width += x;
		if (width < 0)
		{
			width = 0;
		}
		x = 0;
	}

	if (y < 0)
	{
		height += y;
		if (height < 0)
		{
			height = 0;
		}
		y = 0;
	}

	TilePos tilePos = TilePos(x / tileWidth_, y / tileHeight_);

	return(TileRegionPos(tilePos.column,
		tilePos.column + width / tileWidth_ + 1,
		tilePos.row,
		tilePos.row + height / tileHeight_ + 1));
}

bool TileField::checkTilePos(TileX _column, TileY _row)
{
	return (_column < width_ && _row < height_);
}

TilePtr TileField::getTile(TileX _column, TileY _row)
{
	if (!checkTilePos(_column, _row))
	{
		return nullptr;
	}
	return tileStore_[_row * width_ + _column];
}

std::vector<TilePtr> TileField::selectTileRegion(TileRegionPos _region)
{
	std::vector<TilePtr> selectList;

	for (TileY row = _region.startRow; row <= _region.endRow; row++)
	{
		for (TileX column = _region.startColumn; column <= _region.endColumn; column++)
		{
			TilePtr objTile = getTile(column, row);
			if (objTile)
			{
				selectList.push_back(objTile);
			}
		}
	}
	return selectList;
}

void TileField::addObject(StrongObjectPtr& _obj)
{
	TileRegionPos tileRegionPos = getTileRegionPos(_obj->getObjectRect());

	/*if (!checkTilePos(tileRegionPos.startColumn, tileRegionPos.endColumn) ||
	!checkTilePos(tileRegionPos.startRow, tileRegionPos.endRow))
	{
	return;
	}*/

	gameObjectStore_.insert(std::pair<ObjectID, StrongObjectPtr>(_obj->getId(), _obj));
	_obj->changePosEvent.Add(shared_from_this(), &TileField::objectChangePosHandler);

	std::vector<TilePtr> tiles = selectTileRegion(tileRegionPos);

	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->addObject(_obj.get());
	}

}

void TileField::deleteObject(ObjectPtr _obj)
{

	std::vector<TilePtr> tiles = selectTileRegion(getTileRegionPos(_obj->getObjectRect()));
	for (TilePtr tile : tiles)
	{
		tile->deleteObject(_obj);
	}
	gameObjectStore_.erase(_obj->getId());
}


void TileField::objectChangePosHandler(ChangePosArgs _arg)
{
	ObjectRect sourceObjRect = _arg.source->getObjectRect();
	sourceObjRect.pos = _arg.sourcePos;

	TileRegionPos targetTileRegionPos = getTileRegionPos(_arg.source->getObjectRect());

	if (getTileRegionPos(sourceObjRect) == targetTileRegionPos)
	{
		return;
	}


	/*if (!checkTilePos(targetTileRegionPos.startColumn, targetTileRegionPos.endColumn) ||
	!checkTilePos(targetTileRegionPos.startRow, targetTileRegionPos.endRow))
	{
	return;
	}*/

	std::vector<TilePtr> tiles = selectTileRegion(getTileRegionPos(sourceObjRect));
	for (TilePtr tile : tiles)
	{
		tile->deleteObject(_arg.source.get());
	}


	tiles = selectTileRegion(targetTileRegionPos);

	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->addObject(_arg.source.get());
	}
}


std::vector<StrongObjectPtr> TileField::selectCrossedObj(ObjectType _type, ObjectRect _rect, ObjectID _id, std::vector<ObjectType> _typeList)
{
	std::vector<TilePtr> selectedTiles = selectTileRegion(getTileRegionPos(_rect));
	std::vector<StrongObjectPtr> selectedCrossedObj;
	std::vector<ObjectPtr> selectedObj;
	std::map<ObjectID, ObjectPtr> checkedObj;

	for (TilePtr tile : selectedTiles)
	{
		for (ObjectType type : _typeList)
		{
			selectedObj = tile->getObjects(type, _id);
			for (ObjectPtr obj : selectedObj)
			{
				if (checkedObj.find(obj->getId()) != checkedObj.end())
				{
					break;
				}

				if (_rect.isCrossed(obj->getObjectRect()))
				{
					selectedCrossedObj.push_back((*gameObjectStore_.find(obj->getId())).second);
				}

				checkedObj.insert(std::pair<ObjectID, ObjectPtr>(obj->getId(), obj));
			}
		}
	}

	return selectedCrossedObj;
}

TileField::~TileField()
{
	for (TilePtr tile : tileStore_)
	{
		delete tile;
	}
}