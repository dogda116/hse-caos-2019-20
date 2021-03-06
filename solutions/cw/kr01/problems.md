# Problem kr01-1: КР 1-1

На стандартном потоке ввода задаются два числа: x — 64-битное знаковое целое число в десятичном виде, и b (1 < b < 1000) — основание системы счисления — целое число в десятичном виде.

На стандартный поток вывода напечатайте сумму цифр числа x, записанного в системе счисления по основанию b. Сумму цифр выводите в десятичной системе счисления. Число x может быть отрицательным, знак числа цифрой не является.

Не забывайте выводить \n в конце вывода.

## Examples
###### Input
```
12345 10
```
###### Output
```
15
```
###### Input
```
2746 16
```
###### Output
```
31
```

# Problem kr01-2: КР 1-2
На стандартном потоке ввода подается последовательность символов, которая заканчивается с признаком конца ввода. Словом назовем последовательность строчных латинских букв ('a' - 'z'), идущих в тексте подряд, и максимально возможной длины. То есть, текст 'abcd.' содержит одно слово 'abcd', а не, например, два слова 'a' и 'bcd'. На стандартный поток вывода напечатайте длину самого длинного слова в тексте, не содержащего букву 'q'.

## Input format
На стандартном потоке ввода подается последовательность символов, которая заканчивается с признаком конца ввода.

## Output format
На стандартный поток вывода выведите одно число — длину самого длинного слова, не содержащего 'q', в тексте. Если такое слово отсутствует, выведите 0.

Не забывайте выводить \n в конце вывода.

## Examples
###### Input
```
a abcd qabcd.
```
###### Output
```
4
```

# Problem kr01-3: КР 1-3
На стандартном потоке ввода задаются два 32-битных знаковых числа a и b. В множестве 32-битных знаковых чисел найдите число c, такое, что с делится нацело на b и |a − c| минимально. Если таких чисел несколько, выберите из них максимальное.

## Input format
Число a — 32-битное знаковое целое. Число b — положительное 32-битное знаковое целое.

## Output format
На стандартный поток вывода выведите число c.

Не забывайте выводить \n в конце вывода.

## Examples
###### Input
```
2
4
```
###### Output
```
4
```

# Problem kr01-4: КР 1-4
На стандартном потоке ввода вводятся два положительных целых числа ez, mz (ez + mz ≤ 63), задающие размер поля порядка в битах и размер поля мантиссы в битах для представления чисел с плавающей точкой, полностью аналогичному стандарту IEEE 754, но с другими размерами полей. В этом представлении чисел используются те же принципы, что и в стандарте, то есть поля числа располагаются в последовательности (бит_знака, порядок, мантисса) от старшего бита к младшему. Порядок хранится со смещением (bias), старший бит мантиссы всегда равен 1 и не хранится. В представлении поддерживается знаковый ноль, денормализованные числа, бесконечность и "не число" (NAN).

Далее на стандартном потоке ввода вводятся 64-битные целые беззнаковые значения в десятичном представлении, побитово кодирующие вещественные числа, описанные выше. Если для представления вещественного числа требуется меньше 64 бит, старшие биты вводимых целых чисел равны 0. Среди вводимых чисел не встречаются денормализованные значения, а также "бесконечность" и "не число".

Преобразуйте каждое введенное число в значение типа double в предположении, что тип double — это IEEE 754 тип двойной точности. При этом если порядок введенного числа слишком велик для double, преобразуйте его в бесконечность соответствующего знака, а если слишком мал, то в 0 соответствующего знака. Если биты мантиссы введенного числа не помещаются в биты мантиссы типа double, лишние биты мантиссы отбросьте.

Каждое преобразованное число напечатайте на стандартный поток вывода в шестнадцатеричном виде, то есть с помощью форматного преобразования %a. После каждого числа выводите символ перехода на новую строку.

Описанное выше преобразование однозначно, поэтому ваш ответ будет сравниваться с эталонным на точное совпадение.

В примере ниже параметры 8, 23 задают представление чисел с плавающей точкой, совпадающее с типом float.

## Examples
###### Input
```
8 23
1065353216
1073741824
3231711232
1078530010
3645061860
```
###### Output
```
0x1p+0
0x1p+1
-0x1.4p+2
0x1.921fb4p+1
-0x1.8675c8p+51
```
# Problem kr01-5: КР 1-5
Черно-белый сканер отсканировал квадратный лист черного цвета, на котором возможно находился ровно один белый прямоугольник со сторонами, параллельными сторонам листа. Результат сканирования передается в виде потока бит, записанных в 16-ричной системе счисления, причем более левый пиксель изображения кодируется более старшим битом 16-ричной цифры. Например, пиксели #.#., где # — это черная точка, а . — это белая точка, будут закодированы как шестнадцатеричная цифра a.

Напишите программу, которая по потоку бит, подаваемому на стандартный поток ввода, определит размер листа и координаты углов белого прямоугольника на листе. Гарантируется, что лист квадратный, размер стороны положителен, не превышает 10000 и кратен 8. Гарантируется, что белый прямоугольник не касается краев листа, то есть вокруг него всегда есть черная рамка.

## Input format
На стандартный поток ввода подаются шестнадцатеричные цифры (0-9, a-f, A-F). Цифры могут разделяться произвольным количеством пробельных символов (whitespace characters).

## Output format
Если на листе отсутствует белый прямоугольник выведите 5 чисел: размер листа и 4 нуля.

Если белый прямоугольник присутствует, выведите 5 чисел: размер листа, координаты левого верхнего угла и правого нижнего угла. Каждая координата записывается в виде пары чисел: номер строки (отсчитывается сверху листа от 0) и номер столбца (отсчитывается слева листа от 0).

Не забывайте выводить \n в конце вывода.

## Examples
###### Input
```
ffffffff803f803f803f803f803f803f
803fffffffffffffffffffffffffffff
```
###### Output
```
16 2 1 8 9
```
###### Input
```
fffff fffffffffff
```
###### Output
```
8 0 0 0 0
```
