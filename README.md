# CNN Convolution Engine (AVX2 + OpenMP + Web UI)

A high-performance 2D convolution engine inspired by CNN convolution layers, implemented using low-level CPU optimization techniques.

---

## Features

- Optimized 2D convolution engine in C++
- SIMD acceleration using AVX2
- Multi-core parallelism using OpenMP
- Cache-friendly blocking (tiling)
- Real image input/output support (PNG)
- Web UI built with React + TailwindCSS
- Execution time benchmarking using `std::chrono`

---

## Project Structure

```text
cnn_convolution_engine/
│
├── backend/       # C++ convolution engine (AVX2 + OpenMP)
├── server/        # Node.js API server (image upload + execution bridge)
├── frontend/      # React + Tailwind UI
```

---

## Requirements

### System Requirements

- Windows / Linux
- CPU supporting AVX2 (modern Intel/AMD CPUs)
- Node.js (v16+ recommended)
- MSYS2 (for g++ compiler on Windows)

---

## Install Dependencies

### Frontend dependencies

```bash
cd frontend
npm install
```

### Server dependencies

```bash
cd server
npm install
```

---

## Install C++ Compiler (MSYS2)

Install MSYS2 from:

```text
https://www.msys2.org/
```

Then open the **UCRT64 terminal** and run:

```bash
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc
```

Verify installation:

```bash
g++ --version
```

---

## Build Backend (C++ Engine)

From the `backend/` directory:

```bash
g++ -O3 -mavx2 -mfma -fopenmp src/main.cpp src/convolution.cpp src/image_loader.cpp src/filters.cpp -o build/cnn_processor.exe
```

---

## Run the Project

### 1. Start backend server (Node.js bridge)

```bash
cd server
node server.js
```

Server runs at:

```text
http://localhost:5000
```

---

### 2. Start frontend (React UI)

```bash
cd frontend
npm run dev
```

Frontend runs at:

```text
http://localhost:5173
```

---

## How It Works

1. User uploads an image through the web UI
2. Image is sent to the Node.js server
3. Server executes the compiled C++ binary
4. C++ engine:
   - Loads image using `stb_image`
   - Applies convolution (AVX2 + OpenMP optimized)
   - Writes output image
   - Measures execution time
5. Result is returned and displayed in the frontend

---

## Optimization Techniques Used

### SIMD (AVX2)

Processes multiple floating-point operations in parallel using 256-bit registers.

### OpenMP Multithreading

Distributes computation across CPU cores.

### Cache Blocking (Tiling)

Improves memory locality and reduces cache misses.

### Loop Interchange

Optimizes memory access patterns for row-major arrays.

---

## Supported Filters

- Blur
- Edge Detection
- Sharpen

---

## Performance Output

Each run prints execution time in milliseconds:

```text
Execution Time: 12 ms
```

---

## Notes

- Ensure `cnn_processor.exe` is built before starting the server
- On Windows, ensure correct path handling when executing binaries
- Input images are converted to grayscale for simplicity
- Output image size is reduced due to convolution (no padding)

---

## Educational Value

This project demonstrates core computer architecture concepts:

- SIMD vectorization (AVX2)
- Thread-level parallelism (OpenMP)
- Memory hierarchy optimization
- Cache-aware programming
- Real-world image processing pipeline

---

## Author

Computer Architecture optimization project focused on high-performance convolution using modern CPU techniques.