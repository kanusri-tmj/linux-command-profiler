# Linux Command Execution Time Profiler

## 1. Project Overview

The Linux Command Execution Profiler is a C-based command-line tool that measures the execution time and resource usage of Linux commands.

It executes commands, collects resource usage information, and displays an execution report for each command.

## 2. Problem Statement

Create a tool that measures the execution time and resource usage of Linux commands.

## 3. Objectives

- Measure command execution time.
- Measure user CPU time and system CPU time.
- Display maximum memory usage.
- Display the command's exit status.
- Handle invalid and empty commands.
- Allow users to execute multiple commands in one session.

## 4. Technologies Used

- Programming Language: C
- Operating Environment: Linux (Ubuntu on WSL2)
- Compiler: GCC
- System Calls and Linux APIs: `fork()`, `execvp()`, `wait4()`, `clock_gettime()`
- Development Tools: Ubuntu Terminal and Nano editor

## 5. Features

- Executes Linux commands with their arguments.
- Reports elapsed execution time in seconds.
- Displays user CPU time and system CPU time.
- Reports maximum memory usage in KB.
- Displays the command's exit status.
- Detects invalid commands and reports execution failure.
- Handles empty command input.
- Continues accepting commands until the user enters `exit`.

## 6. Project Setup

Open a Linux terminal and navigate to the project directory:

```bash
cd ~/linux-command-profiler
```

Compile the program:

```bash
gcc -Wall -Wextra profiler.c -o profiler
```

Run the profiler:

```bash
./profiler
```

## 7. Usage

Enter a Linux command when prompted.

Example commands:

```text
pwd
ls -l
sleep 2
exit
```

The profiler displays an execution report after each command. Enter `exit` to close the program.

## 8. Execution Report

The report contains:

- Command: The command entered by the user.
- Execution time: The elapsed time measured for the command execution and waiting process.
- User CPU time: CPU time spent executing user-space code.
- System CPU time: CPU time spent executing kernel code on behalf of the process.
- Maximum memory: Maximum resident memory usage reported by Linux.
- Exit status: The command's exit code, or a signal number if the process is terminated by a signal.

## 9. Testing

The following tests have been performed:

| Test | Expected Behaviour | Result |
|---|---|---|
| `pwd` | Displays the working directory and execution report | Passed |
| `sleep 2` | Reports approximately two seconds of elapsed time | Passed |
| `ls -l` | Lists directory contents and displays the report | Passed |
| `abcxyz` | Displays an execution error and exit status 127 | Passed |
| Empty input | Displays an empty-command error | Passed |
| `exit` | Closes the profiler | Passed |

## 10. Limitations

- Commands are entered using space-separated arguments.
- Shell features such as pipes, redirection, and shell operators are not supported.
- Arguments containing embedded spaces or quotation marks are not parsed as shell syntax.
- Resource measurements depend on the Linux environment and the command being executed.

## 11. Conclusion

The Linux Command Execution Profiler demonstrates how process creation, command execution, timing, and resource measurement can be implemented using C and Linux APIs. It provides a simple way to observe the execution time and resource usage of Linux commands.

## 12. Future Enhancements

- Support command history and saved reports.
- Export execution reports to a CSV file.
- Compare resource usage across multiple commands.
- Add support for more advanced command-line parsing.
