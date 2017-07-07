#include "Vector/Vector.h"
#include "Array/Array.h"
#include <cstdlib>
#include <string>
#include "my_print.h"
#include "Smart_Pointers/auto_ptr/my_auto_ptr.h"
#include "Smart_Pointers/uniq_ptr/my_unique_ptr.h"
#include "Smart_Pointers/shared_ptr/my_shared_ptr.h"
#include "Stack/Stack.h"
#include "Assembler/Translator/my_translator.h"
#include "Assembler/Processor/my_processor.h"
#include <memory>



/*Vector<int>* pv = new Vector<int>(5);
Vector<int>* f()
{
	return pv;
}

Vector<int>* pv1 = new Vector<int>(5);
Vector<int>* f1()
{
	return pv1;
}*/

int fact(int a)
{
	if (a == 1) return 1;
	return a * fact(a - 1);
}





void main()
{

	

	{


		
		ERROR_CODE error =  my_translator::translate("D:\\1.txt", "D:\\2.txt");
		std::cout << "\n" << error;
		my_processor proc;
		proc.RecognizeWhatTODO("D:\\2.txt");
		proc.Execute();




		/*char buf[4];
		std::string _string = "12340";
		int temp = 0;
		size_t ssize = _string.size();
		for (int i = 0; i < ssize; i++)
		{
			temp += pow(10, i) * (_string[ssize - i - 1] - '0');
		}
		memcpy(buf, &temp, sizeof(int));
		for (int i = 0; i <4; i++)
		{
			std::cout << buf[i];
		}*/

		//r("1");

		//my_translator::translate("D:\\1.txt", "D:\\2.txt");
		
		/*Vector<Vector<int>> p;
		p = Vector<Vector<int>>{ Vector<int>(), Vector<int>(), Vector<int>() };*/
	}
	system("pause");
	/*{

		Stack<int, 2> s;
		s.pop();
		s.push(1);
		s.push(2);
		s.push(3);
		int a = s.pop();
		int b = s.pop();
		int c = s.pop();
		int d = s.top();
		d = 10;

		std::cout << a << "    " << b << "    " << c << "    " << d;

		s.pop();








	}*/

	{
		/*Array<int, 5> a{ 1,2,3,4,5 };
		Array<int, 5> b(a);*/

	
	}
	/*{
	
		int a1 = 1;
		Vector<int> a (0);

		

		TA::shared_ptr<Vector<int>> p(f());

		TA::shared_ptr<Vector<int>> p1(f1());

		TA::shared_ptr<Vector<int>> p2(f());
		
		p.~shared_ptr();
		p1.~shared_ptr();
		p2.~shared_ptr();
		std::cout << "END";
	}
	std::system("pause");
	{
		Vector<int>* pp = new Vector<int>();
		TA::unique_ptr<Vector<int>> p(new Vector<int>());
		TA::unique_ptr<Vector<int>> p1(unique_ptr<Vector<int>>(new Vector<int>()));
		try
		{
			std::cout << (*p).size();
		}
		catch(TA::no_init error)
		{
			std::cout << "!!!";
		}


	}/*
	std::system("pause");
	/*{

		Array<int, 1> a;
		for (array_iterator<int> it = a.begin(); it != a.end(); it++)
		{
			std::cout << "\n\n\n" << *it << "\n\n\n";
		}
		
	}*/
	/*{
		
		TA::print("1:#, 2:#, 3:#", 1, 2, 3);

		Vector<bool> b{0,0,0,0,0,0,1};
		b = b;
		Vector<bool> a(b);
		Vector<bool> c;

		b.push_back(1);

		for (vector_iterator<bool> it = c.begin(); it != c.end(); it++)
		{
			std::cout <<"\n\n\n"<< *it<<"\n\n\n";
		}


		std::cout << "\n\n\n";*/



		

		
		

	/*	for (array_iterator<bool> it = b.begin(); it != b.end(); it++)
		{
			std::cout<<"\n\n\n" << *it<<"\n\n";
		}*/
		
	//	b = a;

	//}

	std::system("pause");

	/*{
		Vector <long float> a{1,2,3};
		a.push_back(4);
		Vector<long float> b;
		b = a;

		for (vector_iterator<long float> it = b.begin(); it != b.end(); it++)
		{
			std::cout << "\n\n\n" << *it << "\n\n";
		}

	}*/

	std::system("pause");

}