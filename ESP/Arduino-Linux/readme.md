Linux Arduino 설치
LTS 22.04 버전

python3 -m pip install pyserial

https://www.arduino.cc/en/software

Linux AppImage 64 bits(X86-64) 


```
# 다운로드
mkdir Arduino
cp ~/Downloads/arduino-ide_2.3.2_Linux_64bit.AppImage ~/Arduino
# 
cd Arduino
sudo add-apt-repository universe
sudo apt install libfuse2
# 초록색으로 변하는것 확인
chmod +x arduino-ide_2.3.2_Linux_64bit.AppImage

# CP210X UART Bridge 필요
lsusb

#
ls -la /dev | grep ttyACM
ls -la /dev | grep ttyUSB
sudo usermod -a -G dialout smileb
```
