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

// 구조체와 클래스의 차이
// 구조체는 디폴트 접근제한 지정자가 public:
// 클래스는 디폴트 접근제한 지정자가 private

// 사용자 정의 자료형
int main()
{
    // 자료구조

    // 구조체, 클래스
    
    People smileb;

    smileb.age = 10;
    smileb.height = 120;
     // 문자열 복사
    strcpy(&smileb.name[0], "SeongBeen")
    strcpy(smileb.name, "SeongBeen")
    
    cPeople SB;
    SB.age;

    return 0;
}

