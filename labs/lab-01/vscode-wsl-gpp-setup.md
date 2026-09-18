# VS Code + WSL + g++: Edit on Windows, Compile on Linux

**Goal:** Keep your project files on the normal Windows file system (e.g. `C:\Users\you\CS211`), so File Explorer, OneDrive, backups, etc. all work as usual, but run a **real Linux `g++`** (matching what an autograder or Linux-based assignment expects) through a WSL terminal built into VS Code.

> **This is the opposite of the "Remote-WSL" tutorials you'll find online.** Most official guides (including Microsoft's own) tell you to move your project *into* the Linux file system for best performance. This guide intentionally does **not** do that. Your files never leave Windows. Only the terminal (and the compiler it runs) lives in WSL. WSL automatically mounts your Windows drives at `/mnt/c/`, `/mnt/d/`, etc., which is what makes this possible.

---

## Prerequisites

- Windows 10 (build 19041+) or Windows 11
- [VS Code](https://code.visualstudio.com/) already installed on Windows
- Administrator access (one-time, for installing WSL)

---

## Step 1: Install WSL2 and a Linux distro

1. Open **PowerShell as Administrator** (right-click the Start button → *Terminal (Admin)* or *PowerShell (Admin)*).
2. Run:

   ```
   wsl --install
   ```

   This enables the WSL/Virtual Machine Platform features and installs **Ubuntu** by default.

   ![PowerShell running wsl --install](https://learn.microsoft.com/en-us/windows/wsl/media/wsl-install.png)
   *Source: [Microsoft Learn: Install WSL](https://learn.microsoft.com/en-us/windows/wsl/install)*

3. **Restart your computer** when prompted.
4. After restart, Ubuntu launches automatically (or find it in the Start menu). The first launch takes a minute to finish setting up, then asks you to create a UNIX username and password. This is separate from your Windows login and can be anything.

   ![Ubuntu terminal asking for a UNIX username](https://learn.microsoft.com/en-us/windows/wsl/media/ubuntuinstall.png)
   *Source: [Microsoft Learn: Install WSL](https://learn.microsoft.com/en-us/windows/wsl/install)*

5. Verify it installed correctly. In PowerShell:

   ```
   wsl --list --verbose
   ```

   You should see `Ubuntu` with `VERSION` = `2`.

You now have a Linux terminal available on demand. This is what you'll link VS Code's terminal to.

![Windows Terminal with a WSL/Ubuntu tab open](https://learn.microsoft.com/en-us/windows/wsl/media/terminal.png)
*Source: [Microsoft Learn: Install WSL](https://learn.microsoft.com/en-us/windows/wsl/install)*

---

## Step 2: Install the C++ toolchain **inside WSL**

Open the Ubuntu terminal (Start menu → *Ubuntu*) and run:

```
sudo apt update
sudo apt install -y build-essential gdb
```

`build-essential` includes `g++`, `gcc`, and `make`. Verify:

```
g++ --version
gdb --version
```

Both should print version info. This compiler lives **inside the WSL Linux environment only**. It is not installed on Windows, and that's fine, because we'll reach it through the WSL terminal.

---

## Step 3: Install the C/C++ extension in VS Code (on the Windows side)

1. Open VS Code normally (as a regular Windows app; **do not** use the "WSL" / "Reopen in Container" remote options for this workflow).
2. Go to the Extensions view (`Ctrl+Shift+X`) and install **C/C++** by Microsoft (`ms-vscode.cpptools`). Since VS Code itself is running locally on Windows (not in remote mode), it will install as a normal local extension, and you won't be prompted to "Install in WSL."

> You do **not** need the "WSL" (Remote Development) extension for this guide. That extension is for the alternate workflow where VS Code itself runs inside Linux and your files live there. It's shown below just so you recognize it and know to skip it here:

![VS Code Extensions view showing WSL-related extensions](https://learn.microsoft.com/en-us/windows/wsl/media/vscode-remote-wsl-extensions.png)
*Source: [Microsoft Learn: Set up a WSL development environment](https://learn.microsoft.com/en-us/windows/wsl/setup/environment)*

---

## Step 4: Open your project folder normally

`File → Open Folder…` and pick a folder on your `C:` drive, e.g. `C:\Users\you\CS211`.

Check the bottom-left corner of the VS Code window: it should **not** say "WSL: Ubuntu." If it does, you're in Remote-WSL mode and your files are being read from Linux, not Windows. Reopen the folder locally (`File → Open Recent`, or the `><` remote indicator → *Close Remote Connection*).

---

## Step 5: Point the integrated terminal at WSL

1. Open the integrated terminal: `` Ctrl+` `` (backtick).
2. Click the small dropdown arrow (⌄) next to the **+** button in the terminal panel.
3. Pick **Ubuntu (WSL)** from the list of detected profiles.

   ![Terminal profile dropdown listing PowerShell, Command Prompt, Git Bash, and WSL](https://code.visualstudio.com/assets/docs/terminal/basics/select-profile-dropdown.png)
   *Source: [VS Code Docs: Terminal Basics](https://code.visualstudio.com/docs/terminal/basics)*

A new terminal tab opens running **bash inside WSL**. Your prompt will change to something like `you@DESKTOP-XXXX:...$` instead of `PS C:\>`.

---

## Step 6: Navigate to your Windows files from inside WSL

WSL automatically mounts your Windows drives under `/mnt/`. Your project is reachable at:

```
cd /mnt/c/Users/you/CS211
ls
```

(Recent VS Code versions often open the WSL terminal already inside the matching `/mnt/c/...` folder for you. If it instead opens in your Linux home directory `~`, just `cd` there manually as above.)

You should see the same `.cpp` files you see in the VS Code Explorer pane on the left: same files, same filesystem, just viewed through Linux.

---

## Step 7: Compile and run

```
g++ -Wall -std=c++17 -o hello hello.cpp
./hello
```

![Terminal showing compiled program output](https://code.visualstudio.com/assets/docs/cpp/playbutton/helloworld-terminal-output.png)
*Source: [VS Code Docs: Using C++ and WSL in VS Code](https://code.visualstudio.com/docs/cpp/config-wsl)*

Edit the file in the normal VS Code editor (saving to Windows as always), then re-run the same `g++` command in the WSL terminal to recompile. Because the file lives on the shared `/mnt/c/` mount, the terminal always sees your latest saved changes instantly.

---

## Optional: make WSL your default terminal

So every new terminal opens straight into WSL without picking it from the dropdown each time:

1. `Ctrl+Shift+P` → **Terminal: Select Default Profile** → choose **Ubuntu (WSL)**.

Or add this to your VS Code `settings.json` (`Ctrl+Shift+P` → *Preferences: Open User Settings (JSON)*):

```json
{
  "terminal.integrated.defaultProfile.windows": "Ubuntu (WSL)"
}
```

---

## Optional: help IntelliSense find the WSL compiler

Editing still happens locally on Windows, so the C/C++ extension's IntelliSense engine runs on Windows too and can't automatically see `g++` inside WSL. This only affects red squiggles / autocomplete accuracy. It has **no effect** on compiling or running from the terminal in Steps 5-7 above, so it's safe to skip.

If you want to try tightening it up, open the Command Palette → **C/C++: Edit Configurations (JSON)** and set:

```json
{
  "configurations": [
    {
      "name": "WSL",
      "compilerPath": "C:\\Windows\\System32\\wsl.exe",
      "compilerArgs": ["g++"],
      "cStandard": "c17",
      "cppStandard": "c++17",
      "intelliSenseMode": "linux-gcc-x64"
    }
  ],
  "version": 4
}
```

Behavior here varies a bit by C/C++ extension version. If IntelliSense doesn't pick it up cleanly, don't worry about it; it's cosmetic.

---

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| `g++: command not found` | You're in a Windows shell (prompt shows `PS C:\>`), not the WSL profile. Reopen the terminal with the **Ubuntu (WSL)** profile (Step 5). |
| "Ubuntu (WSL)" doesn't appear in the profile dropdown | WSL/Ubuntu isn't installed yet (Step 1), or VS Code needs to be restarted after installing WSL. |
| `bash: /mnt/c/...: No such file or directory` | Double-check the exact path and capitalization. WSL's `/mnt/c/` mount is case-sensitive even though Windows isn't. |
| Compiling feels slow on large projects | Reading/writing across the Windows-WSL boundary (`/mnt/c/`) is slower than a native Linux filesystem. It's negligible for coursework-sized C++ files; if it ever matters, that's when the full Remote-WSL workflow (files stored natively in Linux) is worth switching to. |
| VS Code shows "WSL: Ubuntu" in the bottom-left corner | You've accidentally opened the folder in Remote-WSL mode. Click that indicator → *Close Remote Connection*, then reopen the folder normally (Step 4). |

---

## Sources / further reading

- [Microsoft Learn: Install WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
- [Microsoft Learn: Set up a WSL development environment](https://learn.microsoft.com/en-us/windows/wsl/setup/environment)
- [VS Code Docs: Terminal Profiles](https://code.visualstudio.com/docs/terminal/profiles)
- [VS Code Docs: Terminal Basics](https://code.visualstudio.com/docs/terminal/basics)
- [VS Code Docs: Using C++ and WSL in VS Code](https://code.visualstudio.com/docs/cpp/config-wsl) *(describes the full Remote-WSL workflow this guide deliberately avoids)*
