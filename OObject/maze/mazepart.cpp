#include "mazepart.h"
#include <algorithm>
#include <assert.h>
namespace yj{
	static const Direction C_REVERSE_DIRS[5] = {Right,Down,Left,Up,INVALID_DIRECTION};
	Direction Room::GetSide(MapSpite* spite)
	{
		if(spite->m_sides.size() == 2)
			return C_REVERSE_DIRS[spite->GetSide(this)];
		assert(spite->m_sides.size() == 4);
		MapSpite* side = 0;
		for(int i = 0; i < 4; ++i)
		{
			std::vector<MapSpite*>::iterator it = std::find(m_sides.begin(),m_sides.end(),spite->m_sides[i]);
			if(it != m_sides.end())
			{
				side = *it;
				break;
			}
		}
		return side->GetSide(spite);
	}

	Direction Door::GetSide(MapSpite* spite)
	{
		std::vector<MapSpite*>::iterator it = std::find(m_sides.begin(),m_sides.end(),spite);
		if(it == m_sides.end())
			return INVALID_DIRECTION;

		MapSpite* side = *it;
		
		it = std::find(spite->m_sides.begin(),spite->m_sides.end(),side);

		return static_cast<Direction>(it-spite->m_sides.begin());
	}

	Direction Wall::GetSide(MapSpite* spite)
	{
		std::vector<MapSpite*>::iterator it = std::find(m_sides.begin(),m_sides.end(),spite);
		if(it == m_sides.end())
			return INVALID_DIRECTION;

		MapSpite* side = *it;
		
		it = std::find(spite->m_sides.begin(),spite->m_sides.end(),side);

		return static_cast<Direction>(it-spite->m_sides.begin());
	}

}