#include<iostream>
#include<omp.h>

using namespace std;

int main(){
    cout << omp_get_max_threads() << endl;

    #pragma omp parallel for
    for(int i=0;i<10;i++){
        printf("thread = %d, i = %2d\n", omp_get_thread_num(), i);
    }
#pragma omp parallel for
    for(int i=0;i<10;i++){
        #pragma omp critical
        cout << "i=" << i << ":" << "Hello" << endl;
    }
    // for(int i=0;i<10;i++){
    //    printf("i = %d, Hello\n" ,i);
    // }

}
