# CS2025-Fall

学习 · 记录 · 成长

---

## 🧰 一、前提条件

请确保你已经完成以下安装：

- [x] VS Code 安装在 `D:\Program Files\VS Code`
- [x] Git 已安装并加入 PATH
- [x] MinGW-w64（或 MSYS2）已安装并 `g++` 可用
- [x] NASM 汇编器已安装并加入 PATH
- [x] Live Server 插件已安装

> 如果未完成，请参考前文“下载 VS Code 到 D 盘”和“工具准备”部分补全。

---

## 🔌 二、Git 集成（版本控制）

### ✅ 步骤 1：验证 Git 是否可用

1. 打开 VS Code。
2. 按下 `Ctrl + ``（反引号）打开内置终端。
3. 输入：
   ```bash
   git --version
   ```
   应显示类似：
   ```
   git version 2.45.1.windows.1
   ```

✅ 如果有版本号，说明 Git 已正确集成。

---

### ✅ 步骤 2：初始化 Git 仓库

1. 在资源管理器中右键你的项目文件夹（如 `D:\Projects\html-css-js`）。
2. 选择 **“Open with Code”**。
3. 在 VS Code 中按下 `Ctrl+Shift+P` 打开命令面板。
4. 输入并选择：`Git: Initialize Repository`
5. 选择当前文件夹作为仓库根目录。

---

### ✅ 步骤 3：使用源代码管理功能

- 左侧活动栏点击 **源代码管理图标（分支形状）**
- 添加文件 → 写提交信息 → 点击 ✔ 提交
- 可连接 GitHub 进行推送（需登录）

> 💡 提示：安装 **GitLens** 插件可增强 Git 功能（查看行级提交记录等）

---

## 🧱 三、C++ 集成（编译与调试）

### ✅ 步骤 1：创建 C++ 项目

1. 在 `D:\Projects\cpp` 下新建文件夹 `hello-cpp`
2. 用 VS Code 打开该文件夹
3. 新建文件 `main.cpp`

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, C++!" << endl;
    return 0;
}
```

---

### ✅ 步骤 2：配置编译运行（使用 Code Runner）

1. 安装插件：**Code Runner**
2. 打开设置：`Ctrl + ,`
3. 搜索 `code runner executor map`
4. 点击“在 settings.json 中编辑”
5. 添加或修改 `cpp` 的执行命令：

```json
"code-runner.executorMap": {
    "cpp": "cd $dir && g++ -Wall -O2 -std=c++17 $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt"
}
```

> ⚠️ Windows 用户注意：最后是 `$dir$fileNameWithoutExt`，不是 `/` 而是 `\`，但 VS Code 会自动处理。

---

### ✅ 步骤 3：运行 C++ 程序

- 打开 `main.cpp`
- 右键 → **“Run Code”** 或按 `Ctrl+Alt+N`
- 终端输出：
  ```
  Hello, C++!
  ```

---

### ✅ 步骤 4：配置调试（launch.json）

1. 按 `Ctrl+Shift+P` → 输入 `Debug: Open launch.json`
2. 选择环境：`C++ (GDB/LLDB)`
3. 自动生成 `launch.json` 文件，内容如下：

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "g++.exe - Build and debug active file",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "C:\\msys64\\mingw64\\bin\\gdb.exe", // 修改为你的 gdb 路径
      "setupCommands": [
        {
          "description": "Enable pretty printing",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "Compile C++"
    }
  ]
}
```

---

### ✅ 步骤 5：配置编译任务（tasks.json）

1. 按 `Ctrl+Shift+P` → 输入 `Tasks: Configure Task`
2. 选择 `Create tasks.json file from template` → `Others`
3. 编辑为：

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Compile C++",
      "type": "shell",
      "command": "g++",
      "args": [
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}.exe"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

✅ 现在你可以按 `F5` 启动调试，支持断点、单步执行等功能。

---

## 🌐 四、HTML/CSS/JavaScript 集成

### ✅ 步骤 1：使用 Live Server

1. 在 `D:\Projects\html-css-js` 创建 `index.html`
2. 写入简单 HTML 内容
3. 右键编辑器 → **“Open with Live Server”**
4. 浏览器自动打开 `http://127.0.0.1:5500/index.html`
5. 修改代码保存后，页面自动刷新！

---

### ✅ 步骤 2：格式化与智能提示

- 安装 **Prettier** 插件
- 保存时自动格式化：设置中启用
  ```json
  "editor.formatOnSave": true
  ```

---

## 🔤 五、汇编语言集成（NASM + DOSBox）

### ✅ 步骤 1：语法高亮

- 安装插件：**Assembly Language Support for Visual Studio Code**

### ✅ 步骤 2：创建汇编项目

1. 在 `D:\Projects\assembly` 创建 `hello.asm`
2. 写入 32 位 Linux 风格汇编（用于学习）：

```nasm
section .data
    msg db 'Hello, Assembly!', 0xA
    len equ $ - msg

section .text
    global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, len
    int 0x80

    mov eax, 1
    int 0x80
```

---

### ✅ 步骤 3：运行汇编（需 WSL 或 Linux）

如果你使用 **WSL**：

1. 在 VS Code 中打开 WSL 环境
2. 安装 NASM：
   ```bash
   sudo apt install nasm
   ```
3. 编译运行：
   ```bash
   nasm -f elf32 hello.asm -o hello.o
   ld -m elf_i386 hello.o -o hello
   ./hello
   ```

> Windows 本地可用 DOSBox + NASM 实现 16 位汇编调试（见前文）

---

## ✅ 六、总结：VS Code 集成成果

| 技术            | 功能                             |
| --------------- | -------------------------------- |
| **Git**         | 提交、推送、分支管理，图形化操作 |
| **C++**         | 编译、运行、调试（F5 断点调试）  |
| **HTML/CSS/JS** | 实时预览（Live Server）、格式化  |
| **汇编**        | 语法高亮、外部工具链运行         |

---

## 🎯 下一步建议

1. **每天练习一个小项目**（如写一个计算器网页）
2. **把代码提交到 GitHub**
3. **尝试调试 C++ 程序的断点**
4. **用 Live Server 查看网页实时变化**

## 需要我为你生成一份 **`settings.json` 完整配置模板** 或 **项目结构脚本** 吗？欢迎继续提问！

© 2025 cybxiaohai
