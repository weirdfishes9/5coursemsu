#include <array>
#include <iostream>

template <int N>
constexpr std::array<int, N-1> myErase(const std::array<int, N>& str, int index) {
	std::array<int, N-1> res = {{}};
	for (int i = 0; i < index; i++) {
		res[i] = str[i];
	} 
	for (int i = index + 1; i < N; i++) {
		res[i-1] = str[i];
	}
	return res;
}

template <int N>
constexpr std::array<std::array<int, N-1>, N-1>
getMinor(const std::array<std::array<int, N>, N>& a, int str, int col) {
	std::array<std::array<int, N-1>, N-1> res = {{{}}};
	for (int i = 0; i < str; i++) {
		res[i] = myErase<N>(a[i], col);
	} 
	for (int i = str + 1; i < N; i++) {
		res[i-1] = myErase<N>(a[i], col);
	}
	return res;
}

template <int N>
constexpr int det(const std::array<std::array<int, N>, N>& a) {
	int res = 0;
	int odd = 1;
	for (int i = 0; i < N; i++) {
		res = (N == 1) ? a[0][0] : res + odd * a[0][i] * det<N-1>(getMinor<N>(a, 0, i));
		odd *= -1;
	}
	return res;
}

template <>
constexpr int det<1>(const std::array<std::array<int, 1>, 1>& a) {
	return a[0][0];
}

int main() {
	constexpr std::array<std::array<int, 3>, 3> A = {{
		 {0, 1, 2}
		,{1, 2, 3}
		,{2, 3, 7}
	}};
	constexpr int res = det<3>(A);
}