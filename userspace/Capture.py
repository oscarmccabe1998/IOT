from picamera import PiCamera

def takePhoto():
    camera = PiCamera()
    camera.resolution = (1024, 768)
    camera.capture('/home/pi/tempPics/temp.jpg')