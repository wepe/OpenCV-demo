import cv2
from face_detection import drawFaces

f = "./video.wmv"
wd = "Window's name!"
capture = cv2.VideoCapture(f)

#save as video
fourcc = cv2.cv.CV_FOURCC(*'XVID')
out = cv2.VideoWriter('output.avi',fourcc,20.0,(720,400))


while(capture.isOpened()):
	ret,img = capture.read()
	img = drawFaces(img)
	if ret == True:
		out.write(img)
	cv2.imshow(wd,img)
	#press 'q' to quit
	c = cv2.waitKey(1)
	if c&0xFF == ord('q'):
		break
#release
capture.release()
out.release()
cv2.destroyAllWindows()
