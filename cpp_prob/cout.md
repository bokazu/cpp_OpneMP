# std::coutによる標準出力が崩れることへの対処方法

## まとめ
std::coutの前には`pramga omp critical`の指示文を付け加えよう。

## 内容
以下のようなコードを実行したとする。
``` C++
#include<iostream>
#include<omp.h>

using namespace std;

int main(){
    #pragma omp parallel for
    for(int i = 0; i < 10; i++){
        cout << "i=" << i << ":" << "Hello" << endl;
    }
}
```

このとき、出力が
```
i=3:Hello
i=4:Hello
i=5:Hello
i=8:Hello
i=9:Hello
i=0:Helloi=
i=1:Hello
i=2:Hello
6:Hello
i=7:Hello
```
のように上から6、9行目でこちらが望む形とは別の形で出力されている。coutの部分を例えば
```c++
printf("i = %d : Hello\n" ,i);
```
のようにすると問題なく出力された。そこで、調べてみると[Using std::cout in a parallel for loop using OpneMP (stack overflow)](https://stackoverflow.com/questions/57673688/using-stdcout-in-a-parallel-for-loop-using-openmp)という記事を見つけ、coutの直前で`#pragma opm critical`という指示文を加えると良いとのコメントがあったのでそのとおりにしてみた。
``` C++
#include<iostream>
#include<omp.h>

using namespace std;

int main(){
    #pragma omp parallel for
    for(int i = 0; i < 10; i++){
        #pragma omp critical
        cout << "i=" << i << ":" << "Hello" << endl;
    }
}
```
すると、問題なく出力された。
