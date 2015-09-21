#ifndef MAZE_PART_H
#define MAZE_PART_H
#include <vector>
//#include <windows.h>
namespace yj{
	enum Direction{Left,Up,Right,Down,INVALID_DIRECTION=-1};
	class MapSpite
	{
	public:
		//virtual void Draw() = 0;
		//virtual void AddChild(MapSpite* m){};
		virtual void Move(int x,int y) = 0;
		virtual Direction GetSide(MapSpite*) = 0;
		//virtual void Enter(){};
	public:
		std::vector<MapSpite*> m_sides;
	};

	class Room : public MapSpite
	{
	public:
		Room(int num):m_id(num){};
	//	void AddChild(MapSpite* m)
	//	{
	//		m_doors.push_back(m);
	//	}
		void Move(int x,int y)
		{
			
		}
		Direction GetSide(MapSpite*);
	//	void Enter()
	//	{
	//
	//	}
	//public:
		//std::vector<MapSpite*> m_sides;
	private:
		int m_id;
	};
	class Door : public MapSpite
	{
	public:
		Door(Room*){};
		void Move(int x,int y)
		{
			
		}
		Direction GetSide(MapSpite*);
	private:
	public:
		bool m_bopen;
	};
	class Wall : public MapSpite
	{
	public:
		Wall(){}
		void Move(int x,int y)
		{
		}
		Direction GetSide(MapSpite*);
	};
}
#endif
