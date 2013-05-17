General documentation {#general_documentation}
=========

__Обратите внимание, что мы используем неточные сигнатуры функций.__  
В частности: не указаны (где неважно) ссылки, const-модификаторы; упрощены возвращаемые типы (без `enable_if`).  
За подробностями вы можете обратиться к исходному коду.
+ <a id="IStream"></a> `class IStream` - класс для работы со stream-ами.
  В валидаторе доступен 1 поток `inf`, в чекерах - 3 потока: 
  + `T read<T>(Reader<T> reader, args...)` - чтение с помощью [reader](#Reader) с аргументами `args`.
  + `T read<T>(args...)` - чтение с помощью [Reader по умолчанию](#DefaultReader) с аргументами `args`.
  + `void fill(T& var, args...)` - считать значение типа `T` в переменную `var`.
  + `operator >> (T& var)` - то же, что fill без аргументов. Возвращает `*this`.
  + `void setStrict()`, `void setNonStrict()` - установить строгость потока. По умолчанию STRICT для валидатора, NON_STRICT для чекера. В нестрогом режиме игнорирутся пробельные символы.  
  + `Mode getMode()` - возвращает уровень строгости потока (STRICT или NON_STRICT).
  + `readEof()` - убедиться, что читать нечего.
  + `readToken()` - считать токен. Если режим нестрогий, то сначала будут пропущены все пробельные символы (`' '`, `'\n'`, `'\r'`, `'\t'`), а потом будет считан токен до первого пробельного символа. Если токен пустой, то presentation error.
  + `readChar()` - считать следующий символ.
  + `readChar(char c)` - убедиться, что следующий символ - это символ `c`, и считать его.
  + `readSpace()`, `readEoln()` - прочитать пробел и перенос строки соответственно.
  + `bool seekEoln()`(`bool seekEof()`) - проверить, дочитана ли строка (поток).  
 
  По возможности следует избегать в чекерах и валидаторах следующие низкоуровневые методы:
  + `int peek()` - просмотреть следующий символ без чтения. `EOF`, если поток пуст.
  + `int get()` - прочитать следующий символ. `EOF`, если поток пуст.  

<br/>
+ <a id="DefaultReader"></a> `class DefaultReader<T>` - способ чтения по умолчанию. См. [Reader](#Reader)  
  Реализован для следующих типов:
  + [Целочисленные типы (все встроенные)](Default-Readers-Documentation#wiki-int)
  + [Числа с плавающей точкой (типы float, double, long double)](Default-Readers-Documentation#wiki-float)
  + [char](Default-Readers-Documentation#wiki-char)
  + [std::vector](Default-Readers-Documentation#wiki-vector)
  + [std::pair](Default-Readers-Documentation#wiki-pair)
  + [std::string](Default-Readers-Documentation#wiki-string)

<br/>
+ <a id="Reader"></a>`class Reader<T>`
  Reader - класс для чтения данных. Передается в `IStream::read()`.
  Принимает stream и произвольное число аргументов.
  См. также 
  + [DefaultReader](#DefaultReader)
  + [Reader с зафиксированными аргументами](Reader с зафиксированными аргументами)
  + [Написание собственного Reader'а](Написание собственного Reader'а)

<br/>
+ <a id="Alias"></a>`class Alias`
  Нужен для того, чтобы использовать по умолчанию другой `Reader`.
  Использование:
  `typedef Alias<string, LineReader> Line;`, после чего можно использовать Line, как строку (по умолчанию она будет читаться построчно). Реализована неявная конвертация в обе стороны.
  `string nextLine = inf.read<Line>();`

<br/>
+ <a id="Separator"></a> `class Separator` - класс, который содержит в себе строку, которую он будет пытаться читать при вызове метода `read()`.  
  Конструкторы:  
  + `Separator(char c)`
  + `Separator(char* c)`  
  + `Separator(string c)`  

  Имеет единственный метод `read()`, который пытается прочитать допустимую строку.  

<br/>
+ Написание чекеров и валидаторов.
  + Чекеры: 
  ```cpp
  TESTLIB_CHECK() {
    //your code;
    //Здесь доступны 3 потока(IStream&)
    //`inf` - с входными данными
    //`ouf` с выходными
    //`ans` с правильным ответом.
  }
  ```

  + Валидаторы:
  ```cpp
  TESTLIB_VALIDATE() {
    // validator code
    // Здесь доступен поток(IStream&) inf.
  }
  ```

<br/>
+ Коды возврата.  
  По умолчанию используются стандартные коды возврата:
  + OK 0
  + WA 1
  + PE 2
  + FAIL 3
  + `частичный результат X` X

  При определении константы `EJUDGE` коды возврата меняются:
  + WA 5
  + PE 4
  + FAIL 6

  При определении константы `TESTSYS` `частичный результат X` - `X + 50`.
  Так же можно явно указать свои коды возврата, используя константы `OK_EXIT_CODE`, `WA_EXIT_CODE`, `PE_EXIT_CODE`, `FAIL_EXIT_CODE`, `PARTIALLY_EXIT_CODE`, используя либо `define` __перед__ `#include "testlib.hpp"`, либо опции компиляции. Последняя опция отвечает за константу, которая прибавляется к возвращаемому значению. Например, чтобы показать `частично верно 10`, возвращается `PARTIALLY_EXIT_CODE + 10`. 

  В чекере вы можете управлять результатом вывода следующими способами:

  + Макросы `QUIT(Verdict, msg)`, `WA(msg)`, `OK(msg)`, `FAIL(msg)`, `PE(msg)`. Обратите внимание, что msg может содержать в себе `<<` для вывода нескольких объектов. Пример: `WA("bad number " << n);`
  + Макрос `ensure(condition)` падает c FAIL, если `condition` ложно.
  + Макрос `verify(condition, verdict, msg)`. Тоже, что `ensure`, но падает с вердиктом `verdict` и выводит сообщение `msg`. `msg` - то же, что и в `QUIT()`.
  + Функции `verify*(..., verdict);` Проверяет, что условие, соответствующее названию, выполняется. В противном случае возвращается `verdict`.  
  + `verifyEqual(T a, T b, verdict, equal = std::equal_to<T>)` - простая проверка на равенство компаратором `equal`. Если равенство не выполняется, то возвращается `verdict`.  
  + `verifySorted(Iter start, Iter end, verdict, compare = std::less<*Iter>)` - проверяет, что диапазон `[start, end)` отсортирован (по умолчанию по возрастанию). Если это не выполняется, то возвращается `verdict`.  
  + `verifyEqualRange(Iter start1, Iter end1, Iter start2, Iter end2)` - проверяет, что диапазоны `[start1, end1)`, `[start2, end2)` равны. Если это не выполняется, то возвращается `verdict`.  

  + Стандартные ридеры сообщают об ошибках чтения.

<br/>
+ Вывод данных
  + `string toString(T value)` - возвращает строковое представление `value`. Используется `operator <<` для `ostream`.  
  + `string rangeToString(T begin, T end)` - строковое представление коллекции (`[` в начале, потом элементы коллекции, разделенные `, `, в конце `]`).  
  + `string toPrint(T value)` - представление для вывода чекера/валидатора. В данный момент обрамляет в кавычки и оставляет начало и конец строки, заменяя остальное многоточием, если строка длинная (т.е. больше 70 символов).  
  + <a id="expectation"></a> `string expectation(T expected, U found)` - возвращает "`expected` expected, `found` found".

<br/>
+ Другие полезные функции:
  + `string englishEnding(n)` - возвращает последние 2 буквы записи порядкого числительного `n` на английском языке.  
  + `bool areClose(T expected, T value, T eps)` - возвращает `true`, если абсолютная или относительная погрешность не превосходит `eps`.
