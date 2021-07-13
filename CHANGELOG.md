# ish changelog
### dd/mm/yy date format

## 09/7/2021
- Work on shell started.
- Original shell (shell1) done.
- Work on a better shell started.

## 10/7/2021
- Initial version of the better shell is done.
- Ihe better shell gets its name: `ish` (itai's shell).
- Initial commit.
- A few bugfixes.

## 11/7/2021
- More bug fixes.
- Packaging target using cpack added to CMakeLists.txt
- Github Actions workflow to build x86_64 version on creation of a release added.
- Attempts to make arm64 builds work as well satrted and failed...

## 12/7/2021
- Fix prompt being overwritten when entering a long line of text to the shell.
- Add (admitedly horendous) SIGINT (CTRL+C) handling so the shell kills the child process but keeps itself running.
- Release v0.2-alpha!
- Add `history` built-in command.

## 14/7/2021
- Add `pwd` built-in command.
- Improve `prompt_refresh` function.

***
