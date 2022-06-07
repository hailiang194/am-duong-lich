# am-duong-lich

Chuyển đổi ngày dương sang âm

# Installation (Cài đặt)
```bash
cmake -S . -B build <-DBUILD_EXAMPLES=ON>
```
set ``BUILD_EXAMPLES`` ``ON`` when you want to build examples (đặt ``BUILD_EXAMPLES`` ``ON`` khi muốn xây dựng cả các ví dụ)
## Makefile
Build the library (Xây dựng thư viện)
```
cd build
make
```

## MSVC

```
MSBuild.exe build\am-duong-lich.sln
```

Build examples (Xây dựng các ví dụ)
```
MSBuild.exe build\examples\examples.sln
```

#Implement (Thực thi)
Call this function (Gọi hàm này)
```cpp
std::array<int, 4> convertToLunarCalendar(const int& dd, const int& mm, const int& yyyy, const double& timezones)
```
Suppose you want to get Vietnamese lunar day of June 7 2022
```
auto lunar = convertToLunarCalendar(7, 6, 2022);
```
``lunar`` is a array with 
| Index |       Value       |
| :---: | :---------------: |
|   0   | Lunar day         |
|   1   | Lunar month       |
|   2   | Lunar year        |
|   3   | is lunar leap day |
