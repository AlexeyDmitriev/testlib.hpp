Tutorial {#tutorial}
=========

`testlib.hpp` - это библиотека для разработки задач.  В данный момент с ее помощью вы сможете с легкостью создавать чекеры и валидаторы на языке С++. При этом перед вами будут открыты огромные возможности за счет поддержки нашей библиотекой объектно-ориентированного подхода программирования.

Дальнейшее знакомство с библиотекой предлагаем осуществить на примерах.

Вот так выглядит код чекера, проверяющего равенство двух целых чисел:

~~~~~~~~~~~~~~~
  #include "testlib.hpp"
  TESTLIB_CHECK(){
    int a = ans.read<int>();
    int b = ouf.read<int>();
    if(a != b){
      WA(expectation(a, b)); //Это макрос, который выведет cout << a << " expected, " << b << " found" << endl;
    }
    else{
      OK(a);
    }
  }
~~~~~~~~~~~~~~~

Уже знакомые с проектом [testlib.h](http://code.google.com/p/testlib), могут увидеть здесь знакомые потоки `ouf` (отвечающий за выведенный пользователем ответ) и `ans` (отвечающий за правильный ответ). Также доступен поток `inf`, из которого можно читать входные данные теста.

Этот же чекер можно написать проще:

~~~~~~~~~~~~~~~
#include "testlib.hpp"
TESTLIB_CHECK(){
    verifyEqual(ouf.read<int>(), ans.read<int>());
    OK("1 number");
}
~~~~~~~~~~~~~~~

Отличия будут лишь в выводимых сообщениях.

Теперь рассмотрим как выглядит чекер для следующей задачи: «По заданным `n`, `l`, `r`, `s` найти последовательность из `n` чисел, каждое из которых от `l` до `r`, со средним квадратическим равным `s` (гарантируется, что такая последовательность существует)».
Примечание: среднее квадратическое чисел - это корень из среднего арифметического квадратов данных чисел.

~~~~~~~~~~~~~~~
#include "testlib.hpp"
#include <vector>

using namespace std;
TESTLIB_CHECK(){
	long long n = inf.read<long long>();
	long long l = inf.read<long long>();
	long long r = inf.read<long long>();
	long long s = inf.read<long long>();
	vector<long long> out = ouf.read<vector<long long>>(n, make_default_reader<long long>(l, r));
	long long sumSq = 0;
	for (auto i : out) // используем возможности C++11
		sumSq += i * i;
	if (sumSq % n != 0)
		WA("Sum of squares must be divided by n");
	if (s * s * n != sumSq){
		WA("Quadratic mean isn't equal to " << s);
	}
	OK ("Correct answer");
	// Чекер выдаст вердикт FAIL, если не указать вердикт явно.
	// Если в решении участника будет выведено что-то лишнее, вердикт будет изменен на PE
}
~~~~~~~~~~~~~~~

В строке `vector<int> out = ouf.read<vector<int> >(n, make_default_reader<int>(l, r)); ` мы читаем vector<int> из `n` чисел, каждое из которых от `l` до `r`. Для этого мы передаем количество элементов ` n ` и создаем reader<int> `make_default_reader<int>(l, r))`, который позволит читать числа от `l` до `r`. Отметим, что реализация чтения сложных типов данных осуществляется так же просто, как и реализация чтения простых типов данных.
  
Теперь рассмотрим как выглядит чекер для следующей задачи: «Среди данных попарно различных точек найти три, образующих треугольник максимальной площади (c абсолютной точностью 10<sup>-8</sup>)». Здесь программисту придется столкнуться с геометрическим объектом: точка. Покажем, как удобно осуществлять чтение точек.

~~~~~~~~~~~~~~~
#include "testlib.hpp"
#include <set>
#include <vector>

using namespace std;
const double EPS = 1e-8;
```
Создаем класс, ничего необычного.
```c++
struct Point{
	double x, y;
	Point() {}
	Point(double x, double y): x(x), y(y) {}
	bool operator < (const Point& point) const{
		return make_pair(x, y) < make_pair(point.x, point.y);
	}
	Point operator - (const Point& point) const{ //работаем с точками как с их радиус-векторами
		return Point(x - point.x, y - point.y);
	}
};
typedef vector<Point> Triangle;
~~~~~~~~~~~~~~~

Создаем класс-ридер (который должен быть унаследован от `Reader<Point>`).
Можно также специализировать класс `DefaultReader<Point>`, чтобы не передавать экземпляр ридера явно.

~~~~~~~~~~~~~~~
class ReaderPoint : public Reader<Point>{
public:
	ReaderPoint(double maxAbsX, double maxAbsY): minX(-maxAbsX), maxX(maxAbsX), minY(-maxAbsY), maxY(maxAbsY) {}
	ReaderPoint(double minX, double maxX, double minY, double maxY): minX(minX), maxX(maxX), minY(minY) , maxY(maxY) {}
	Point read(IStream& stream){
		double x = stream.read<double>(minX, maxX);
		if (stream.getMode() == IStream::Mode::STRICT)
			stream.readChar(' ');
		double y = stream.read<double>(minY, maxY);
		return Point(x, y);
	}
private:
	double minX, maxX, minY, maxY;
};
~~~~~~~~~~~~~~~

Такие часто используемые классы, как точка, хочется иметь в стандартной библиотеке, чтобы не реализовывать их в каждом чекере. Мы планируем заняться созданием библиотеки часто используемых классов и надеемся на помощь сообщества в этом.

~~~~~~~~~~~~~~~
double outerProduct(const Point& a, const Point& b){
	return a.x * b.y - a.y * b.x;
}

double triangleArea(const Triangle& triangle){
	return fabs( outerProduct(triangle[2] - triangle[0], triangle[1] - triangle[0]) )/ 2.0;
}

set<Point> inputPoints;
ReaderPoint readerPoint(1e6, 1e6); // экземпляр ридера
	
double readAns(IStream& is, Verdict verdict) {
	double s = is.read<double>();
	Triangle res = is.read<Triangle>(3, readerPoint); 
	for (const auto& point: res){
		if (inputPoints.find(point) == inputPoints.end()){
			QUIT(verdict, "Point " << point.x << " " << point.y << " isn't exist in input file");
		}
	}
	verify(fabs(triangleArea(res) - s) < EPS, verdict, "Triangle's square doesn't match answer");
	return s;
}

TESTLIB_CHECK(){
	int n = inf.read<int>();
	for (int i = 0; i < n; i++){
		inputPoints.insert(inf.read<Point>(readerPoint));
	}
	
	double pa = readAns(ouf, Verdict::WA);
	double ja = readAns(ans, Verdict::FAIL);
	
	if (fabs(ja - pa) < EPS)
		OK(pa);
	if (pa > ja + EPS)
		FAIL("Participant answer is better");
	WA("Jury answer is better");
}
~~~~~~~~~~~~~~~

Теперь перейдем к рассмотрению валидаторов.
Условие задачи: в первой строке число `n` - команд в турнире, далее `n` строк, в каждой из которых записано имя команды (из строчных латинских букв). В последующих строках описываются матчи кругового турнира (каждая команда играет с каждой ровно по одному разу) в формате: `<first team> <second team> <first team score> : <second team score>` (в строке содержится описание ровно одного матча). Например, `cska zenit 2 : 1`

~~~~~~~~~~~~~~~
#include "testlib.hpp"
#include <string>
#include <set>

using namespace std;
const int MAXN = 100, MAX_LEN_TEAM = 30;
typedef pair<string, string> TMatch;
typedef pair<int, int> TMatchResult;

inline void isParticipant(const string& curTeam, const set<string>& teams){
	verify(teams.find(curTeam) != teams.end(), Verdict::FAIL, "Matches must be only between participants");
}

inline void addMatch(const TMatch& match, const set<string>& teams,
                     set<TMatch>& playedMatches) {
    isParticipant(match.first, teams);
    isParticipant(match.second, teams);
    if (playedMatches.find(match) != playedMatches.end())
        FAIL("Any two teams must play exactly one game");
    if (playedMatches.find(make_pair(match.second, match.first)) != playedMatches.end())
        FAIL("Any two teams must play exactly one game");
    playedMatches.insert(match);
}


typedef pair<int, int> TMatchResult;
TESTLIB_VALIDATE() {
    size_t n = inf.read<size_t>(1, MAXN);
    inf.readEoln();
    set<string> teams;
    for (size_t i = 0; i < n; ++i) {
        string curTeam = inf.read<string>(MAX_LEN_TEAM);
        for (size_t j = 0; j < curTeam.length(); ++j) {
            verify(curTeam[j] <= 'z' && 'a' <= curTeam[j], Verdict::FAIL, "Incorrect team name"); // проверяем, что имя команды состоит из строчных латинских букв
        }
        verify(teams.find(curTeam) == teams.end(), Verdict::FAIL, "No same team names!");
        teams.insert(curTeam);
        inf.readEoln();
    }
    set<TMatch> playedMatches; // храним множество пар команд, которые уже играли друг с другом
    for (size_t i = 0; i < n * (n - 1) / 2; ++i) {
        TMatch match = inf.read<TMatch>(make_default_reader<string>(MAX_LEN_TEAM), ' '); // читаем пару строк через пробел
        addMatch(match, teams, playedMatches);
        inf.readChar(' ');
        inf.read<TMatchResult>(make_default_reader<int>(0, 10), " : "); // читаем пару чисел (каждое из которых от 0 до 10) с разделителем " : "
        inf.readEoln();
    }
    // Валидатор проверит, что больше ничего в тесте нет (даже пробелов и переводов строк!) и вернет ОК.
}
~~~~~~~~~~~~~~~

Более подробно обо всех функциях библиотеки можно прочитать [в документации](#general_documentation).
