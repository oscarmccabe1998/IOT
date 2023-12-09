from picamera import PiCamera
from time import sleep 

camera = PiCamera()
camera.resolution = (1024, 768)
camera.capture('/home/pi/tempPics/temp.jpg')