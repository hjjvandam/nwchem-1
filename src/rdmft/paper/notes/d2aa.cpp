#include <iostream>
#include <exception>

/** \brief a determinant of 4 orbitals
 *
 *  a determinant of 4 orbitals with the orbital in positions 1 and 3
 *  being alpha electrons, and positions 2 and 4 being beta electrons.
 */
class determinant {
    int sign = 1;
    std::vector<int> orbs{0,0,0,0};
    std::string coefficient;
public:
    determinant(const char* name, const int a, const int b, const int c, const int d) {
        sign = 1;
        if (a == c) throw std::logic_error("determinant: a == c"); 
        if (b == d) throw std::logic_error("determinant: b == d"); 
        orbs[0] = a;
        orbs[1] = b;
        orbs[2] = c;
        orbs[3] = d;
        coefficient = name;
    }
    determinant(const determinant& orig) {
        sign = orig.sign;
        orbs[0] = orig.orbs[0];
        orbs[1] = orig.orbs[1];
        orbs[2] = orig.orbs[2];
        orbs[3] = orig.orbs[3];
        coefficient = orig.coefficient;
    }
    determinant& operator=(const determinant& orig) {
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
    friend std::string integrate_24(const determinant& bra, const determinant& ket);
    friend bool match_24(std::string& out, const determinant& bra, const determinant& ket);
    friend bool matchup_13(determinant& det, const int a, const int b);
    friend std::ostream& operator<<(std::ostream& os, const determinant& det);
};

std::ostream& operator<<(std::ostream& os, const determinant& det) {
    if (det.sign > 0) {
        os << "+";
    }
    else {
        os << "-";
    }
    os << det.coefficient << "[" << det.orbs[0] << det.orbs[1] 
                                 << det.orbs[2] << det.orbs[3] << "]";
    return os;
}

bool match_24(std::string& out, const determinant& bra, const determinant& ket) {
    if (bra.orbs[1] == ket.orbs[1] && bra.orbs[3] == ket.orbs[3]) {
        if (bra.sign*ket.sign > 0) {
            out = '+';
        }
        else {
            out = '-';
        };
        out.append(bra.coefficient);
        out.append(ket.coefficient);
        return true;
    }
    if (bra.orbs[1] == ket.orbs[3] && bra.orbs[3] == ket.orbs[1]) {
        if (bra.sign*ket.sign > 0) {
            out = '-';
        }
        else {
            out = '+';
        };
        out.append(bra.coefficient);
        out.append(ket.coefficient);
        return true;
    }
    return false;
}

/** \brief Try if we can match up orbitals 1 and 3 with a and b
 *
 *  If we can apply a permutation such that orbitals 1 and 3 match
 *  a and b, then return true and return the determinant with this
 *  permutation.
 *
 */
bool matchup_13(determinant& det, const int a, const int b) {
    if (det.orbs[0] == a && det.orbs[2] == b) return true;
    det.swap_a();
    if (det.orbs[0] == a && det.orbs[2] == b) return true;
    det.swap_a();
    return false;
}

void integrate_24(std::string& out, const determinant& bra, const determinant& ket) {
    auto bra2 = bra;
    auto ket2 = ket;
    match_24(out,bra2,ket2);
}

class wavefunction {
    std::vector<determinant> terms;
public:
    wavefunction() { };
    wavefunction(const wavefunction& in_wfn) {
        terms = in_wfn.terms;
    }
    wavefunction(const wavefunction& in_wfn, const int a, const int b) {
        for (auto det: in_wfn.terms) {
            if (matchup_13(det,a,b)) {
                this->terms.push_back(det);
            }
        }
    }
    wavefunction& operator=(const wavefunction& in_wfn) {
        this->terms = in_wfn.terms;
        return *this;
    }
    void add(const determinant& det) {
        this->terms.push_back(det);
    }
    const std::vector<determinant> dets() const {
        return this->terms;
    }
    friend std::ostream& operator<<(std::ostream& os, const wavefunction& wfn);
};

std::ostream& operator<<(std::ostream& os, const wavefunction& wfn) {
    for (auto det: wfn.terms) {
        os << det << std::endl;
    }
    return os;
}

void integrate_24(std::string& str, const wavefunction& wbra, const wavefunction& wket) {
    std::string tmp("");
    for (auto bra: wbra.dets()) {
        for (auto ket: wket.dets()) {
            std::string out("");
            integrate_24(out,bra,ket);
            if (out.length() > 0) {
                if (tmp.length() == 0) tmp.append("\\begin{array}{l}\n");
                tmp.append(out);
                tmp.append(" \\\\\n");
            }
        }
    }
    if (tmp.length() == 0) {
        tmp.append("0");
    }
    else {
        tmp.append("\\end{array}");
    }
    str.append(tmp);
}

/** \brief Add the LaTeX expression for the alpha-alpha block of the 2-electron density matrix
 *
 *  Given a wavefunction as the sum of Slater determinants generate
 *  the expression for the 2-electron density matrix and add it to the
 *  string argument. Note that the bra and ket wavefunctions are assumed
 *  to be expressed in the same orbital basis.
 *
 */
void build_d2aa(std::string& str, const wavefunction& wbra, const wavefunction& wket){
    str.append("\\begin{eqnarray}\nD_2 &=&\n\\begin{pmatrix}\n");
    for (int bra_a = 1; bra_a <= 4; bra_a++) {
        for (int bra_b = 1; bra_b <= 4; bra_b++) {
            if (bra_a == bra_b) continue;
            wavefunction wsbra(wbra,bra_a,bra_b);
            for (int ket_a = 1; ket_a <= 4; ket_a++) {
                for (int ket_b = 1; ket_b <= 4; ket_b++) {
                    if (ket_a == ket_b) continue;
                    wavefunction wsket(wket,ket_a,ket_b);
                    std::string tmp("");
                    integrate_24(tmp,wsbra,wsket);
                    str.append(tmp);
                    if (ket_a == 4 && ket_b == 3) {
                        str.append(" \\\\\n");
                    }
                    else {
                        str.append(" &\n");
                    }

                }
            }
        }
    }
    str.append("\\end{pmatrix}\n\\end{eqnarray}\n");
}

int main(int argc, char* argv[]) {
    wavefunction wfn;
    wfn.add(determinant("c_{1122}",1,1,2,2));
    wfn.add(determinant("c_{1133}",1,1,3,3));
    wfn.add(determinant("c_{1144}",1,1,4,4));
    wfn.add(determinant("c_{2233}",2,2,3,3));
    wfn.add(determinant("c_{2244}",2,2,4,4));
    wfn.add(determinant("c_{3344}",3,3,4,4));
    wfn.add(determinant("c_{1234}",1,2,3,4));
    wfn.add(determinant("c_{2143}",2,1,4,3));
    wfn.add(determinant("c_{1243}",1,2,4,3));
    wfn.add(determinant("c_{2134}",2,1,3,4));
    wfn.add(determinant("c_{1324}",1,3,2,4));
    wfn.add(determinant("c_{3142}",3,1,4,2));
    std::string eq("");
    build_d2aa(eq,wfn,wfn);
    std::cout << eq << std::endl;
}
