# Problem 093 - Czar的Silly Pacman

**ACMOJ Problem ID**: 2344

## Table of Contents

- [Problem 093 - Czar的Silly Pacman](#problem-093-czar的silly-pacman)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [OJ Git Repository Compilation Process](#oj-git-repository-compilation-process)
    - [Git Configuration Requirements](#git-configuration-requirements)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

This problem tests algorithmic problem-solving skills.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **2344. Czar的Silly Pacman** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/093/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

在大一暑假中，Czar在大量代码模板的帮助下完成了简易的pacman agent实现AI操控吃豆人，可悲的是在长达数天的数据训练后，pacman不但没有有效提升躲避ghost的能力，还掌握了骗分奇技淫巧：通过吃药丸后吃鬼拿到高分，再及时送死。这让Czar很是失落，于是他准备反向上分，实现一款Silly pacman agent，请你帮他判断这个吃豆人能拿到多少分。

地图大小10×10（默认地图外围有墙体）

每格上：

0表示墙体，1表示空位，2表示带有豆子的位子，3表示鬼魂（可有多个），4表示吃豆人起点（保证存在且唯一）

**游戏规则**

**行动**

吃豆人从起点向上出发，若遇到分岔路口按照**右手原则**，即右转>直行>左转>掉头的优先级行动，碰到鬼魂后游戏结束，**若吃豆人会进入死循环请输出“Silly Pacman”**。

**加分**

吃到豆子+2（豆子可被吃掉，即**不会重复加分**），碰到鬼魂-500，无时间代价。

### Input Format

10*10的数据，即：

共 10行输入。每一行各输入 10个数字。第 i 行 j 列表示地图上（i , j) 位置。（0 base）

### Output Format

一个整数，表示pacman最后的得分；若进入死循环则输出**“Silly Pacman”**。

### Samples

#### 样例 1

**Input:**
```
4 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 2
1 1 1 1 3 0 0 0 0 0
0 0 1 0 0 0 0 0 0 0
0 2 1 0 0 0 0 0 2 2
0 0 1 3 0 0 0 0 0 0
0 0 1 1 1 1 2 0 0 0
0 0 0 0 0 0 1 2 0 0
0 0 0 0 2 2 1 0 0 0
2 1 1 1 1 0 0 0 0 0
```

**Output:**
```
-488
```

#### 样例 2

**Input:**
```
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 3 0 0 0 0
0 0 0 0 0 4 1 0 0 0
0 0 0 0 0 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```

**Output:**
```
Silly Pacman
```

### Data Constraints

保证出发点唯一，保证输入合法

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 1000 ms
- **Memory Limit (per test case)**: 256 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/093/data_test/`.

## Submission Requirements

### OJ Git Repository Compilation Process

For Git compilation, we will first clone the repository using a command similar to:
```bash
git clone <repo_url> . --depth 1 --recurse-submodules --shallow-submodules --no-local
```

Then we check if there is a `CMakeLists.txt` file. If it exists, we run (if not, a warning message will be displayed):
```bash
cmake .
```

Finally, we check if there is any of `GNUmakefile`/`makefile`/`Makefile` (if cmake was run previously, this will be the generated Makefile). If it exists, we run (if not, a warning message will be displayed):
```bash
make
```

After this process is complete, we will use the `code` file in the project root directory as the compilation result.

A `CMakeLists.txt` file is provided in the project. You can use or modify it as needed. The local environment has gcc-13 and g++-13 available.

### Git Configuration Requirements

**IMPORTANT**: You must create a `.gitignore` file in your project root directory to avoid OJ evaluation conflicts.

The `.gitignore` file should include at least the following entries:

```gitignore
CMakeFiles/
CMakeCache.txt
```

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The compiled executable file name must be `code`
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
