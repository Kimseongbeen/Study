#include <iostream>

struct People
{
    int age;
    int height;
    char name[256];
};

class cPeople{
//접근제한 지정자
//private:
public:
    int age;
    int height;

private:
    char name[256];
};
void printPeople(People p1)
{
    (*p1).age += 1;
}
// 사용자 정의 자료형
int main()
{
    // 자료구조

    // 구조체, 클래스
    
    People smileb;

    smileb.age = 10;
    smileb.height = 120;
    cPeople SB;
    SB.age;

    // 1. printPeople 안에 아무것도 없을때 -p1의 배열에 smileb의 배열이 복사가됨 p1[0] = 10, p1[1]=120
    printPeople(smileb);
    // 2. People* p1 일때
    // People의 주소를 p1에 복사하는것, ex) smileb.age의 주소값이 0x2라고 할때 p1[0]에는 0x2 즉, p1[0]에 접근하면 smileb.age의 주소에 접근하게 된다.
    // 3. *p1.age += 1 
    // age의 주소에 접근해서 1을 더해준다.
    return 0;
}

