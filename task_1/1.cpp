Class ComplexNumber {
public:
	void SetRe(const double& x);
	void SetIm(const double& x);
private:
	double Re;
	double Im;
}

constexpr ComplexNumber Conjugate(const ComplexNumber& x) {
	ComplexNumber res;
	res.SetRe(x.GetRe());
	res.SetIm(-x.GetIm());
	return res;
}

int main() {
	constexpr ComplexNumber a(1, 2);
	constexpr ComplexNumber b(1, -2);
	constexpr auto c = Conjugate(a);
	static_assert(b == c, "failed");
}