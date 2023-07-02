#include <iostream>
#include <exception>

/** \brief a determinant of 4 orbitals
 *
 *  a determinant of 4 orbitals with the orbital in positions 1 and 3
 *  being alpha electrons, and positions 2 and 4 being beta electrons.
 *  When stored i1 < i3, and i2 < i4.
 */
class determinant {
    int sign = 1;
    std::vector<int> orbs{0,0,0,0};
    std::string coefficient;
public:
    determinant(const char* name, int a, int b, int c, int d) {
        sign = 1;
        if (a == c) throw std::logic_error("determinant: a == c"); 
        if (b == d) throw std::logic_error("determinant: b == d"); 
        if (a > c) {
            int t = c;
            c = a;
            a = t;
        }
        if (b > d) {
            int t = d;
            d = b;
            b = t;
        }
        orbs[0] = a;
        orbs[1] = b;
        orbs[2] = c;
        orbs[3] = d;
        coefficient = name;
    }
    determinant(determinant& orig) {
        sign = orig.sign;
        orbs[0] = orig.orbs[0];
        orbs[1] = orig.orbs[1];
        orbs[2] = orig.orbs[2];
        orbs[3] = orig.orbs[3];
        coefficient = orig.coefficient;
    }
    determinant& operator=(determinant& orig) {
        this->sign = orig.sign;
        this->orbs[0] = orig.orbs[0];
        this->orbs[1] = orig.orbs[1];
        this->orbs[2] = orig.orbs[2];
        this->orbs[3] = orig.orbs[3];
        this->coefficient = orig.coefficient;
        return *this;
    }
    void swap_a() {
        int t = orbs[0];
        orbs[0] = orbs[2];
        orbs[2] = t;
        sign = -sign;
    }
    void swap_b() {
        int t = orbs[1];
        orbs[1] = orbs[3];
        orbs[3] = t;
        sign = -sign;
    }
    friend std::string integrate_34(const determinant& bra, const determinant& ket);
    friend std::bool match_34(std::string& out, const determinant& bra, const determinant& ket);
};

std::bool match_34(std::string& out, const determinant& bra, const determinant& ket) {
    if (bra.orbs[3] == ket.orbs[3] && bra.orbs[4] == ket.orbs[4]) {
        if (bra.sign*ket.sign > 0) {
            out = '+';
        }
        else {
            out = '-';
        };
        out.append(bra.coefficient);
        out.append(ket.coefficient);
        return True;
    }
    else {
        return False;
    };
}

std::string integrate_34(const determinant& bra, const determinant& ket) {
    auto bra2 = bra;
    auto ket2 = ket;
    std::string out('0');
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_b();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_b();

    bra2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_b();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_b();

    bra2.swap_b();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_b();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_b();

    bra2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_b();
    if (match_34(out,bra2,ket2)) return out;
    ket2.swap_a();
    if (match_34(out,bra2,ket2)) return out;
    return out;
}

class wavefunction {
    std::vector<determinant> terms;
public:
    wavefunction() { };
    wavefunction(const wavefunction& in_wfn) {
        terms = in_wfn.terms;
    }
    wavefunction& operator=(const wavefunction& in_wfn) {
        this->terms = in_wfn.terms;
        return *this;
    }
    void add(const determinant& det) {
        this->terms.push_back(det);
    }

}

int main(int argc, char* argv[]) {
    
}
