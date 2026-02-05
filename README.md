
# How to prepare

To get started, you can either install a **Local Environment** (preferred for hardware testing) or use the **Remote Development Setup**.

## Local development setup

This is the preferred method for development. It allows you to build and test code for both the Wokwi Simulator and real hardware.

### 1. Required Software
Install the following tools to get started:

* Editor: [Visual Studio Code](https://code.visualstudio.com/)
* Extensions:
    * [ESP-IDF Extension](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension): For building and flashing code.
    * [Wokwi Simulator](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode): For hardware simulation within VS Code.

### 2. Initial Configuration
1.  **ESP-IDF Setup:** After installing the extension, you must run the **ESP-IDF Setup wizard**. 
    > *Note: This process downloads the compiler and tools; it may take a significant amount of time depending on your internet speed.*
2.  **Wokwi Licensing:** * Register an account at [wokwi.com](https://wokwi.com).
    * In VS Code, press `F1` (or `Ctrl+Shift+P`) and run the command: **Wokwi: Request a new License**.
    * Follow the browser prompts to activate the extension.

### 3. Building & Running
* **Build:** Use the ESP-IDF "Build" icon (the cylinder icon) in the bottom status bar. The first build will be slow as it compiles the entire framework.
* **Simulate:** Once the build is successful, open the `diagram.json` file. The simulator should automatically trigger, or you can press the **Play** button.

**Have fun coding!**

## Remote Development Setup

If you are unable to configure your local system, you can use **Wokwi** for programming, building, and simulation.

### 1. Pre-requisites
Before setting up the environment, download the following driver files from the [Max7219 GitHub Library](https://github.com/esp-idf-lib/max7219/):
* `max7219.c`
* `max7219.h`

### 2. Wokwi Project Initialization
1.  Go to [www.wokwi.com](https://www.wokwi.com).
2.  Select **ESP32** > **ESP-IDF Templates** > **ESP32**.
3.  Copy the content of `explorer_main.c` from this project and paste it into the `main.c` tab in Wokwi.
4.  Copy the content of `diagram.json` file from this project and paste it into the `diagram.json` tab in the Wokwi editor.



### 3. Adding Library Files
To ensure the project compiles correctly, you must manually add the driver files:
1.  In the Wokwi file explorer, click the **arrow** next to the Library Manager (or the "plus" icon for new files).
2.  Choose **Upload file(s)...**.
3.  Select and upload the `max7219.c` and `max7219.h` files you downloaded in Step 1.

You should now be ready to code. Have fun.


# Usefull tools
This tool will help you with making bitmaps:
  https://xantorohara.github.io/led-matrix-editor/


