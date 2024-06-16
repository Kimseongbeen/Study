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

// 사용자 정의 자료형
int main()
{
    // 자료구조

    // 구조체, 클래스
    
    People smileb;

    smileb.age = 10;

    cPeople SB;
    SB.age;

    return 0;
}

