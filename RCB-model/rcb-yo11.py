from ultralytics import YOLO

model = YOLO('best.pt')
results = model.predict(r'RCB-1\test\images\35310395_36629064_png.rf.e4a9b9ec2c99236399a2ffb6f233a9f5.jpg', conf=0.3)
results[0].show()