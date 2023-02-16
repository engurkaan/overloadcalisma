#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <thread>
#include "Zamanlayici.cpp"

template<typename T> void findPrime(T toWhatNumber,
        std::vector<T>& saveToWhatArray, uint64_t fromWhatNumber=2);
template<typename T>
void findPrimeBetter(const T towhat, std::vector<T>& array, uint64_t fromwhat);

template<class T>
void findPrimeMT(T towhat);

uint64_t findNumberOfPrime(uint64_t towhat, uint64_t fromwhat=2);


int main() {
    std::cout<< "Hangi sayıya kadar asal bulmak istediğinizi giriniz: " <<"\n";
    uint64_t toWhatNumb;
    std::cin>>toWhatNumb;
    std::vector<uint32_t> v;
    Timer t;
    findPrimeMT<uint64_t>(toWhatNumb);
    //findPrime(toWhatNumb, v);
    //std::cout<< "Asal sayı sayısı: "<< v.size() <<"\n";
    //std::cout<< "Tahmini asal sayı sayısı: " <<"\n";

/*    std::cout<< "Asallarınız: ";
    for (int i : v) {
        std::cout<< i <<" ";
    }
*/
    /*std::ofstream dosya("asallar.txt");
    for (uint32_t i: v) {
        dosya<<i<<" ";
    }*/
    std::cout<<"\n"<<"Geçen süre: "<<t.elapsed()<<"\n";
    //dosya.close();
}

template<typename T>
void findPrime(const uint64_t towhat, std::vector<T>& array, const uint64_t fromwhat) {
    uint64_t currentNumber{fromwhat};
    bool isPrime{true};
    while(currentNumber<=towhat) {

        for (int i = 2; i <= sqrt(currentNumber); ++i) {
            if(currentNumber%i==0) {
                isPrime=false;
                break;
            }
        }
        if(isPrime) { array.push_back(currentNumber); }
        isPrime=true;
        ++currentNumber;
    }
}

uint64_t findNumberOfPrime(const uint64_t towhat, const uint64_t fromwhat) {
    uint64_t currentNumber{fromwhat};
    uint32_t totalNum{0};
    bool isPrime{true};
    while(currentNumber<=towhat) {

        for (int i = 2; i <= sqrt(currentNumber); ++i) {
            if(currentNumber%i==0) {
                isPrime=false;
                break;
            }
        }
        if(isPrime) { ++totalNum; }
        isPrime=true;
        ++currentNumber;
    }
    return totalNum;
}

template<typename T>
void findPrimeBetter(const T towhat, std::vector<T> &array, uint64_t fromwhat) {
    array.resize( towhat/(log(towhat) - 1.0836 ) - (
            (fromwhat>2)? fromwhat/(log(fromwhat) -1.0836):0) );
    bool isPrime{true};
    uint32_t index{0};
    while(fromwhat<=towhat) {

        for (int i = 2; i <= sqrt(fromwhat); ++i) {
            if(fromwhat%i==0) {
                isPrime=false;
                break;
            }
        }
        if(isPrime) { array[index++]=fromwhat; }
        isPrime=true;
        ++fromwhat;
    }
}

template<class T>
void findPrimeMT(T towhat) {
    std::vector<T> v1, v2;
    std::thread t1(findPrimeBetter<T>, 3*towhat/5, std::ref(v1), 2);
    std::thread t2(findPrimeBetter<T>, towhat, std::ref(v2), 3*towhat/5);

    t1.join();
    //while (true) {
    //    if(*(v1.cend()-1)==0)
    //        break;
    //    v1.erase(v1.cend()-1);
    //}

    std::cout<< "Asallar: " <<'\n';
    for (auto i:v1) {
        std::cout<< i <<' ';
    }
    std::cout<< "bitti " <<"\n";

    t2.join();
    //while (true) {
    //    if(*(v2.cend()-1)==0)
    //        break;
    //    v2.erase(v2.cend()-1);
    //}
    for (auto i:v2) {
        std::cout<< i <<' ';
    }

}


//715'656 -> 0.4 saniye (SOA: 0.007sn)
//14'511'641 -> run: 35.2 saniye | debug: 33.1 saniye