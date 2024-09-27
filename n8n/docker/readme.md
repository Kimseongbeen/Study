Windows SubSystem Linux를 활성화시키는 명령어를 입력
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart

VirtualMachinePlatform 기능을 활성화시키는 명령어 : WSL2 버전에 필요한 명령어
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

재부팅

MicroSoft Stroe에서 ubuntu를 설치
ubuntu 20.04.6 LTS 다운

ubuntu 계정 및 패스워드 설정하기

Powershell에서 ubuntu가 설치되어 있는지 확인하기
wsl -l -v