#include <iostream>
#include <vector>
#include "mazepart.h"
#include "DesignModel/Singleton.h"
class Maze;
class MazeGame
{
public:
	Maze* CreateMaze();
};
class Maze : public Singleton<Maze>
{
	friend class Singleton<Maze>;
protected:
	Maze(){};
public:
	//void CreateMaze();
	void AddRoom(Room* r){
		m_rooms.push_back(r);
	};
	std::vector<Room*>& GetRooms(){
		return m_rooms;
	};
private:
	std::vector<Room*> m_rooms;
};
class RoomBuilder
{
public:
	Room* GetRoomWithDoor(Direction dir)
	{
		Room* r = new Room(m_count++);
		Door* d = new Door(r);
		for(int i = East; i <= North; ++i)
		{
			Direction t_dir = static_cast<Direction>(i);
			if(t_dir == dir)
				r->SetSide(t_dir,d);
			r->SetSide(t_dir,new Wall());
		}
	};
private:
	static int m_count;
};
int RoomBuilder::m_count = 1;
Maze* MazeGame::CreateMaze()
{
	Maze* m = Maze::GetSingleton();
	Room* r1 = new Room(1);
	Room* r2 = new Room(2);
	m->AddRoom(r1);
	m->AddRoom(r2);
	Door* d = new Door(r1,r2);
	r1->SetSide(East,new Wall());
	r1->SetSide(South,d);
	r1->SetSide(West,new Wall());
	r1->SetSide(North,new Wall());
	r2->SetSide(East,new Wall());
	r2->SetSide(South,new Wall());
	r2->SetSide(West,new Wall());
	r2->SetSide(North,d);
	
	return m;
}
int main(int argc,char* argv[])
{
	MazeGame mg;
	Maze* m = mg.CreateMaze();
	std::vector<Room*> rooms = m->GetRooms();
	for(int i = 0; i < rooms.size(); ++i)
	{
		rooms[i]->Enter();
		rooms[i]->PrintSides();
	}
	Maze::Release();
}