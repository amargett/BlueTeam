# BlueTeam

This is the code repository for [MIT's 2.009](https://2009.mit.edu) [Blue Team](https://2009.mit.edu/teams/team-pages/blue). It is intended to be used for source control for Arduino code.

## Setup

### Mac

Please see https://medium.com/@thomas.kilmar/arduino-cli-with-visual-studio-code-on-macos-d2ad32ff0276 for instructions on using Arduino with VSCode on Mac.

This link is also helpful: https://arduino.github.io/arduino-cli/0.35/installation/

**This is confirmed to work for macOS when `arduino-cli` is installed using [`brew`](https://formulae.brew.sh/formula/arduino-cli), which is the recommended installation method.**

Once you have `arduino-cli` set up, go to VS Code and install the [Arduino](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) extension by Microsoft. Once installed, go to the settings. Modify `Arduino: Command Path` to be `arduino-cli` and modify `Arduino: Path` to be `/usr/local/bin/`

### Windows

This link should help for Windows: https://colddsam.medium.com/exploring-the-world-of-arduino-programming-in-visual-studio-code-bbcb4af982e7

## How To Use

Each script must be a `.ino` format file and must reside in a folder with the same name as the file.

## Creating New Sketches

To create new sketches, you can run the following in the terminal under the BlueTeam directory:

```bash
arduino-cli sketch new sketchName
```
