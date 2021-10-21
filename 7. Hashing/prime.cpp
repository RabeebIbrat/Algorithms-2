#include <iostream>
#include <math.h>
using namespace std;

int main() {
    while(true) {
        int p;
        bool prime = false;
        cin >> p;
        while(!prime) {
            int lim = sqrt(p);
            prime = true;
            for(int i = 2; i <= lim; i++) {
                if(p%i == 0) {
                    prime = false;
                    p += 1;
                    break;
                }
            }
        }
        cout << p << endl;
    }
}
