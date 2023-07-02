/** \brief Program to work out permutations of 4 different orbital indeces
 *
 *  In this case we have 4 orbitals labeled 1, 2, 3, and 4. We need to find all
 *  possible orderings of these labels. In addition the positions 1 and 3 refer
 *  to alpha electrons and positions 2 and 4 refer to beta electrons. So we create
 *  all orderings and keep those the label at position 1 is smaller than the one at
 *  position 3, and likewise for positions 2 and 4.
 *
 */
#include <iostream>

int main(int argc, char* argv[]) { 
    bool used[5];
    for (int i = 1; i < 5; ++i) used[i] = false;
    for (int i = 1; i < 5; ++i) {
        used[i] = true;
        for (int j = 1; j < 5; ++j) {
            if (used[j]) continue;
            used[j] = true;
            for (int k = 1; k < 5; ++k) {
                if (used[k]) continue;
                used[k] = true;
                for (int l = 1; l < 5; ++l) {
                    if (used[l]) continue;
                    used[l] = true;
                    if (i < k && j < l) {
                      std::cout << i << " " << j << " " << k << " " << l << std::endl;
                    }
                    used[l] = false;
                }
                used[k] = false;
            }
            used[j] = false;
        }
        used[i] = false;
    }
}
