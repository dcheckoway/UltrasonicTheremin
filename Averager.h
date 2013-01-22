/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef AVERAGER_H
#define AVERAGER_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/**
 * Template Based Averager
 * @author Dan Checkoway
 */
template <class T>
class Averager {
private:
  uint16_t cacheSize;
  T *cache;
  T total;
  uint16_t index;
public:
  Averager(uint16_t numSamples) {
    cacheSize = numSamples;
    cache = (T *)malloc(sizeof(T) * cacheSize);
    total = 0.0;
    index = 0;
    for (uint16_t k = 0; k < cacheSize; ++k) {
      cache[k] = 0;
    }
  }
  
  ~Averager() {
    free(cache);
  }
  
  void integrate(T value) {
    total -= cache[index];
    cache[index] = value;
    total += value;
    if (++index >= cacheSize) {
      index = 0;
    }
  }
  
  float getAverage() {
    return (float)total / (float)cacheSize;
  }
};

#endif
