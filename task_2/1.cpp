#include <iostream>
#include <vector>

int main() {
    std::vector<bool> v = {true, false};

    for (auto&& x : v ) {
    	std::cout << typeid(x).name() << std::endl;
    }

	for (auto& x : v ) {
		std::cout << typeid(x).name() << std::endl;
	}
	/*Во втором случае возникает ошибка компиляции,
	  так как спользует вспомогательный ссылочный класс,
	  rvalue-объект которого не может быть связан с неконстанной ссылкой
	  (объяснение ошибки подсмотрено на просторах интернета)*/
}