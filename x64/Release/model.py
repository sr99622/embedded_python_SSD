import tensorflow as tf
import numpy as np
import cv2

class Model: 
    def __init__(self): 
        self.model = None
        self.threshold = 0.5

    def initialize_model(self, filename):
        self.model = tf.saved_model.load(filename)

    def set_threshold(self, arg):
        self.threshold = arg/100

    def __call__(self, img):
        height = img.shape[0]
        width = img.shape[1]
        input = tf.convert_to_tensor(np.expand_dims(img, 0))
        output = self.model(input)
        detection_scores = output['detection_scores'].numpy().squeeze().transpose()
        detection_classes = output['detection_classes'].numpy().squeeze().transpose()
        detection_boxes = output['detection_boxes'].numpy().squeeze()

        mask = detection_classes == 1
        detection_boxes = detection_boxes[mask]
        detection_scores = detection_scores[mask]
        print('detection scores: \n', detection_scores)
        mask = detection_scores > self.threshold
        detection_boxes = detection_boxes[mask]

        for x in range(0, detection_boxes.shape[0]):
            detection_boxes[x, 0] *= height
            detection_boxes[x, 1] *= width
            detection_boxes[x, 2] *= height
            detection_boxes[x, 3] *= width

        return detection_boxes
    
if __name__ == "__main__":
    function = Model()
    function.initialize_model("ssd_mobilenet_v2_320x320_coco17_tpu-8/saved_model")
    img = cv2.imread("000394.jpg")
    detection_boxes = function(img)
    print('detections: \n', detection_boxes)

    for x in range(0, detection_boxes.shape[0]):
        top = detection_boxes[x, 0]
        left = detection_boxes[x, 1]
        bottom = detection_boxes[x, 2]
        right = detection_boxes[x, 3]
        cv2.rectangle(img, (int(left), int(top)), (int(right), int(bottom)), (255, 255, 255), 1)
    
    cv2.imshow('image', img)
    cv2.waitKey(0)
