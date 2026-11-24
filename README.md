# C++ 课程实验

彭彰航（2025080910013） · [下载课程提交包](./2025080910013_彭彰航.zip)

**验收入口**见[提交工程与构建](#提交工程与构建)。核对 Git 开发步骤请查看下表，运行历史节点请见[复跑历史提交](#复跑历史提交)。

## 开发过程

最终交付位于 `main` 的五个实验目录和页面顶部的 ZIP。下表同时给出过程分支和可用于核对提交版的源码节点。

| 实验 | 逐步提交 | 提交版源码节点 | 完成内容 |
| --- | --- | --- | --- |
| 实验 1 | [实验 1 提交](https://github.com/p1z2h3H/c-/commits/history/lab1/) | [`07214cf`](https://github.com/p1z2h3H/c-/commit/07214cf) | 实现位姿初始化和查询，支持前进、左转、右转和批量指令，补充批量与空指令测试。 |
| 实验 2 | [实验 2 提交](https://github.com/p1z2h3H/c-/commits/history/lab2/) | [`f9a392d`](https://github.com/p1z2h3H/c-/commit/f9a392d) | 分别抽取移动与左右转成员函数，再集中封装三个指令类，通过 `ICommand` 分派。随后增加加速开关与持续状态测试。 |
| 实验 3-1 | [本人操作记录](https://github.com/p1z2h3H/c-/commits/practice/lab3-1/) | [`5e3cc6a`](https://github.com/p1z2h3H/c-/commit/5e3cc6a) | 抽离位姿状态和指令类，改为表驱动，分别抽取坐标与朝向。 |
| 实验 3-2 | [本人操作记录](https://github.com/p1z2h3H/c-/commits/practice/lab3-2/) | [`8157010`](https://github.com/p1z2h3H/c-/commit/8157010) | 先写倒车测试，再实现倒车与转向，改用函数对象分派指令。 |
| 综合实验 | [本人操作记录](https://github.com/p1z2h3H/c-/commits/practice/lab4/) | [`6f5a3c0` 阶段快照](https://github.com/p1z2h3H/c-/commit/6f5a3c0)，随后在 `main` [补充相邻掉头测试](https://github.com/p1z2h3H/c-/commit/a96ce75)并[修复工厂拷贝约束、更新提交包](https://github.com/p1z2h3H/c-/commit/a40fcbf) | 实现掉头、原子动作编排、指令工厂与单例，分层整理工程，扩展跑车和 Bus。 |

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

`main` 保存五份可独立构建的实验工程。下表是提交工程在 Windows MinGW 下记录的 GoogleTest 通过数。综合实验的 `practice/lab4` 通过 28 项 GoogleTest，`main` 的综合实验工程通过 177 项。测试数量对应各自的源码版本。

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

## 复跑历史提交

过程分支的 CMake 工程需要课程自带的 `tests/googletest`。从 GitHub 克隆仓库后，在 `main` 的仓库根目录执行下面的 Bash 命令。示例将综合实验的练习分支导出到临时目录，并从提交工程复制同一份 GoogleTest。

```bash
git fetch origin
review_dir="$(mktemp -d)"
git archive origin/practice/lab4 | tar -x -C "$review_dir"
cp -R "实验1-高质量编程基础/tests/googletest" "$review_dir/tests/"
cmake -S "$review_dir" -B "$review_dir/build"
cmake --build "$review_dir/build" --parallel 2
ctest --test-dir "$review_dir/build" --output-on-failure
```

把 `origin/practice/lab4` 换成表中的过程分支或单个提交号，即可复跑其他节点。例如，`57f8444` 先加入掉头测试，此时预期有测试失败。`491f583` 加入实现后，预期通过。

## 掉头验收口径

综合实验按《需求4-支持掉头功能》和实验 4 第 13 页实现 `TR`。`B` 状态下仍执行普通掉头，`BF` 状态下执行加速掉头。实验 4 第 41–42 页的示例会在倒车状态跳过掉头，两处口径存在差异。以初始位姿 `(0, 0, E)` 为例，本工程执行 `BTR` 后得到 `(0, 1, W)`，执行 `BFTR` 后得到 `(1, 1, W)`。
