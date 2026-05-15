CXX = g++

CXXFLAGS = -O3 -mavx2 -mfma -fopenmp

SRC = src/main.cpp \
      src/convolution.cpp \
      src/image_loader.cpp \
      src/filters.cpp

OUT = build/cnn_processor

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)