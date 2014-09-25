#include "minerva.h"

#include <cstring>
#include <fstream>

using namespace std;
using namespace minerva;

int main(int argc, char** argv) {
  MinervaSystem& ms = MinervaSystem::Instance();
  ms.Initialize(&argc, &argv);
#ifdef HAS_CUDA
  uint64_t gpuDevice = ms.CreateGpuDevice(0);
#endif
  uint64_t cpuDevice = ms.CreateCpuDevice();
  ms.current_device_id_ = cpuDevice;
  int m = 3;
  int k = 2;
  NArray a = NArray::Randn({m, k}, 0.0, 1.0);
#ifdef HAS_CUDA
  ms.current_device_id_ = gpuDevice;
#endif
  NArray b = 1 - a;
  ms.current_device_id_ = cpuDevice;
  FileFormat format{false};
  a.ToFile("a.txt", format);
  b.ToFile("b.txt", format);
  return 0;
}
