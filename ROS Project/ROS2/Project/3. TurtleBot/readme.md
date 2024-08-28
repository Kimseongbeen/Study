# 라즈베리 파이 설정 및 원격 접속 가이드

## 1. Raspberry Pi OS 설치

1. [Raspberry Pi 공식 웹사이트](https://www.raspberrypi.com/software/)에서 Ubuntu용 Raspberry Pi Imager를 다운로드합니다.

주의! Ubuntu software 에서 다운로드 시 에러 발생(구버전)

.deb 파일 다운로드 후 
```bash
cd Downloads
sudo apt install ./rpi-imager_1.8.5_amd64.deb
```
2. Imager를 실행하고 다음과 같이 설정합니다:
   - CHOOSE OS > Other general-purpose OS > Ubuntu > 22.04.4 LTS(64-bit)
   - SSH 활성화

**설명**: 이 단계에서는 라즈베리 파이에 운영 체제를 설치합니다. Ubuntu를 선택하여 더 많은 기능과 호환성을 제공합니다. SSH를 활성화하면 원격으로 라즈베리 파이에 접속할 수 있습니다.

## 2. 원격 접속 설정

```bash
# 라즈베리 파이의 동적 IP 확인
ping 192.168.5.15

# SSH로 접속
ssh raspberry@192.168.5.15

# 호스트 파일 편집
sudo vim /etc/hosts
# 다음 줄 추가:
192.168.5.15 raspberry 

# 호스트명으로 접속 확인
ping raspberry
ssh raspberry@raspberry

# 시스템 업데이트
sudo apt-get update
sudo apt-get upgrade
```

**설명**: 이 단계에서는 라즈베리 파이에 원격으로 접속하기 위한 설정을 합니다. 동적 IP를 고정 호스트명(raspberry)과 연결하여 접속을 편리하게 만듭니다. 마지막으로 시스템을 최신 상태로 업데이트합니다.

## 3. 외부 장치 설정

```bash
# 사용자를 dialout 그룹에 추가 (시리얼 포트 접근 권한 부여)
sudo usermod -a -G dialout $USER

# Bluetooth 설정
bluetoothctl power on
bluetoothctl scan on
bluetoothctl pairable on
bluetoothctl pair MacAddress
bluetoothctl trust MacAddress
bluetoothctl connect MacAddress

# Bluetooth 설정 파일 수정
sudo vim /etc/bluetooth/main.conf
# FastConnectable = False 주석 해제

# 입력 장치 권한 설정
cd /etc/udev/rules.d/
sudo touch 81-event.rules
sudo vim 81-event.rules
# 다음 내용 추가:
SUBSYSTEM=="input", KERNEL=="event*", GROUP="raspberry", MODE="0660"
```

**설명**: 이 단계에서는 외부 장치와의 연결을 위한 설정을 합니다. Bluetooth 장치를 연결하고, 입력 장치에 대한 권한을 설정합니다. 이를 통해 다양한 외부 장치를 라즈베리 파이와 원활하게 사용할 수 있습니다.

## 4. Arduino IDE 설치

```bash
```

```bash
cd Downloads
ls
chmod +x arduino...

# 필요한 패키지 설치
sudo add-apt-repository universe
sudo apt install libfuse2

# Arduino 규칙 파일 생성
cd /etc/udev/rules.d
sudo touch 99-arduino.rules
sudo vim 99-arduino.rules
# 다음 내용 추가:
SUBSYSTEM=="usb", ATTRS{idVendor}=="2341", GROUP="plugdev", MODE="0666"

# brltty 제거 (시리얼 포트 충돌 방지)
sudo apt remove brltty

# 실행
./arduino-ide_2.3.2_Linux_64bit.AppImage

```

**설명**: 이 단계에서는 Arduino IDE 사용을 위한 설정을 합니다. 필요한 패키지를 설치하고, Arduino 보드를 인식할 수 있도록 udev 규칙을 추가합니다. brltty를 제거하여 시리얼 포트 충돌을 방지합니다.