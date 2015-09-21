#include <iostream>
#include <strstream>
#include <string>
class Man
{
	public:
		Man(){std::cout << "Man Created!\n";};
		std::string& GetData(){return m_data;};
	private:
		std::string m_data;
};
class Builder
{
	public:
		virtual void BuildHead() = 0;
		virtual void BuildBody() = 0;
		virtual void BuildTowHand() = 0;
		virtual void BuildTowLeg() = 0;
		virtual void BuildMan() = 0;
		virtual Man* GetMan() = 0;
};
class World
{
	public:
		Man* CreateMan(Builder& b)
		{
			b.BuildMan();
			b.BuildHead();
			b.BuildBody();
			b.BuildTowHand();
			b.BuildTowLeg();
			return b.GetMan();
		};
};
class ManBuilder : public Builder
{
	public:
		void BuildMan(){man = new Man();};
		void BuildHead(){man->GetData().append("Head With Two eyes,one mouth and one nose created!\n");};
		void BuildBody(){man->GetData().append("Body With green cloth Created!\n");};
		void BuildTowHand(){man->GetData().append("Hands And Arms Created!\n");}
		void BuildTowLeg(){man->GetData().append("Tow Leg and feet Created!\n");};
		Man* GetMan(){return man;};
	private:
		Man* man;
};
int main(int argc,char* argv[])
{
	World w;
	ManBuilder mb;
	Man* man = w.CreateMan(mb);
	std::cout << man->GetData() << std::endl;
	return 0;
}