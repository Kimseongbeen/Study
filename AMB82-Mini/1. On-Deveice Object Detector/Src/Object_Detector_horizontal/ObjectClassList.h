#ifndef __OBJECTCLASSLIST_H__
#define __OBJECTCLASSLIST_H__

// 객체 감지 항목을 위한 구조체 정의
struct ObjectDetectionItem {
    uint8_t index;        // 객체의 인덱스 번호
    const char* objectName;  // 객체의 이름
    uint8_t filter;       // 필터 값 (0: 무시, 1: 감지)
};

// 사전 훈련된 모델이 인식할 수 있는 객체 목록
// 인덱스 번호는 훈련에서 고정되어 하드코딩됨
// 필터 값을 0으로 설정하면 해당 객체는 감지에서 제외됨
ObjectDetectionItem itemList[80] = {
    {0,  "person",          1},  // 사람
    {1,  "bicycle",         1},  // 자전거
    {2,  "car",             1},  // 자동차
    {3,  "motorbike",       1},  // 오토바이
    {4,  "aeroplane",       1},  // 비행기
    {5,  "bus",             1},  // 버스
    {6,  "train",           1},  // 기차
    {7,  "truck",           1},  // 트럭
    {8,  "boat",            1},  // 보트
    {9,  "traffic light",   1},  // 신호등
    {10, "fire hydrant",    1},  // 소화전
    {11, "stop sign",       1},  // 정지 표지판
    {12, "parking meter",   1},  // 주차 미터기
    {13, "bench",           1},  // 벤치
    {14, "bird",            1},  // 새
    {15, "cat",             1},  // 고양이
    {16, "dog",             1},  // 개
    {17, "horse",           1},  // 말
    {18, "sheep",           1},  // 양
    {19, "cow",             1},  // 소
    {20, "elephant",        1},  // 코끼리
    {21, "bear",            1},  // 곰
    {22, "zebra",           1},  // 얼룩말
    {23, "giraffe",         1},  // 기린
    {24, "backpack",        1},  // 백팩
    {25, "umbrella",        1},  // 우산
    {26, "handbag",         1},  // 핸드백
    {27, "tie",             1},  // 넥타이
    {28, "suitcase",        1},  // 여행 가방
    {29, "frisbee",         1},  // 프리스비
    {30, "skis",            1},  // 스키
    {31, "snowboard",       1},  // 스노보드
    {32, "sports ball",     1},  // 스포츠 공
    {33, "kite",            1},  // 연
    {34, "baseball bat",    1},  // 야구 방망이
    {35, "baseball glove",  1},  // 야구 글러브
    {36, "skateboard",      1},  // 스케이트보드
    {37, "surfboard",       1},  // 서핑보드
    {38, "tennis racket",   1},  // 테니스 라켓
    {39, "bottle",          1},  // 병
    {40, "wine glass",      1},  // 와인 잔
    {41, "cup",             1},  // 컵
    {42, "fork",            1},  // 포크
    {43, "knife",           1},  // 나이프
    {44, "spoon",           1},  // 숟가락
    {45, "bowl",            1},  // 그릇
    {46, "banana",          1},  // 바나나
    {47, "apple",           1},  // 사과
    {48, "sandwich",        1},  // 샌드위치
    {49, "orange",          1},  // 오렌지
    {50, "broccoli",        1},  // 브로콜리
    {51, "carrot",          1},  // 당근
    {52, "hot dog",         1},  // 핫도그
    {53, "pizza",           1},  // 피자
    {54, "donut",           1},  // 도넛
    {55, "cake",            1},  // 케이크
    {56, "chair",           1},  // 의자
    {57, "sofa",            1},  // 소파
    {58, "pottedplant",     1},  // 화분
    {59, "bed",             1},  // 침대
    {60, "diningtable",     1},  // 식탁
    {61, "toilet",          1},  // 변기
    {62, "tvmonitor",       1},  // TV 모니터
    {63, "laptop",          1},  // 노트북
    {64, "mouse",           1},  // 마우스
    {65, "remote",          1},  // 리모컨
    {66, "keyboard",        1},  // 키보드
    {67, "cell phone",      1},  // 휴대폰
    {68, "microwave",       1},  // 전자레인지
    {69, "oven",            1},  // 오븐
    {70, "toaster",         1},  // 토스터기
    {71, "sink",            1},  // 싱크대
    {72, "refrigerator",    1},  // 냉장고
    {73, "book",            1},  // 책
    {74, "clock",           1},  // 시계
    {75, "vase",            1},  // 꽃병
    {76, "scissors",        1},  // 가위
    {77, "teddy bear",      1},  // 테디 베어
    {78, "hair dryer",      1},  // 헤어 드라이어
    {79, "toothbrush",      1}   // 칫솔
};

#endif // __OBJECTCLASSLIST_H__