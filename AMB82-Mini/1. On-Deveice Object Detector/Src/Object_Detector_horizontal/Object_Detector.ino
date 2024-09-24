/*
[1] 보드
    > Realtek Ameba 보드(32-bit Arm v8M) 
    > 버전: 4.0.7

[2] 라이브러리
    > **Arduino TJpg_Decoder 라이브러리** https://github.com/Bodmer/TJpg_Decoder
    > 버전: 1.1.0
    JPEG 이미지 버퍼를 디스플레이에 그리기 위해 디코딩이 필요합니다.
    안타깝게도 아직 "Ameba Pro 2" 아키텍처를 지원하지 않으므로,
    성공적인 빌드를 위해 User_Config.h 파일을 수정해야 합니다.
    > "/src/User_Config.h" 열기
    > "#define TJPGD_LOAD_SD_LIBRARY" 제거
*/

#include "SPI.h"
#include "AmebaILI9341.h"

#include <TJpg_Decoder.h>
#include "StreamIO.h"
#include "VideoStream.h"
#include "NNObjectDetection.h"
#include "VideoStreamOverlay.h"
#include "ObjectClassList.h"

#define CHANNELTFT 1
#define CHANNELNN 3

// NN 처리를 위한 낮은 해상도
#define NNWIDTH 576
#define NNHEIGHT 320

// 지원되는 모든 보드(AMB21/AMB22, AMB23, BW16/BW16-TypeC, AW-CU488_ThingPlus)에 대해,
// TFT_RESET과 TFT_DC에 연결할 2개의 GPIO 핀을 선택하세요. 그리고 기본 SPI_SS/SPI1_SS는 TFT_CS에 연결됩니다.
#define TFT_RESET 5
#define TFT_DC 4
#define TFT_CS SPI_SS

AmebaILI9341 tft = AmebaILI9341(TFT_CS, TFT_DC, TFT_RESET);
#define ILI9341_SPI_FREQUENCY 20000000
#define TFT_WIDTH 320
#define TFT_HEIGHT 240
#define TFT_FPS 10

VideoSetting configNN(NNWIDTH, NNHEIGHT, 10, VIDEO_RGB, 0);
VideoSetting configTFT(TFT_WIDTH, TFT_HEIGHT, TFT_FPS, VIDEO_JPEG, 1);
NNObjectDetection ObjDet;
StreamIO videoStreamerNN(1, 1);

uint32_t img_addr = 0;
uint32_t img_len = 0;

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  tft.drawBitmap(x, y, w, h, bitmap);
  return 1;
}

void setup() {
  Serial.begin(115200);

  SPI.setDefaultFrequency(ILI9341_SPI_FREQUENCY);

  tft.begin();
  tft.setRotation(1);
  intoText();

  //
  delay(5000);
  TJpgDec.setJpgScale(1);
  TJpgDec.setCallback(tft_output);

  Camera.configVideoChannel(CHANNELNN, configNN);
  Camera.configVideoChannel(CHANNELTFT, configTFT);
  Camera.videoInit();

  // 해당 비디오 포맷 정보로 객체 감지 구성
  // 신경망(NN) 작업 및 모델 선택
  ObjDet.configVideo(configNN);
  ObjDet.modelSelect(OBJECT_DETECTION, DEFAULT_YOLOV7TINY, NA_MODEL, NA_MODEL);
  ObjDet.begin();

  Camera.channelBegin(CHANNELTFT);

  // RGB 비디오 채널에서 객체 감지로 데이터를 스트리밍하도록 StreamIO 객체 구성
  videoStreamerNN.registerInput(Camera.getStream(CHANNELNN));
  videoStreamerNN.setStackSize();
  videoStreamerNN.setTaskPriority();
  videoStreamerNN.registerOutput(ObjDet);
  if (videoStreamerNN.begin() != 0) {
    Serial.println("StreamIO 링크 시작 실패");
  }

  Camera.channelBegin(CHANNELNN);
}

void loop() {
  // 참고: JPEG 버퍼가 가득 찼을 때 처리가 필요합니다
  Camera.getImage(CHANNELTFT, &img_addr, &img_len);
  TJpgDec.drawJpg(0, 0, (const uint8_t*)img_addr, img_len);

  std::vector<ObjectDetectionResult> results = ObjDet.getResult();
  printf("감지된 총 객체 수 = %d\r\n", ObjDet.getResultCount());
  if (ObjDet.getResultCount() > 0) {
    for (uint32_t i = 0; i < ObjDet.getResultCount(); i++) {
      int obj_type = results[i].type();
      if (itemList[obj_type].filter) {  // 항목을 무시해야 하는지 확인

        ObjectDetectionResult item = results[i];
        // 결과 좌표는 0.00에서 1.00 사이의 부동 소수점입니다
        // RTSP 해상도와 곱하여 픽셀 단위의 좌표를 얻습니다
        int xmin = (int)(item.xMin() * tft.getWidth());
        int xmax = (int)(item.xMax() * tft.getWidth());
        int ymin = (int)(item.yMin() * tft.getHeight());
        int ymax = (int)(item.yMax() * tft.getHeight());

        // 경계 상자 그리기
        tft.drawRectangle(xmin, ymin, xmax, ymax, ILI9341_RED);

        // 식별 텍스트 출력
        char text_str[20];
        snprintf(text_str, sizeof(text_str), "%s %d", itemList[obj_type].objectName, item.score());

        int textLength = strlen(itemList[obj_type].objectName) + String(item.score()).length() + 1;
        if (textLength > 20) {
          textLength = 20;
        }

        for (int i = 0; i < textLength; i++) {
          tft.drawChar(xmin + (i * 12), ymin, text_str[i], ILI9341_GREEN, ILI9341_RED, 2);
        }
      }
    }
  }
}

unsigned long intoText() {
  tft.clr();
  tft.setCursor(0, 30);
  tft.setForeground(ILI9341_GREEN);
  tft.setFontSize(3);
  tft.println("On-Device-Project");
  tft.println();
  tft.setForeground(ILI9341_WHITE);
  tft.setFontSize(4);
  tft.println("Tiny Yolo v7");
  tft.setForeground(ILI9341_YELLOW);
  tft.setFontSize(2);
  tft.println("Pre-trained items: 80");
  tft.println();
  tft.println();
  tft.setForeground(ILI9341_LIGHTGREY);
  tft.setFontSize(1);
  tft.println("Thanks");
  return 0;
}