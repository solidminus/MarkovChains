#include <iostream>
#include "Markov.h"
#include <string>
#include <fstream>

using namespace std;

int main()
{
	Markov<string> chain;
	ofstream outs;
	outs.open("out.txt");
	ifstream ins;
	ins.open("matrix.txt");

	int num;
	double Prob = 0;
	(ins >> num).get();
	string str;
	for (int i = 0; i < num; i++)
	{
		getline(ins, str);
		chain.AddElement(str);
	}
	if (chain.InitAdjacency())
	{
		for (int i = 0; i < chain.size(); i++)
		{
			for (int j = 0; j < chain.size(); j++)
			{
				(ins >> Prob).get();
				if (!chain.PushAdjacency(i, j, Prob))
				{
					cerr << "Adjacency matrix write error" << endl;
				}
			}
		}

		outs << chain.At(0) << " ";
		for (int i = 0; i < 20 * chain.size() - 1; i++)
		{
			string *str = chain.Next();
			if (str != NULL)
				outs << (*str).c_str() << " ";
			else
			{
				outs << std::endl;
				chain.Current = 0;
				outs << chain.At(0) << " ";

			}
		}

		chain.UninitAdjacency();
	}
	else
		cerr << "Can not initialize Adjacency matrix" << endl;;

	ins.close();
	outs.close();
	cin.get();
	return 0;
}