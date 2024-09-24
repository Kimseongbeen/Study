# Realtek AMB82-Mini IoT AI 카메라 보드 프로젝트

## AMB82 MINI 사양

- **MCU**: ARMv8M (최대 500 MHz)
- **NPU**: Intelligent Engine (0.4 TOPS)
- **메모리**: 
  - SoC 내부 DDR2 128 MB
  - 개발 보드의 외부 SPI Nor 플래시 16 MB
- **Wi-Fi**: 
  - 802.11 a/b/g/n 1x1
  - 듀얼밴드 2.4GHz/5GHz
  - Wi-Fi 간편 설정
- **Bluetooth**: BLE 5.1
- **보안**: 
  - 하드웨어 암호화 엔진
  - 보안 부팅 (선택사항)
  - Trust-Zone (선택사항)
  - Wi-Fi WEP, WPA, WPA2, WPA3, WPS
- **오디오 코덱**: ADC/DAC/I2S
- **ISP/비디오**: 
  - HDR / 3DNR / WDR
  - H264/H265/JPEG 비디오 인코더 (1080p@30fps + 720p@30fps)
- **카메라 모듈**: 
  - JXF37 1920 x 1080 풀 HD CMOS 이미지 센서
  - 광각 렌즈 (FOV 130°)
- **인터페이스**: 
  - 개발 보드에 마이크 1개
  - Micro USB_B 2개
  - MicroSD 카드 슬롯 1개
  - 택트 스위치 버튼 2개
  - UART 3개, SPI 2개, I2C 1개, PWM 8개, GDMA 2개
  - 최대 23개 GPIO

## Arduino IDE에서 시작하기

[공식 가이드](https://www.amebaiot.com/en/amebapro2-amb82-mini-arduino-getting-started)를 참조하거나 아래 단계를 따르세요.

1. **Arduino IDE의 추가 보드 매니저 URL에 Ameba Arduino SDK 링크 추가**
   - Arduino IDE 1.6.5 이상 버전 사용 권장
   - "File" -> "Preferences" -> "Additional Boards Manager URLs:"에 다음 링크 추가:
     ```
     https://github.com/ambiot/ambpro2_arduino/raw/main/Arduino_package/package_realtek_amebapro2_index.json
     ```
   - "Show verbose output" 옵션 활성화 권장 (디버깅 용이)

2. **"Board Manager"에서 Ameba 보드 설치**
   - "Tools" -> "Board" -> "Board Manager" 열기
   - "ameba" 검색 후 Realtek Ameba 설치

3. **"Tools" -> "Board" -> "AmebaPro2 ARM (32-bits) Boards"에서 Ameba 모델 선택**
   - 올바른 모델 선택 중요

자세한 정보는 [여기](https://www.amebaiot.com/en/ameba-arduino-summary/)에서 확인하세요.

## 독립 실행형 객체 감지 (Yolo v7 Tiny)

### 1. 필요한 라이브러리

- [Arduino TJpg_Decoder 라이브러리](https://github.com/Bodmer/TJpg_Decoder)
  - JPEG 이미지 버퍼를 디스플레이에 그리기 위해 필요
  - "Ameba Pro 2" 아키텍처 지원을 위해 User_Config.h 파일 수정 필요:
    - "/src/User_Config.h" 열기
    - "#define TJPGD_LOAD_SD_LIBRARY" 제거

### 2. 소스 코드 로드

- src 폴더에서 데모 소스 코드 가져오기
- Arduino IDE에서 src/Standalone_Object_Detector_v1 열기

## 라이선스

MIT 라이선스
Copyright (c) 2024 Eric Nam

이 소프트웨어와 관련 문서 파일("소프트웨어")의 복사본을 얻은 모든 사람에게 무상으로 허가합니다. 소프트웨어를 제한 없이 사용, 복사, 수정, 병합, 게시, 배포, 서브라이선스 및/또는 판매할 수 있는 권리와 이 소프트웨어를 제공받은 사람에게 동일한 권리를 부여할 수 있는 권리가 포함되며, 다음 조건에 따릅니다:

위의 저작권 고지와 이 허가 고지는 소프트웨어의 모든 복사본 또는 상당 부분에 포함되어야 합니다.

소프트웨어는 "있는 그대로" 제공되며, 상품성, 특정 목적에의 적합성 및 비침해성에 대한 보증을 포함하여 명시적이거나 묵시적인 어떠한 종류의 보증도 없습니다. 어떠한 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 소프트웨어와 관련하여 발생하는 모든 청구, 손해 또는 기타 책임에 대해 책임지지 않습니다.