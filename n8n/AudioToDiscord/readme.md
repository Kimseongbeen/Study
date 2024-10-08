
# m4a to mp3 변환

이 프로젝트는 **ffmpeg**를 사용하여 **m4a** 파일을 **mp3**로 변환하는 기능을 제공합니다. Docker 환경에서 설정 및 변환 과정을 아래와 같이 진행합니다.

## 사전 준비

- **Docker** 및 **Docker Compose**가 시스템에 설치되어 있어야 합니다.

## 설정 단계

### 1. ffmpeg 설치

먼저, Docker 컨테이너 내에서 ffmpeg가 설치되도록 설정합니다. 이를 위해 아래 파일들을 수정합니다.

### 2. 환경 파일 수정

#### `.env`

데이터베이스 자격 증명, `N8N_ENCRYPTION_KEY`, `N8N_USER_MANAGEMENT_JWT_SECRET` 등의 환경 변수를 포함시킵니다.

#### `docker-compose.yml`

`docker-compose.yml` 파일을 업데이트하여 공유 볼륨을 마운트하고, n8n 컨테이너에 ffmpeg 설치를 포함시킵니다.

```yaml
services:
  n8n:
    build:
      context: .
      dockerfile: Dockerfile.n8n
    container_name: n8n
    restart: unless-stopped
    ports:
      - 5678:5678
    volumes:
      - n8n_storage:/home/node/.n8n
      - ./n8n/backup:/backup
      - ./shared:/data/shared
    depends_on:
      postgres:
        condition: service_healthy
      n8n-import:
        condition: service_completed_successfully

volumes:
  n8n_storage:
  postgres_storage:
  shared_data:
```

#### `Dockerfile.n8n`

`Dockerfile.n8n` 파일에 ffmpeg 및 필요한 패키지 설치를 포함합니다.

```Dockerfile
# n8n 이미지를 기반으로 사용
FROM n8nio/n8n:latest

# ffmpeg 설치
USER root
RUN apk add --update --no-cache ffmpeg

# 권한 설정
USER node
```

### 3. 폴더 생성

`shared/input` 및 `shared/output` 폴더를 생성하여 파일을 변환할 때 사용합니다.

```bash
mkdir -p ./shared/input
mkdir -p ./shared/output
```

### 4. 폴더 권한 부여

Docker 컨테이너에서 파일을 읽고 쓸 수 있도록 폴더 권한을 설정합니다.

```bash
sudo chmod -R 777 ./shared/input
sudo chmod -R 777 ./shared/output
```

### 5. Docker 재빌드 및 실행

Docker 이미지를 재빌드한 후 컨테이너를 실행합니다.

```bash
docker-compose build --no-cache
docker-compose up -d
```

빌드 에러
```bash
docker-compose down --remove-orphans
docker system prune -a
docker-compose build --no-cache
```

## 사용 방법

1. **m4a 파일 업로드**: `shared/input` 폴더에 변환할 m4a 파일을 업로드합니다.
2. **mp3로 변환**: n8n 워크플로우에서 FFmpeg를 사용하여 m4a 파일을 mp3로 변환합니다.
3. **변환 결과 확인**: 변환된 mp3 파일은 `shared/output` 폴더에 저장됩니다.
4. **파일 삭제**: 변환 작업이 완료된 후 원본 파일과 mp3 파일을 삭제할 수 있습니다.

## 예시 명령어

FFmpeg를 사용하여 m4a 파일을 mp3로 변환하는 명령어는 다음과 같습니다:

```bash
ffmpeg -i /data/shared/input/filename.m4a -q:a 0 /data/shared/output/filename.mp3
```

## 파일 삭제

변환 작업 후 불필요한 파일을 삭제하는 명령어는 다음과 같습니다:

```bash
rm /data/shared/input/input.m4a
rm /data/shared/output/output.mp3
```

이 과정을 통해 m4a 파일을 mp3로 변환하고, 변환된 파일을 관리할 수 있습니다.
```

