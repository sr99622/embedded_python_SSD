# embedded_python_SSD
C++ program with embedded python running SSD model on tensorflow v2

Command line program developed in MSVC 2019.  The program requires the use of tensorflow v2
and opencv as well as numpy.  The program is intended to be compiled as a 64 bit release version
and the executable will reside in the x64/Release subdirectory.  Included in this subdirectory
is a sample jpg file for use by the test program.  It is necessary to place a downloaded SSD
model in the subdirectory as well for the code to be able to find it.  The SSD model used during
testing was taken from the tensorflow model zoo, <a href=http://download.tensorflow.org/models/object_detection/tf2/20200711/ssd_mobilenet_v2_320x320_coco17_tpu-8.tar.gz>
ssd_mobilenet_v2_320x320_coco17_tpu-8</a>.  The model should be unpacked and placed in the x64\Release
subdirectory so the program can find it.

The python portion of the code is also found in the executable subdirectory and may be run
independently using the command python model.py to confirm results.

To compile the program, environment variabled are used to find include and lib files.
$(CONTRIB_PATH) has the location of the opencv and tensorflow files similar to the fragment
shown below.  The PATH environment variable should be appended to include the contrib\bin 
folder as well for runtime operation.

```
    C:\Users\sr996\contrib
      bin
        opencv_world451.dll
        tensorflow.dll
      include
        opencv
        tensorflow
      lib
        opencv_world451.lib
        tensorflow.lib
```

There are additional environment variables required.  $(PYTHON_PATH) should point to the python
installation directory e.g.

C:\Users\sr996\AppData\Local\Programs\Python\Python36

and $(NUMPY_PATH)

C:\Users\sr996\AppData\Local\Programs\Python\Python36\Lib\site-packages\numpy\core

This program uses code taken from the article publiched on CodeProject <a href=https://www.codeproject.com/articles/820116/embedding-python-program-in-a-c-cplusplus-code>Embedding Python program in a C/C++ code</a>
