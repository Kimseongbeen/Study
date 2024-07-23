# Ubuntu 가상환경 및 C++ 개발환경 설정 가이드

## 1. 가상환경 설정

1. Ubuntu 22.04 LTS ISO 이미지 다운로드
2. VMWare 설치
3. VMWare에 Ubuntu 가상머신 생성 및 설치

## 2. 개발환경 설정

### VSCode 설치
1. VSCode Linux .deb 파일 다운로드
2. 버전 확인 및 설치:
   ```
   lsb_release -a
   cd ~/Downloads/
   ls
   sudo dpkg -i code_*.deb
   ```

### VSCode 확장 프로그램 설치
- C/C++
- C/C++ Extension Pack
- VSCode Icons
- CMake
- CMake Tools

### G++ 컴파일러 설치
```
sudo apt-get install g++
gcc --version
```

## 3. C++ 테스트

VScode 버벅거림 해결

```
1. vscode 내에서 command + shift + P
2. config runtime arguments 검색
3. "disable-hardware-acceleration": true 추가
```


1. `test.cpp` 파일 생성:
   ```cpp
   #include <iostream>
   
   int main()
   {
       std::cout << "Hello, World!" << std::endl;
       return 0;
   }
   ```

2. VSCode에서 실행:
   - `F5` 키 또는 "Run and Debug" 메뉴 사용
   - 구성: "C/C++: g++ build and debug active file" 선택
