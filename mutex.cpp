#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <string.h>

static std::atomic<bool> KEEP_GOING;

struct Point {
    long x;
    long y;
};

template<class T, size_t arraySize>
class SharedArray {
public:
    void get(size_t index, T* out) const {
        std::lock_guard<std::mutex> lockit(_mtx);
        *out = _items[index];
    }

    void set(size_t index, const T& value) {
        std::lock_guard<std::mutex> lockit(_mtx);
        _items[index] = value;
    }

    void clean() { memset(_items, 0, sizeof(_items)); }
private:
   T _items[arraySize];
   mutable std::mutex _mtx;
};

#define SHARED_ARRAY_SIZE 10
static SharedArray<Point, SHARED_ARRAY_SIZE> SHARED_ARRAY;

void doWrites()
{
  Point p;
  p.x = 0;
  p.y = 0;
  while(true) {
      if (!KEEP_GOING.load())
          break;
      for (size_t i = 0 ; i < SHARED_ARRAY_SIZE; ++i){
          SHARED_ARRAY.set(i, p);
          ++p.x;
          ++p.y;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

void doReads()
{
    while(true) {
      if(!KEEP_GOING.load())
        break;
      for (size_t i = 0 ; i < SHARED_ARRAY_SIZE; ++i){
          Point r;
          SHARED_ARRAY.get(i, &r);
          std::cout << "x=" << r.x << " y=" << r.y << "\n";
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(500));   
  }
}

int main() {
  KEEP_GOING.store(true);
  SHARED_ARRAY.clean();
  std::thread writer(&doWrites);
  std::thread reader(&doReads);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  KEEP_GOING.store(false);
  writer.join();
  reader.join();
}