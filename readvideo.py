import numpy as np
import cv2
import os


cap = cv2.VideoCapture('C:\\Users\\INKOM06\\Documents\\a1OpenCVcodes\\data\\bubat.mp4')

totalFrames = cap.get(cv2.CAP_PROP_FRAME_COUNT)
print(totalFrames)


scRatio = 0.2

ret, frame = cap.read()
M = frame.shape[0]  # column
N = frame.shape[1]  # row

print("M: row (height) ",M,"  N: col (width)", N)

frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
M = frame.shape[0]  # row
N = frame.shape[1]  # col

print("Grayscale M: row (height) ",M,"  N: col (width)", N)

newRow = int(M*scRatio)
newCol = int(N*scRatio)


frameIdx = 1
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    pct = (frameIdx/totalFrames)*100
    print('Frame index: %d Pct: %3.2f %s' % (frameIdx,pct,chr(37)))
    frameIdx = frameIdx + 1

    frame = cv2.resize(frame,(newCol,newRow) , interpolation = cv2.INTER_AREA)
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    frame2 = frame[int(newRow/2):newRow, 0:newCol]
    cv2.imshow('Original image',frame2)


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

