class ComplexNumber {
    int Re;
    int Im;
public:
    constexpr ComplexNumber() : Re(0), Im(0) {}
    constexpr ComplexNumber(const int& a, const int& b) : Re(a), Im(b) {}
    constexpr void operator=(const ComplexNumber& c) {
        Re = c.Re;
        Im = c.Im;
    }
    constexpr bool operator==(const ComplexNumber& c) const {
        return (Re == c.Re) && (Im == c.Im);
    }
    constexpr int GetRe() const { return Re; }
    constexpr int GetIm() const { return Im; }
    constexpr void SetRe(const int& x) { Re = x; }
    constexpr void SetIm(const int& x) { Im = x; }
};

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