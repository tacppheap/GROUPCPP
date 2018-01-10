#ifndef DLL_INTERFACE_H_
#define DLL_INTERFACE_H_
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#include "stdafx.h"
#include "ZombieM.h"
#include "TileField.h"
#include <iostream>

class AIInterface
{
public:
	virtual Direction AIRequestHandler(TileField* _tileField, ZombieM* zombie) = 0;

	virtual void release() = 0;
	virtual ~AIInterface() = default;
};

extern "C" DLL_API AIInterface * createAI();

namespace detail
{
	struct AIInterfaceRelease
	{
		void operator()(AIInterface * ptr) const
		{
			ptr->release();
		}
	};

} // detail


#endif /*DLL_INTERFACE_H_*/
