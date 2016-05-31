#pragma once

#include <vector>
#include <fstream>
#include <random>

template<class Element> class Markov
{
private:
	std::vector<Element> elems;
	std::vector<std::vector<double> > AdjacencyMatrix;
	bool Initiated; // флаг инициализации
public:
	int Current; // текущий элемент

	Markov() : Initiated(false), Current(0) {};

	void AddElement(Element Elem); // добавляет вершину в цепь Маркова

	bool InitAdjacency(); // выполняется после добавления элементов

	Element *Next(int StartElement = -1); // делает проход с заданного элемента цепи. Если элемент не задан,
										 // то используется предыдущий пройденный из переменной Current

	Element At(int Index); // возвращает элемент по его индексу

	bool UninitAdjacency(); // очистить матрицу смежности

	bool PushAdjacency(int StringNum, int RawNum, double Probability); // заполнение матрицы смежности для связей в цепочке Маркова 

	int size(); // возвращает размер n матрицы смежности (n x n)

	void info(std::ostream &stream); // выводит в ofstream информацию о текущем состоянии цепи Маркова

};


template <class Element> void Markov<Element>::AddElement(Element elem)
{
	Markov<Element>::elems.push_back(elem);
}

template <class Element> bool Markov<Element>::InitAdjacency()
{
	std::vector<double> strings;
	if ((Markov<Element>::elems.size() > 1) && (!Markov<Element>::Initiated))
	{
		if (Markov<Element>::AdjacencyMatrix.size())
		{
			return false;
		}
		for (unsigned int i = 0; i < Markov<Element>::elems.size(); i++)
		{
			Markov<Element>::AdjacencyMatrix.push_back(strings);
			for (unsigned int j = 0; j < Markov<Element>::elems.size(); j++)
			{
				Markov<Element>::AdjacencyMatrix.at(i).push_back(0);
			}
		}
		Markov<Element>::Initiated = true;
		return true;
	}
	else
		return false;
}

template <class Element> bool Markov<Element>::PushAdjacency(int StringNum, int RawNum, double Probability)
{
	bool result = false;;
	if (!Markov<Element>::Initiated)
		return result;
	try
	{
		Markov<Element>::AdjacencyMatrix.at(StringNum).at(RawNum) = Probability;
		result = true;
	}
	catch (...) {}
	return result;
}

template <class Element> Element Markov<Element>::At(int Index)
{
	return Markov<Element>::elems.at(Index);
}

template <class Element> int Markov<Element>::size()
{
	return Markov<Element>::AdjacencyMatrix.size();
}

template <class Element> bool Markov<Element>::UninitAdjacency()
{
	if (Markov<Element>::Initiated)
	{
		for (int i = 0; i < Markov<Element>::size(); i++)
		{
			Markov<Element>::AdjacencyMatrix.at(i).clear();
		}
		Markov<Element>::AdjacencyMatrix.clear();
		Markov<Element>::Initiated = false;
		return true;
	}
	else
		return false;
}

template <class Element> void Markov<Element>::info(std::ostream &stream)
{
	stream << "Markov chain dump:" << std::endl;

	for (int i = 0; i < Markov<Element>::elems.size(); i++)
	{
		stream << i << ": " << Markov<Element>::elems.at(i).c_str() << std::endl;
	}
	if (Markov<Element>::Initiated)
	{
		stream << "Adjacency matrix initialized: " << std::endl;
		for (int i = 0; i < Markov<Element>::size(); i++)
		{
			stream << i << ": ";
			for (int j = 0; j < Markov<Element>::size(); j++)
			{
				stream << Markov<Element>::AdjacencyMatrix.at(i).at(j) << " ";
			}
			stream << std::endl;
		}
	}
	else
		stream << "Adjacency matrix was not initialized" << std::endl;
	stream << "Current iteration state at " << Markov<Element>::Current << " vertex" << std::endl;
}

template <class Element> Element *Markov<Element>::Next(int StartElement = -1)
{

	if (Markov<Element>::Initiated)
	{

		if (StartElement == -1)
			StartElement = Markov<Element>::Current;

		std::random_device              rd;
		std::mt19937                    gen(rd());
		std::discrete_distribution<>    dicr_distr(Markov<Element>::AdjacencyMatrix.at(Current).begin(),
			Markov<Element>::AdjacencyMatrix.at(Current).end());


		int next = dicr_distr(gen);
		if (next == Markov<Element>::size())
			return NULL;

		Markov<Element>::Current = next;
		return &(Markov<Element>::elems.at(next));
	}
	return NULL;
}