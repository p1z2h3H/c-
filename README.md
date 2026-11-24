# C++ 课程实验

提交人 彭彰航（2025080910013）

[原始提交包](./2025080910013_彭彰航.zip)。以下各阶段均可独立构建，表中的测试数量来自 Windows MinGW 构建后的实际运行。

| 阶段 | 实现内容 | 通过的测试数 |
| --- | --- | ---: |
| [实验1-高质量编程基础](./实验1-高质量编程基础/代码说明.txt) | 基本指令、初始化和查询 | 16 |
| [实验2-面向对象编程](./实验2-面向对象编程/代码说明.txt) | 指令类与加速 | 22 |
| [实验3-1-面向对象编程](./实验3-1-面向对象编程/代码说明.txt) | 状态抽离与表驱动 | 22 |
| [实验3-2-面向函数式编程](./实验3-2-面向函数式编程/代码说明.txt) | 函数对象、倒车和加速倒车 | 55 |
| [综合实验](./综合实验/代码说明.txt) | 掉头、原子动作编排、跑车和 Bus | 177 |

每个阶段包含 `include/`、`src/`、`tests/`、构建脚本和代码说明。

## 构建与验收

如使用 Windows MinGW，请把要测试的阶段复制到全英文路径，再在该阶段的根目录运行：

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
ctest --test-dir build --output-on-failure
```

也可运行 `script\build_and_run.bat`。配置、编译或测试失败时，脚本会返回非零退出码。使用 Linux 时，运行 `bash script/build_and_run.sh`。

## 开发记录

以下练习分支记录了彭彰航亲手完成的实验3-1、实验3-2和综合实验。可以按阶段逐条查看测试、实现与重构提交。

| 阶段 | 本人操作记录 | 主要步骤 |
| --- | --- | --- |
| 实验3-1 | [practice/lab3-1](https://github.com/p1z2h3H/c-/commits/practice/lab3-1/) | 状态抽离、拆出指令类、表驱动、坐标与方向抽象 |
| 实验3-2 | [practice/lab3-2](https://github.com/p1z2h3H/c-/commits/practice/lab3-2/) | 倒车和倒车转向先提交测试再实现，改用函数对象 |
| 综合实验 | [practice/lab4](https://github.com/p1z2h3H/c-/commits/practice/lab4/) | 掉头、原子动作编排、指令工厂、单例、工程分层和车型扩展 |

练习分支的综合实验在 Windows MinGW 下通过 28 项 GoogleTest 和 CTest。`main` 上方的测试数量对应打包提交的工程。

以下是各阶段的原始提交记录。记录来自各阶段使用的本地 Git 仓库，导入时保留了文件快照、提交说明、时间与父子关系，公开邮箱使用 GitHub 的 noreply 地址。

| 阶段 | 提交历史 | 可核验的开发过程 |
| --- | --- | --- |
| 实验1 | [history/lab1](https://github.com/p1z2h3H/c-/commits/history/lab1/) | 初始化、移动和转向分别提交测试及实现，随后增加批量与空指令测试。 |
| 实验2 | [history/lab2](https://github.com/p1z2h3H/c-/commits/history/lab2/) | 抽取基础动作和指令类，引入多态。加速测试与功能实现分开提交。 |
| 实验3-1 | [history/lab3-1](https://github.com/p1z2h3H/c-/commits/history/lab3-1/) | 一次阶段提交，记录状态抽离和表驱动重构。 |
| 实验3-2 | [history/lab3-2](https://github.com/p1z2h3H/c-/commits/history/lab3-2/) | 先提交倒车测试，再继承状态抽象，随后实现函数对象与倒车行为。 |
| 综合实验 | [history/lab4](https://github.com/p1z2h3H/c-/commits/history/lab4/) | 一次阶段提交，记录掉头、车型行为和原子动作编排。 |

`main` 保存按提交样本组织的五份工程和压缩包，后续构建修订也记录在 `main`。
