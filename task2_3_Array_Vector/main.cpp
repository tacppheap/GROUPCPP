#include "Vector.h"
#include "Array.h"
#include <cstdlib>
#include <string>


void po_value(Vector<int> a)
{
	cout << "\n\nIncide po_value\n\n";
}
void main()
{

	{
		//Vector<int> a = 5;
		Vector<int> a(5);
		po_value(a);
		Vector<int> b(5);
		a.insert(0, 1);
		a.insert(1, 2);
		a.insert(3, 4);
		a.insert(4, 5);
		b.insert(0,6);
		b = a;
		Vector<int> c(b);
	}

	std::system("pause");

}