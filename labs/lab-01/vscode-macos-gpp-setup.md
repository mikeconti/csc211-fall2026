# VS Code + g++ on macOS

**Goal:** Get a working `g++` command-line toolchain and VS Code set up on macOS for CSC 211. Unlike Windows, macOS is already Unix-based, so there's no WSL-style split here: your files and your compiler live in the same place, and VS Code's built-in terminal is already a real Unix shell.

> **One thing to know:** on macOS, the `g++` command is actually Apple's own compiler (Clang) wearing a `g++` name. That's fine for this course; it's very compatible with GNU g++ for course-level C++. Just keep in mind that your final submission is graded on a Linux station, so always test your code once more after any last-minute changes.

---

## Prerequisites

- macOS with an admin account
- [VS Code](https://code.visualstudio.com/) already installed

---

## Step 1: Install the Xcode Command Line Tools

This gives you a working compiler, `make`, `git`, and other basic dev tools, without installing the full Xcode app.

Open **Terminal** (Spotlight → type "Terminal") and run:

```
xcode-select --install
```

A system dialog will pop up asking to install the developer tools. Click **Install**, accept the license, and wait for it to finish (a few minutes).

Verify it worked:

```
g++ --version
```

This should print version info (it will report itself as Apple Clang; see the note above).

---

## Step 2: Install the C/C++ extension in VS Code

1. Open VS Code.
2. Go to the Extensions view (`Cmd+Shift+X`) and install **C/C++** by Microsoft (`ms-vscode.cpptools`).

![C/C++ extension shown in the VS Code Extensions view](https://code.visualstudio.com/assets/docs/cpp/cpp/cpp-extension.png)
*Source: [VS Code Docs: Using Clang in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-clang-mac)*

---

## Step 3: Open your project folder and use the integrated terminal

`File → Open Folder…` and pick your project folder (e.g. `~/CSC211`). Open the integrated terminal with `` Ctrl+` ``. It's already a normal Unix shell (zsh by default), already sitting in your project folder, no profile switching required.

---

## Step 4: Compile and run

```
g++ -Wall -std=c++17 -o hello hello.cpp
./hello
```

![Terminal output after running a compiled C++ program](https://code.visualstudio.com/assets/docs/cpp/clang-mac/helloworld-terminal-output.png)
*Source: [VS Code Docs: Using Clang in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-clang-mac)*

Edit the file in the editor, save it, then re-run the same `g++` command in the terminal to recompile.

---

## Optional: one-click build with the Play button

The C/C++ extension adds a play button in the top-right corner of a `.cpp` file. Clicking it (or its dropdown) offers a **"C/C++: clang++ build and debug active file"** task, which compiles and runs the current file without typing the `g++` command yourself.

![Debug configuration dropdown for building and debugging the active C++ file](https://code.visualstudio.com/assets/docs/cpp/clang-mac/build-and-debug-active-file.png)
*Source: [VS Code Docs: Using Clang in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-clang-mac)*

---

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| `xcrun: error: invalid active developer path` | The Command Line Tools didn't finish installing, or got removed by a macOS/Xcode update. Re-run `xcode-select --install`. |
| `g++ --version` shows "Apple clang" | Expected; see the note at the top. This is fine for this course. |
| `command not found: g++` | The Command Line Tools aren't installed yet. Run `xcode-select --install` (Step 1). |
| Program compiles but VS Code shows red squiggles everywhere | IntelliSense hasn't picked up the compiler yet. Command Palette → **C/C++: Edit Configurations (UI)** and set the compiler path explicitly (e.g. `/usr/bin/clang++`). This is cosmetic and doesn't affect compiling in the terminal. |

---

## Sources / further reading

- [VS Code Docs: Using Clang in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-clang-mac)
