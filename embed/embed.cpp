#include <iostream>
#include <Python.h>
#include "pyhelper.h"
#include <opencv2/opencv.hpp>
#include <numpy/arrayobject.h>

int main(int argc, char* argv[])
{
	CPyInstance pyInstance;
	PySys_SetArgv(argc, (wchar_t**)argv);
	PyRun_SimpleString("import tensorflow as tf");
	PyRun_SimpleString("import cv2");
	PyRun_SimpleString("import numpy as np");
	import_array1(-1);

	cv::Mat image = cv::imread("000394.jpg");
	npy_intp dimensions[3] = { image.rows, image.cols, image.channels() };
	CPyObject pData = PyArray_SimpleNewFromData(3, dimensions, NPY_UINT8, image.data);
	CPyObject pArg = Py_BuildValue("(O)", pData);

	CPyObject pName = PyUnicode_FromString("model");
	CPyObject pModule = PyImport_Import(pName);
	CPyObject pDict = PyModule_GetDict(pModule);
	CPyObject pClass = PyDict_GetItemString(pDict, "Model");
	CPyObject pInstance = PyObject_CallObject(pClass, NULL);
	CPyObject pCallHandle2 = PyObject_CallMethod(pInstance, "set_threshold", "(i)", 50);
	CPyObject pCallHandle1 = PyObject_CallMethod(pInstance, "initialize_model", "(s)", "ssd_mobilenet_v2_320x320_coco17_tpu-8/saved_model");
	if (pCallHandle1) {
		PyObject* pValue = PyObject_CallObject(pInstance, pArg);
		if (pValue) {
			npy_intp* dims = PyArray_DIMS((PyArrayObject*)pValue);
			int height = dims[0];
			int width = dims[1];

			cv::Scalar color = cv::Scalar(255, 255, 255);
			int top = 0, left = 0, bottom = 0, right = 0;
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					void* ptr = PyArray_GETPTR2(pValue, y, x);
					CPyObject pElement = PyArray_GETITEM(pValue, ptr);
					double element = PyFloat_AsDouble(pElement);

					switch (x) {
					case 0:
						top = element;
						break;
					case 1:
						left = element;
						break;
					case 2:
						bottom = element;
						break;
					case 3:
						right = element;
						break;
					}
					std::cout << " " << element;
				}
				rectangle(image, cv::Point(left, top), cv::Point(right, bottom), color, 1);
				std::cout << std::endl;
			}

			Py_DECREF(pValue);

			cv::imshow("image", image);
			cv::waitKey(0);
		}
	}

	return 0;
}
