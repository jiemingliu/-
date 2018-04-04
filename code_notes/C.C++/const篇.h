const限定符的讲解
1.声明变量只能被读
2.必须初始化
3.在另一连接文件中使用const常量不能再次赋值  extern const int i；
4.可以避免不必要的内存分配，const常量在程序运行中只有一份拷贝，而#define定义的常量在内存中有多个拷贝
5.可以通过函数进行初始化
	int function();
	const int &i=function();
6.通过强制类型转换，将地址赋给变量，再作修改即可以改变const常量值
	const int i=0;
	int *p=(int*)&i;
	p=100;
7.便于进行类型检查
8.  int i=0；					
	const int j=0;				//j是常量，值不会被修改
	const int* p1=&j;			//指针p1所指内容是常量，可以不初始化
	int* const p2=&i;			//指针p2是常量，所指内容可修改
	const int* const p3=&j;		//指针p3是常量，所指内容也是常量
	p1=&i;
	*p2=100;
9.const修饰类的数据成员，不能在类声明中初始化const数据成员，const成员的初始化只在构造函数的初始化列表中进行，如需要建立整个类中都恒定的常量，应该在类中枚举常量来实现
10.const修饰类的成员函数，任何不会修改数据成员的函数和不会调用其他非const成员函数的函数都应该声明为const类型，const关键字只能放在函数声明的尾部
11.const修饰函数的参数
	a.const只能修饰输入参数，如果输入参数采用“指针传递”，那么加const修饰可以防止指针被意外修改；如果采用“值传递”，则不需加const修饰
	b.对于非内部数据类型的输入参数，应该将“值传递”的方式改为“const 引用传递”，提高效率
	  对于内部数据类型的输入参数，则不需要“const 引用传递”
12.const修饰函数的返回值，一般是给以“指针传递”方式的函数返回值加const修饰，那么函数返回值(即指针)指向的内容不能被修改，而且返回值只能被赋给加const修饰的同类型指针