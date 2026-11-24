# C++ 课程实验

彭彰航（2025080910013） · [下载课程提交包](./2025080910013_彭彰航.zip)

## 开发过程

| 实验 | 提交记录 | 完成内容 |
| --- | --- | --- |
| 实验 1 | [实验 1 提交](https://github.com/p1z2h3H/c-/commits/history/lab1/) | 实现位姿初始化和查询，支持前进、左转、右转和批量指令，补充批量与空指令测试。 |
| 实验 2 | [实验 2 提交](https://github.com/p1z2h3H/c-/commits/history/lab2/) | 抽取移动与转向动作，通过 `ICommand` 分派指令，再增加加速开关与持续状态测试。 |
| 实验 3-1 | [本人操作记录](https://github.com/p1z2h3H/c-/commits/practice/lab3-1/) | 抽离位姿状态和指令类，改为表驱动，分别抽取坐标与朝向。 |
| 实验 3-2 | [本人操作记录](https://github.com/p1z2h3H/c-/commits/practice/lab3-2/) | 先写倒车测试，再实现倒车与转向，改用函数对象分派指令。 |
| 综合实验 | [本人操作记录](https://github.com/p1z2h3H/c-/commits/practice/lab4/) | 实现掉头、原子动作编排、指令工厂与单例，分层整理工程，扩展跑车和 Bus。 |

### 实验 3-1

1. 从 `ExecutorImpl` 抽出管理位姿的 `PoseHandler`。[提交](https://github.com/p1z2h3H/c-/commit/03c2162)
2. 将指令类移到 `Command.hpp`，随后用查找表分派指令。[指令类](https://github.com/p1z2h3H/c-/commit/c6e33d8) · [表驱动](https://github.com/p1z2h3H/c-/commit/ff68a63)
3. 分别抽取 `Point` 表示坐标、`Direction` 表示朝向。[坐标](https://github.com/p1z2h3H/c-/commit/edc1ade) · [朝向](https://github.com/p1z2h3H/c-/commit/da9fd9c)

### 实验 3-2

1. 为倒车移动增加测试，再实现 `B` 开关和后退。[测试](https://github.com/p1z2h3H/c-/commit/90ae31d) · [实现](https://github.com/p1z2h3H/c-/commit/c62d783)
2. 为普通倒车和加速倒车的转向增加测试，再实现倒车状态下的反向转向。[测试](https://github.com/p1z2h3H/c-/commit/895676e) · [实现](https://github.com/p1z2h3H/c-/commit/79ff87e)
3. 改用可调用的指令对象，补充验证加速与倒车开关独立且跨批次生效的测试。[函数对象](https://github.com/p1z2h3H/c-/commit/a1dc86e) · [状态测试](https://github.com/p1z2h3H/c-/commit/06a09a0)

### 综合实验

1. 先写各驾驶状态下的掉头测试，再实现 `TR`，随后把掉头改成有序的动作组合。[测试](https://github.com/p1z2h3H/c-/commit/57f8444) · [实现](https://github.com/p1z2h3H/c-/commit/491f583) · [动作编排](https://github.com/p1z2h3H/c-/commit/b84665d)
2. 补齐八种原子动作，让指令通过动作序列执行，抽取指令工厂并接入模板单例。[原子动作](https://github.com/p1z2h3H/c-/commit/ff86746) · [指令编排](https://github.com/p1z2h3H/c-/commit/54bc776) · [工厂](https://github.com/p1z2h3H/c-/commit/67f25db) · [单例](https://github.com/p1z2h3H/c-/commit/2a4aef8)
3. 补充相邻 `TRTR` 的测试，按模块整理工程，并在创建执行器时传入车型。[掉头测试](https://github.com/p1z2h3H/c-/commit/3057bab) · [模块分层](https://github.com/p1z2h3H/c-/commit/eebc281) · [车型参数](https://github.com/p1z2h3H/c-/commit/56ce41c)
4. 为跑车和 Bus 编写四种驾驶状态的测试，再实现两种车型的运动规则。[测试](https://github.com/p1z2h3H/c-/commit/aa170a4) · [实现](https://github.com/p1z2h3H/c-/commit/8d40ea9)

## 提交工程与构建

`main` 保存五份可独立构建的实验工程。下表是提交工程在 Windows MinGW 下记录的 GoogleTest 通过数。综合实验的本人操作分支另有 28 项 GoogleTest 通过记录。

| 提交工程 | GoogleTest 通过数 |
| --- | ---: |
| [实验 1](./实验1-高质量编程基础/代码说明.txt) | 16 |
| [实验 2](./实验2-面向对象编程/代码说明.txt) | 22 |
| [实验 3-1](./实验3-1-面向对象编程/代码说明.txt) | 22 |
| [实验 3-2](./实验3-2-面向函数式编程/代码说明.txt) | 55 |
| [综合实验](./综合实验/代码说明.txt) | 177 |

使用 Windows MinGW 时，将要测试的工程复制到全英文路径，在工程根目录运行以下命令。

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
ctest --test-dir build --output-on-failure
```

也可以在提交工程根目录运行 `script\build_and_run.bat`。使用 Linux 时运行 `bash script/build_and_run.sh`。
