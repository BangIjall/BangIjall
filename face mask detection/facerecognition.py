from imutils.video import VideoStream
from imutils.video import FPS
import face_recognition
#import argparse
import imutils
import pickle
import cv2
import time

print("[INFO] loading encodings + face detector...")
data = pickle.loads(open("project.pickle", "rb").read())
detector = cv2.CascadeClassifier("mask8.xml")
detectorface = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
 
print("[INFO] Memulai video streaming...")
vs = VideoStream(src=1).start()
time.sleep(2.0)
 
fps = FPS().start()
while True:
	frame = vs.read()
	frame = imutils.resize(frame, width=500)
	
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
 
	rects = detector.detectMultiScale(gray, scaleFactor=1.3,
		minNeighbors=6, minSize=(30, 30))
 

	boxes = [(y, x + w, y + h, x) for (x, y, w, h) in rects]

	encodings = face_recognition.face_encodings(rgb, boxes)
	names = []
	print(encodings)

	for encoding in encodings:
	
		matches = face_recognition.compare_faces(data["encodings"],
			encoding)

		name = "Unknown"

		if True in matches:
			
			matchedIdxs = [i for (i, b) in enumerate(matches) if b]
			print(matchedIdxs)

			counts = {}
			for i in matchedIdxs:

				name = data["names"][i]

				counts[name] = counts.get(name, 0) + 1

			name = max(counts, key=counts.get)
		names.append(name)
	for ((top, right, bottom, left), name) in zip(boxes, names):
		
		cv2.rectangle(frame, (left, top), (right, bottom),(255, 0, 0), 2)
		y = top - 15 if top - 15 > 15 else top + 15
		cv2.putText(frame, name, (left, y), cv2.FONT_HERSHEY_SIMPLEX,
			0.75, (255, 0, 0), 2)
        
	cv2.imshow("Frame", frame)
	key = cv2.waitKey(1) & 0xFF

	if key == ord("q"):
		break
 
	fps.update()

fps.stop()
print("[INFO] elasped time: {:.2f}".format(fps.elapsed()))
print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))

cv2.destroyAllWindows()
vs.stop()

