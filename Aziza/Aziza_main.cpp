#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

class FirstType
{
	int _type;

	public:	
	string _name;
	float x, y, z;
	FirstType(float coor_x, float coor_y, float coor_z, int type, string name)
		:x(coor_x), y(coor_y), z(coor_z), _type(type), _name(name){	}

	void setCoor(float coor_x, float coor_y, float coor_z)
	{
		x = coor_x; 
		y = coor_y; 
		z = coor_z;
	}

};

inline std::ostream& operator<<(std::ostream& str, const FirstType& p)
{
    str<< p._name<<'\t'<<p.x<<'\t'<<p.y<<'\t'<<p.z;
    return str;
}

inline std::ostream& operator<<(std::ostream& str, const vector <FirstType>& p)
{
    str<<p.size()<<"\n\n";
    for(int i=0; i<p.size(); i++)
	{
		str<<p[i]<<endl;
	}
    return str;
}

// создаём гранецентрированный куб
void gck(std::vector <FirstType>&Vect, int p_x, int p_y, int p_z, string name, int type, float alpha)
{
	for(int i=0; i<p_z; i++)
	{
		for(int j=0; j<p_y; j++)
		{
			for(int k=0; k<p_x; k++)
			{
				Vect.push_back(FirstType((0+i)*alpha, (0+j)*alpha, (0+k)*alpha, type, name));
				Vect.push_back(FirstType((0+i)*alpha, (0.5+j)*alpha, (0.5+k)*alpha, type, name));
				Vect.push_back(FirstType((0.5+i)*alpha, (0.5+j)*alpha, (0+k)*alpha, type, name));
				Vect.push_back(FirstType((0.5+i)*alpha, (0+j)*alpha, (0.5+k)*alpha, type, name));
			}
		}
	}
};

// считаем энергию
float energ (const std::vector <FirstType>&Vect, float a0)
{
	float E=0;

	float A1=0, A0=0.103, ksi=1.178, p=10.928, q=3.139, r0=2.9;
	
	for (int i=0; i<Vect.size(); i++)
	{	
		float Er=0, Eb= 0;
		for (int j=0; j<Vect.size(); j++)
		{
			for (int dx=-1; dx<2; dx++)
			{
				for (int dy=-1; dy<2; dy++)
				{
					for (int dz=-1; dz<2; dz++)
					{
						if (i != j || dx !=0 || dy !=0 || dz !=0 )
						{
						
							float rij=sqrt((Vect[j].x + a0*2*dx - Vect[i].x)*(Vect[j].x + a0*2*dx - Vect[i].x)+(Vect[j].y + a0*2*dy - Vect[i].y)*(Vect[j].y + a0*2*dy - Vect[i].y)+(Vect[j].z + a0*2*dz - Vect[i].z)*(Vect[j].z + a0*2*dz - Vect[i].z));
							if (rij<r0)
							{
								Er=Er+(A1*(rij-r0)+A0)*exp(-p*(rij/r0-1));
								Eb=Eb+ksi*ksi*exp(-2*q*(rij/r0-1));
								//cout<< i << ' ' << j << ' ' << rij << ' ' << Er << ' ' << Eb << endl;
							}
						}
					}
				}
			}
		}
		Eb = -sqrt(Eb);
		//cout << Er << ' ' << Eb << endl;
		E += Er+Eb;
	}
	return E;
}

int main()
{	
	// эти параметры у каждого вещества свои, они есть в статьях
	float A1=0, A0=0.103, ksi=1.178, p=10.928, q=3.139, r0=2.9, a0= 2; //4.085;

	//тут проверяли, правильно ли считается энергия, и на этом пока остановились
	while (a0 < 6)
	{
		vector <FirstType> Vect;
		gck (Vect, 2,2,2, "Ag", 0, a0);
		float E=0;
		cout<<energ (Vect, a0)/Vect.size()<< ' '<<a0<<endl;
		a0 += 0.1;
	}

	//cout<<Vect<<endl;
	//cout<<E;
	ofstream myfile;
	myfile.open("new_file.xyz");

	//myfile<<Vect<<endl;
	myfile.close();

	getchar();
	return 0;
}