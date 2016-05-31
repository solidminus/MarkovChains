# MarkovChains open lib v.1.0

int Current; // текущий элемент

template<class Element>

void AddElement(Element Elem); // добавляет вершину в цепь Маркова

bool InitAdjacency(); // выполняется после добавления элементов

template<class Element>

Element *Next(int StartElement = -1); // делает проход с заданного элемента цепи. Если элемент не задан,
										 // то используется предыдущий пройденный из переменной Current
template<class Element>

Element At(int Index); // возвращает элемент по его индексу

bool UninitAdjacency(); // очистить матрицу смежности

bool PushAdjacency(int StringNum, int RawNum, double Probability); // заполнение матрицы смежности для связей в цепочке Маркова 

int size(); // возвращает размер n матрицы смежности (n x n)

void info(std::ostream &stream); // выводит в ofstream информацию о текущем состоянии цепи Маркова
