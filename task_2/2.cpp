#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <tuple>
#include <vector>
#include <set>

struct Printer {
private:
    inline static std::stringstream buffer;
public:
    std::string str() const { 
        std::string s = buffer.str();
        buffer.str("");
        return s;
    }

    template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
    Printer& format(const T& t) {
        buffer << t;
        return *this; 
    }

    Printer& format(const std::string& t) {
        buffer << t;
        return *this; 
    }

    template<typename T1, typename T2>
    Printer& format(const std::pair<T1, T2>& t) {
        buffer << "( " << format(t.first).str() << ", " << format(t.second).str() << " )";
        return *this; 
    }

    template<typename... T>
    Printer& format(const std::tuple<T...>& t) {
        buffer << "( ";
        std::apply([this](auto&&... args) {((buffer << format(args).str() << ", "), ...);}, t);
        buffer.seekp(-2, std::ios_base::end);
        buffer << " )";
        return *this; 
    }

    template<typename T>
    Printer& format(const std::vector<T>& t) {
        buffer << "[ ";
        for (auto elem : t) {
            buffer<< format(elem).str() << ", " ;
        }
        buffer.seekp(-2, std::ios_base::end);
        buffer << " ]";
        return *this; 
    }

    template<typename T>
    Printer& format(const std::set<T>& t) {
        buffer << "{ ";
        for (auto elem : t) {
            buffer<< format(elem).str() << ", " ;
        }
        buffer.seekp(-2, std::ios_base::end);
        buffer << " }";
        return *this; 
    }
};

template<typename T>
std::string format(const T& t) {
    return Printer().format(t).str();
};

int main() {
    std::pair<std::string, std::pair<int, int>> p = {"xyz", {1, 4}};
    std::tuple<std::string, int, int> t = {"xyz", 1, 2};
    std::vector<std::pair<int, int> > v = {{1, 4}, {5, 6}};
    std::set<std::pair<int, int> > s = {{2, 2}, {1, 1}};

    std::cout << "My tests\n\n";

    std::cout << Printer().format("Double format: ").format(3335125366).format(" I love it!!!\n").str();
    std::cout << Printer().format("I love it 2\n").str();
    std::cout << Printer().format("pair: ").format(p).format("\n").str();
    std::cout << Printer().format("tuple: ").format(t).format(" ! ").format("\n").str();
    std::cout << Printer().format("vector: ").format(v).format("\n").str();
    std::cout << Printer().format("set: ").format(s).format("\n\n").str();

    std::cout << "Not my tests\n\n";

    std::string s1 = Printer().format(" vector: ").format(v).str();
    std::string s2 = Printer().format(t).format(" ! ").format(0).str();
    std::cout << s1 << "\n";
    std::cout << s2 << "\n";
}