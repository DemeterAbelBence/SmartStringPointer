#include <iostream>
#include "mystring.hpp"

/*
	Nev: Demeter Abel Bence
	Neptun: 
	Megjegyzes: A memoriaszivargast a visualstudio2022 beepitett crtdbg eszkozevel vegeztem es az alabbi 
				teszteleshez hasznalt program eseten nem jelzett memoriaszivargast
*/

int main(void) {
	try {
		// + es += teszt
		MyString a = "korte";
		MyString b = "ALMA";
		std::cout << a + b << std::endl;
		std::cout << a + 'C' << std::endl;
		b += a;
		std::cout << b << std::endl;
		a += 'K';
		std::cout << a << std::endl;
		std::cout << std::endl;


		// index teszt
		MyString c("narancs");
		const MyString d = c;
		std::cout << d[0] << std::endl;
		c[0] = 'b';
		std::cout << c << std::endl;
		std::cout << d << std::endl;
		std::cout << std::endl;


		// jobbertek teszt
		MyString e(MyString("ananasz"));
		e = MyString("dinnye");
		std::cout << e << std::endl;
		std::cout << std::endl;


		// beolvasas teszt
		MyString f;
		std::cout << "Add meg f erteket:" << std::endl;
		std::cin >> f;
		std::cout << f << std::endl;
		std::cout << std::endl;


		//pelda1 teszt
		MyString g, h, i;
		g = h = i = "hello vilag";


		// pelda2 teszt
		MyString j = "hello";
		MyString k = j;
		k[0] = 'c';
		std::cout << k;    
		std::cout << j;
		std::cout << std::endl;
	}
	catch (const std::runtime_error& error){
		std::cout << error.what() << std::endl;
	}
}