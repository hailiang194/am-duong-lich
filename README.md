# am-duong-lich

Convert Julian day to Lunar day based on the idea of [Hồ Ngọc Đức](https://www.informatik.uni-leipzig.de/~duc/amlich/)

# Installation 
```sh
cmake -S . -B build <-DBUILD_EXAMPLES=ON>
```
set ``BUILD_EXAMPLES`` ``ON`` when you want to build examples
## Makefile
Build the library
```sh
cd build
make
```

## MSVC

```sh
MSBuild.exe build\am-duong-lich.sln
```

Build examples
```sh
MSBuild.exe build\examples\examples.sln
```

# Implement
Call this function
```cpp
std::array<int, 4> convertToLunarCalendar(const int& dd, const int& mm, const int& yyyy, const double& timezones)
```
Suppose you want to get Vietnamese lunar day of June 7 2022
```cpp
auto lunar = convertToLunarCalendar(7, 6, 2022, 7.0);
```
``lunar`` is a array with 
| Index |       Value       |
| :---: | :---------------: |
|   0   | Lunar day         |
|   1   | Lunar month       |
|   2   | Lunar year        |
|   3   | is lunar leap day |
