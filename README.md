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

To compile the program, environment variables are used to find include and lib files.
$(CONTRIB_PATH) has the location of the opencv files similar to the directory fragment
shown below.  The PATH environment variable should be appended to include the contrib\bin 
folder as well for runtime operation.

```
    C:\Users\sr996\contrib
      bin
        opencv_world451.dll
      include
        opencv2
      lib
        opencv_world451.lib
```

There are additional environment variables required.  $(PYTHON_PATH) should point to the python
installation directory e.g.

C:\Users\sr996\AppData\Local\Programs\Python\Python36

and $(NUMPY_PATH)

C:\Users\sr996\AppData\Local\Programs\Python\Python36\Lib\site-packages\numpy\core

This program uses code taken from the article published on CodeProject <a href=https://www.codeproject.com/articles/820116/embedding-python-program-in-a-c-cplusplus-code>Embedding Python program in a C/C++ code</a>

Python packages used
<br>Python 3.6.8
<br>opencv 4.4.0.42
<br>tensorflow 2.6.0
<br>numpy 1.19.5

To use with a conda installation the following instructions may be helpful

Using the conda prompt, build a conda environment with tensorflow-gpu

conda create --name tf tensorflow-gpu
activate tf
conda install -c conda-forge opencv

set PYTHON_PATH=C:\Users\sr996\anaconda3\envs\tf
set NUMPY_PATH=C:\Users\sr996\anaconda3\Lib\site-packages\numpy\core
set PYTHONHOME=%PYTHON_PATH

Use fully qualified file pathnames in the code
